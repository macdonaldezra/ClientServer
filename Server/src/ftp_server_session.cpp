#include "../include/ftp_server_session.hpp"
#include "../include/ftp_server_connection.hpp"
#include "../include/ftp_server_command.hpp"
#include "../include/ftp_server_response.hpp"

#include <iostream>
#include <cstring>
#include <unistd.h>

using namespace std;


void startClientFTPSession(int& controlSockDescriptor) {
    bool isClientConnected = true;
    bool isUser = false;
    bool isLoggedIn = false;
    int dataSocketDescriptor = -1;
    int dataListenerSockDescriptor = -1;
    char rootDir[200];

    getcwd(rootDir, sizeof(rootDir));

    bool isError = false;
    bool isTimedOut = false;

    sendToRemote(controlSockDescriptor, CONNECTED_RESPONSE, FTP_RESPONSE_MAX_LENGTH);
    char command[FTP_RESPONSE_MAX_LENGTH];

    while (isClientConnected) {
        if (isConnectionReadyToRead(controlSockDescriptor, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError, isTimedOut)) {
            memset(command, '\0', FTP_RESPONSE_MAX_LENGTH);
            receiveFromRemote(controlSockDescriptor, command, FTP_RESPONSE_MAX_LENGTH);
            printf("Received command: %s\n", command);
            interpreteCommand(
                command, 
                controlSockDescriptor, 
                dataListenerSockDescriptor, 
                dataSocketDescriptor, 
                isClientConnected, 
                isUser, 
                isLoggedIn,
                const_cast<char*>(rootDir)
            );
        } else {
            if (isTimedOut) {
                printf("Connection timed out.\n");
            } else if (isError) {
                printf("Connection error.\n");
            }
                sendToRemote(controlSockDescriptor, CONNECTION_RESET_BY_PEER, strlen(CONNECTION_RESET_BY_PEER));
                closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSocketDescriptor, isClientConnected);
        }
    }

}
