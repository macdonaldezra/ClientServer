#include "../include/ftp_server_connection.hpp"
#include "../include/ftp_server_net_util.hpp"

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>

using namespace std;


int sendToRemote(int sockDescriptor, const char* message, int messageLength) {
    int bytesLeft = messageLength;
    int bytesSent;

    while((messageLength - bytesLeft) < messageLength) {
        bytesSent = send(sockDescriptor, message + messageLength - bytesLeft, bytesLeft, 0);
        if (bytesSent == -1) { 
            return -1;
        }
        bytesLeft -= bytesSent;
    }

    return messageLength - bytesLeft;
}


bool isConnectionReadyToRead(int sockDescriptor, int timeoutSec, int timeoutUSec, bool& isError, bool&isTimedout) {
    return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
}


int receiveFromRemote(int sockDescriptor, char* message, int messageLength) {
    return recv(sockDescriptor, message, messageLength, 0);
}


void closeConnection(int& sockDescriptor) {
    closeSocket(sockDescriptor);
}


void closeAllConnections(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected) {
    printf("Closing client's connections.......\n");
    closeConnection(controlSockDescriptor);
    closeConnection(dataListenerSockDescriptor);
    closeConnection(dataSockDescriptor);
    isClientConnected = false;
}
