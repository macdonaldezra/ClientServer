#include "../include/ftp_server_command.hpp"
#include "../include/ftp_server_connection.hpp"
#include "../include/ftp_server_passive.hpp"
#include "../include/ftp_server_nlist.hpp"
#include "../include/ftp_server_retrieve.hpp"
#include "../include/ftp_server_response.hpp"
#include "../include/ftp_server_string_util.hpp"

#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>

using namespace std;


#define FTP_RESPONSE_MAX_LENGTH 1024

#define COMMAND_BUFFER_SIZE 512
#define COMMAND_CODE_CHARACTER_COUNT 5
#define COMMAND_ARG_MAX_CHARACTER_COUNT 256
#define COMMAND_DELIMITER " "

#define PATH_NOT_ALLOWED_CURRENT_DIRECTORY "./"
#define PATH_NOT_ALLOWED_PARENT_DIRECTORY "../"


void interpreteCommand(char* commandLine, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isUser, 
                       bool& isLoggedIn, 
                       const char* rootDir) {

    char command[COMMAND_CODE_CHARACTER_COUNT];
    char argument[COMMAND_ARG_MAX_CHARACTER_COUNT];
    parseCommandLine(commandLine, command, argument);

    if (strcmp(command, COMMAND_USER) == 0) {
        handleCommandUSER(
            argument
            ,controlSockDescriptor
            ,dataListenerSockDescriptor
            ,dataSockDescriptor
            ,isClientConnected
            ,isUser
        );
    } else if (strcmp(command, COMMAND_PASSWORD) == 0) {
        handleCommandPASS(
            argument
            ,controlSockDescriptor
            ,dataListenerSockDescriptor
            ,dataSockDescriptor
            ,isClientConnected
            ,isUser
            ,isLoggedIn
        );
    } else if (strcmp(command, COMMAND_PWD) == 0) {
        handleCommandPWD(
            controlSockDescriptor
            ,dataListenerSockDescriptor
            ,dataSockDescriptor
            ,isClientConnected
            ,isLoggedIn
        );
    } else if (strcmp(command, COMMAND_CWD) == 0) {
        handleCommandCWD(
            argument
            ,controlSockDescriptor
            ,dataListenerSockDescriptor
            ,dataSockDescriptor
            ,isClientConnected
            ,isLoggedIn
        );
    } else if (strcmp(command, COMMAND_CDUP) == 0) {
        handleCommandCDUP(
            controlSockDescriptor
            ,dataListenerSockDescriptor
            ,dataSockDescriptor
            ,isClientConnected
            ,isLoggedIn
            ,rootDir
        );
    } else if (strcmp(command, COMMAND_PASV) == 0) {
        handleCommandPASV(
            argument
            ,controlSockDescriptor
            ,dataListenerSockDescriptor
            ,dataSockDescriptor
            ,isClientConnected
            ,isLoggedIn
        );
    } else if (strcmp(command, COMMAND_NLST) == 0) {
        handleCommandNLST(
            controlSockDescriptor
            ,dataListenerSockDescriptor
            ,dataSockDescriptor
            ,isClientConnected
            ,isLoggedIn
        );
    } else if (strcmp(command, COMMAND_RETR) == 0) {
        handleCommandRETR(
            argument
            ,controlSockDescriptor
            ,dataListenerSockDescriptor
            ,dataSockDescriptor
            ,isClientConnected
            ,isLoggedIn
        );
    } else if (strcmp(command, COMMAND_QUIT) == 0) {
        handleCommandQUIT(
            controlSockDescriptor
            ,dataListenerSockDescriptor
            ,dataSockDescriptor
            ,isClientConnected
        );
    } else {
        handleCommandUnSupported(controlSockDescriptor);
    }
}


void parseCommandLine(char* commandLine, char* command, char* argument) {
    int cmdIndex = 0;
    int argIndex = 0;
    int i = 0;

    command[0] = '\0';
    argument[0] = '\0';

    while (i < COMMAND_BUFFER_SIZE) {
        if (commandLine[i] == '\0') {
            if (cmdIndex != 0) {
                command[cmdIndex] = '\0';
            }
            break;
        } else if (commandLine[i] == ' ') {
            if (cmdIndex != 0) {
                command[cmdIndex] = '\0';
                i++;
                break;
            }
        } else {
            command[cmdIndex] = commandLine[i];
            cmdIndex++;
        }
        i++;
    }

    while (i < COMMAND_BUFFER_SIZE) {
        if (commandLine[i] == '\0') {
            if (argIndex != 0) {
                argument[argIndex] = '\0';
            }
            break;
        } else if (commandLine[i] == ' ') {
            if (argIndex != 0) {
                argument[argIndex] = '\0';
                i++;
                break;
            }
        } else {
            argument[argIndex] = commandLine[i];
            argIndex++;
        }
        i++;
    }
}


void handleCommandUSER(char* username, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isUser) {

    if (strcmp(username, DEFAULT_USERNAME) == 0) {
        isUser = true;
        sendToRemote(controlSockDescriptor, USERNAME_OK_RESPONSE, strlen(USERNAME_OK_RESPONSE));
    } else {
        printf("User UNAUTHORIZED.......\n");
        if (username[0] == '\0') {
            sendToRemote(controlSockDescriptor, UNSUPPORTED_COMMAND_RESPONSE, strlen(UNSUPPORTED_COMMAND_RESPONSE));
        } else {
            sendToRemote(controlSockDescriptor, INVALID_USERNAME_RESPONSE, strlen(INVALID_USERNAME_RESPONSE));
        }

        closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    }
}


void handleCommandPASS(char* password, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isUser, 
                       bool& isLoggedIn) {
    
    if (!isUser) {
        handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    } else if (strcmp(password, DEFAULT_PASSWORD) == 0) {
        isLoggedIn = true;
        sendToRemote(controlSockDescriptor, LOGIN_RESPONSE, strlen(LOGIN_RESPONSE));
    } else {
        handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    }
}


void handleCommandPWD(int& controlSockDescriptor, 
                      int& dataListenerSockDescriptor, 
                      int& dataSockDescriptor, 
                      bool& isClientConnected, 
                      bool& isLoggedIn) {

    if (!isLoggedIn) {
        handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    } else {
        char* currentDir = get_current_dir_name();
        sendToRemote(controlSockDescriptor, currentDir, strlen(currentDir));
        free(currentDir);
    }
}


void handleCommandCWD(char* directory, 
                      int& controlSockDescriptor, 
                      int& dataListenerSockDescriptor, 
                      int& dataSockDescriptor, 
                      bool& isClientConnected, 
                      bool& isLoggedIn) {

    if (!isLoggedIn) {
        handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    } else {
        if (startsWith(PATH_NOT_ALLOWED_CURRENT_DIRECTORY, directory) 
                || startsWith(PATH_NOT_ALLOWED_PARENT_DIRECTORY, directory)) {
            sendToRemote(controlSockDescriptor, CWD_FAIL_RESPONSE, strlen(CWD_FAIL_RESPONSE));
        } else {
            char* cur = get_current_dir_name();
            string currentDir = string(const_cast<char*>(cur)); 
            free(cur);
            if (chdir(currentDir.append("/").append(directory).c_str()) == -1) {
                sendToRemote(controlSockDescriptor, CWD_FAIL_RESPONSE, strlen(CWD_FAIL_RESPONSE));
            } else {
                sendToRemote(controlSockDescriptor, CHANGE_DIRECTORY_RESPONSE, strlen(CHANGE_DIRECTORY_RESPONSE));
            }
        }
    }
}


void handleCommandCDUP(int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isLoggedIn, 
                       const char* rootDir) {
    
    if (!isLoggedIn) {
        handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    } else {
        char* cur = get_current_dir_name();
        string currentDir = string(const_cast<char*>(cur));
        free(cur);
        int lastSlash = currentDir.find_last_of("/");

        if (lastSlash == -1 || !startsWith(rootDir, currentDir.substr(0, lastSlash).c_str())) {
            sendToRemote(controlSockDescriptor, CDUP_FAIL_RESPONSE, strlen(CDUP_FAIL_RESPONSE));
        } else {
            if (chdir(currentDir.append("/..").c_str()) == -1) {
                sendToRemote(controlSockDescriptor, CDUP_FAIL_RESPONSE, strlen(CDUP_FAIL_RESPONSE));
            } else {
                sendToRemote(
                    controlSockDescriptor, 
                    CHANGE_TO_PARENT_DIRECTORY_RESPONSE, 
                    strlen(CHANGE_TO_PARENT_DIRECTORY_RESPONSE)
                );
            }
        }
    }
}


void handleCommandPASV(char* argument, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isLoggedIn) {
    
    if (!isLoggedIn) {
        handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    } else {
        enteringIntoPassive(argument, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor);
    }
}


void handleCommandNLST(int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isLoggedIn) {
    
    if (!isLoggedIn) {
        handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    } else {
        if (dataSockDescriptor < 0) {
            sendToRemote(controlSockDescriptor, DATA_OPEN_CONNECTION_ERROR_RESPONSE, strlen(DATA_OPEN_CONNECTION_ERROR_RESPONSE));
            return;
        }
        int numFiles = listDirEntries(dataSockDescriptor);
        char sentByteBuffer[100];
        sprintf(sentByteBuffer, "Number of files: %d\n", numFiles);
        sendToRemote(controlSockDescriptor, sentByteBuffer, strlen(sentByteBuffer));          
        closeConnection(dataSockDescriptor);
    }
}


void handleCommandRETR(char* argument, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isLoggedIn) {
    
    if (!isLoggedIn) {
        handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    } else {
        if (dataSockDescriptor < 0) {
            sendToRemote(controlSockDescriptor, DATA_OPEN_CONNECTION_ERROR_RESPONSE, strlen(DATA_OPEN_CONNECTION_ERROR_RESPONSE));
            return;
        }

        int sentBytes = sendFile(argument, dataSockDescriptor);
        if (sentBytes == -1) {
            printf("%s does not exist.\n", argument);
            sendToRemote(controlSockDescriptor, INVALID_PATH_RESPONSE, strlen(INVALID_PATH_RESPONSE));            
        } else {
            char sentByteBuffer[100];
            sprintf(sentByteBuffer, "Bytes sent: %d\n", sentBytes);
            sendToRemote(controlSockDescriptor, sentByteBuffer, strlen(sentByteBuffer));            
        }
        closeConnection(dataSockDescriptor);
    }
}


void handleCommandQUIT(int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor,
                       bool& isClientConnected) {
    
    printf("Responding QUIT command.......\n");
    sendToRemote(controlSockDescriptor, QUIT_RESPONSE, strlen(QUIT_RESPONSE));
    closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
}


void handleCommandUnSupported(const int controlSockDescriptor) {
    sendToRemote(controlSockDescriptor, UNSUPPORTED_COMMAND_RESPONSE, strlen(UNSUPPORTED_COMMAND_RESPONSE));
}


void handleNotLoggedIn(int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected) {
    
    printf("Not logged in.......\n");
    sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, strlen(NOT_LOGGED_IN_RESPONSE));
    closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
}
