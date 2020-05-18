#include "../include/ftp_client_command.hpp"
#include "../include/ftp_client_control.hpp"
#include "../include/ftp_client_ui.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

#define EMPTY_STRING ""


void handleCommandHelp() {
    printf(
        "Usage: %s[ %s | %s | %s | %s | %s | %s | %s | %s | %s ]\n"
        "%-8s%-8s%-16sGives the list of FTP commands available and how to use them.\n"
        "%-8s%-8s%-16sSubmits the %s to FTP server for authentication.\n"
        "%-8s%-8s%-16sSubmits the %s to FTP server for authentication.\n"
        "%-8s%-8s%-16sRequests FTP server to print current directory.\n"
        "%-8s%-8s%-16sRequests FTP server to list the entries in the current directory.\n"
        "%-8s%-8s%-16sRequests FTP server to change current working directory to %s.\n"
        "%-8s%-8s%-16sRequests FTP server to change current directory to parent directory.\n"
        "%-8s%-8s%-16sRequests FTP server to send the file with %s.\n"
        "%-8s%-8s%-16sRequests to end FTP session and quits the program.\n\n"
        ,FTP_CLIENT_PROMPT
        ,FTP_CLIENT_USER_COMMAND_HELP
        ,FTP_CLIENT_USER_COMMAND_USER
        ,FTP_CLIENT_USER_COMMAND_PASSWORD
        ,FTP_CLIENT_USER_COMMAND_PRINT_DIRECTORY
        ,FTP_CLIENT_USER_COMMAND_DIRECTORY
        ,FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY
        ,FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_UP
        ,FTP_CLIENT_USER_COMMAND_GET
        ,FTP_CLIENT_USER_COMMAND_QUIT
        ,EMPTY_STRING
        ,FTP_CLIENT_USER_COMMAND_HELP
        ,EMPTY_STRING
        ,EMPTY_STRING
        ,FTP_CLIENT_USER_COMMAND_USER
        ,FTP_CLIENT_USER_COMMAND_USER_ARG
        ,FTP_CLIENT_USER_COMMAND_USER_ARG
        ,EMPTY_STRING
        ,FTP_CLIENT_USER_COMMAND_PASSWORD
        ,FTP_CLIENT_USER_COMMAND_PASSWORD_ARG
        ,FTP_CLIENT_USER_COMMAND_PASSWORD_ARG
        ,EMPTY_STRING
        ,FTP_CLIENT_USER_COMMAND_PRINT_DIRECTORY
        ,EMPTY_STRING
        ,EMPTY_STRING
        ,FTP_CLIENT_USER_COMMAND_DIRECTORY
        ,EMPTY_STRING
        ,EMPTY_STRING
        ,FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY
        ,FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_ARG
        ,FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_ARG
        ,EMPTY_STRING
        ,FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_UP
        ,EMPTY_STRING
        ,EMPTY_STRING
        ,FTP_CLIENT_USER_COMMAND_GET
        ,FTP_CLIENT_USER_COMMAND_GET_ARG
        ,FTP_CLIENT_USER_COMMAND_GET_ARG
        ,EMPTY_STRING
        ,FTP_CLIENT_USER_COMMAND_QUIT
        ,EMPTY_STRING
    );
}


void handleCommandUser(string username) {
    handleSimpleCommandResponse("USER " + username, true);
}


void handleCommandPassword(string password) {
    handleSimpleCommandResponse("PASS " + password, true);
}


void handleCommandDirectory() {
    enum pasvNextCmd pasvCmd = PASV_NLST;
    handlePassive(pasvCmd);

    if (isDataConnectionAvailable()) {
        handleNLST();
        disconnectDataConnection();
    }
}


void handleCommandPrintDirectory() {
    handleSimpleCommandResponse("PWD", false);
}


void handleCommandChangeDirectory(string path) {
    handleSimpleCommandResponse("CWD " + path, false);
}


void handleCommandChangeDirectoryUp() {
    handleSimpleCommandResponse("CDUP", false);
}


void handleCommandGetFile(string filename) {
    enum pasvNextCmd pasvCmd = PASV_RETR;
    handlePassive(pasvCmd);

    if (isDataConnectionAvailable()) {
        handleRETR(filename);
        disconnectDataConnection();
    }
}


void handleCommandQuit() {
    handleSimpleCommandResponse("QUIT", false);
    disconnectControlConnection();
    exit(0);
}


void handlePassive(pasvNextCmd pasvNext) {
    int sendLength = sendOnControl("PASV", 4);

    if (sendLength == -1) {
        printf("Failed to send PASV command.\n");
        return;
    }

    char messageArray[DATA_SOCKET_RECEIVE_BUFFER_SIZE + 1];

    int receiveLength = receiveOnControl(messageArray, DATA_SOCKET_RECEIVE_BUFFER_SIZE);

    if (receiveLength == -1) {
        printf("Failed to receive response to PASV command.\n");
        return;
    } else
    
    messageArray[receiveLength] = '\0';

    if (atoi(messageArray) == 227) {
        int hostPort;
        char hostIp[20];
        getHostIPAndPortFromPassiveSuccessResponse(messageArray, hostIp, hostPort);

        connectToServerData(hostIp, hostPort);

        receiveLength = receiveOnControl(messageArray, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
        messageArray[receiveLength] = '\0';

        if (receiveLength == -1) {
            cout << "Failed to receive response from data connection.";
        } else if (atoi(messageArray) >= 400) {
            showFtpResponse(messageArray);
        }

    } else {
        showFtpResponse(messageArray);
        if (atoi(messageArray) == 0) {
            cout << "Error: Response is not an FTP response...\n" ;
        } else if (atoi(messageArray) < 400) { // Unsuccessful response
            cout << "Error: Response is not a PASV success response...\n";
        } // else unsucessful response
    } 
}


void handleNLST() {
    int sendLength = sendOnControl("NLST", 4);
    if (sendLength == -1) {
        printf("Failed to send NLST command.\n");
        return;
    }

    char messageArray[DATA_SOCKET_RECEIVE_BUFFER_SIZE + 1];

    int receiveLength = receiveOnControl(messageArray, DATA_SOCKET_RECEIVE_BUFFER_SIZE);

    if (receiveLength == -1) {
        printf("Failed to receive response to NLST command.\n");
        return;
    }

    messageArray[receiveLength] = '\0';
    showFtpResponse(messageArray);

    while((errno = 0, (receiveLength = receiveOnData(messageArray, DATA_SOCKET_RECEIVE_BUFFER_SIZE)) > 0)) {
        if(receiveLength > 0) {
            messageArray[receiveLength] = '\0';
            showFtpDirResponse(messageArray);
        }
    } 

    if (receiveLength == -1) {
        printf("Failed to receive data from NLST command.\n");
    }
}


void handleRETR(string filename) {
    string retrCommand = "RETR " + filename;
    int sendLength = sendOnControl(retrCommand.c_str(), retrCommand.length());
    if (sendLength == -1) {
        printf("Failed to send command `%s`.\n", retrCommand.c_str());
        return;
    }

    char messageArray[DATA_SOCKET_RECEIVE_BUFFER_SIZE + 1];

    int receiveLength = receiveOnControl(messageArray, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
    if (receiveLength == -1) {
        printf("Failed to receive response to command `%s`.\n", retrCommand.c_str());
        return;
    }

    messageArray[receiveLength] = '\0';
    showFtpResponse(messageArray);
    

    if ((errno = 0, (receiveLength = receiveOnData(messageArray, DATA_SOCKET_RECEIVE_BUFFER_SIZE)) > 0)) {
        ofstream* outFile = new ofstream;
        outFile->open(filename.c_str(), ios_base::trunc);
        if (outFile->fail()) {
            printf("Failed to create file with name \"%s\"...\n", filename.c_str());
            return;
        }

        if(receiveLength > 0) {
            messageArray[receiveLength] = '\0';
            *outFile << messageArray;
        }

        while((errno = 0, (receiveLength = receiveOnData(messageArray, DATA_SOCKET_RECEIVE_BUFFER_SIZE)) > 0)) {
            if(receiveLength > 0) {
                messageArray[receiveLength] = '\0';
                *outFile << messageArray;
            }
        } 

        if (receiveLength == -1) {
            printf("Failed to receive data from `%s` command.\n", retrCommand.c_str());
            return;
        }

        outFile->close();
        delete(outFile);
    }


}


void handleSimpleCommandResponse(string ftpCommand, bool checkAuthentication) {
    int sendLength = sendOnControl(ftpCommand.c_str(), ftpCommand.length());
    if (sendLength == -1) {
        printf("Failed to send %s command.\n", ftpCommand.c_str());
        return;
    }

    char messageArray[DATA_SOCKET_RECEIVE_BUFFER_SIZE + 1];

    int receiveLength = receiveOnControl(messageArray, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
    if (receiveLength == -1) {
        printf("Failed to receive response to %s command.\n", ftpCommand.c_str());
        if (checkAuthentication) {
            exit(0);
        }
        return;
    } 
    
    messageArray[receiveLength] = '\0';

    showFtpResponse(messageArray);
    
    if (atoi(messageArray) >= 400 && checkAuthentication) {
        printf("Authentication unsuccessful: Exiting program...\n");
        exit(0);
    } else if (ftpCommand == "PWD" && atoi(messageArray) < 400) { // PWD response dpoesn't end in newline otherwise
        printf("\n");
    }
}


void getHostIPAndPortFromPassiveSuccessResponse(char* response, char* hostIp, int& hostPort) {
    string copyResponse = response;

    vector<int> extractedInts;
    stringstream ss;

    char *token = strtok(response, " ,()");

    while (token != NULL) {
        ss << token << " ";
        token = strtok(NULL, " ,()");
    }

    string temp;
    int foundInt;
    while (!ss.eof()) {
        ss >> temp;
        if (stringstream(temp) >> foundInt) {
            extractedInts.push_back(foundInt);
        }
        temp = "";
    }

    if (extractedInts.size() < 7) {
        cout << "Error: Passed response contains incorrect number of integers...\n" 
             << "Passed Response -> " << copyResponse << "\n";
        return;
    }

    sprintf(
        hostIp
        ,"%d.%d.%d.%d"
        ,extractedInts.at(1)
        ,extractedInts.at(2)
        ,extractedInts.at(3)
        ,extractedInts.at(4)
    );

    hostPort = extractedInts.at(5) * 256 + extractedInts.at(6);
}
