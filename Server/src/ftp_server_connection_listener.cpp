#include "../include/ftp_server_connection_listener.hpp"
#include "../include/ftp_server_net_util.hpp"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;


void startListenerSocket(char* port, 
                         int& listenerSockDescriptor, 
                         bool& succeeded) {
    
    struct sockaddr_in addressPort;
    addressPort.sin_family = AF_INET;
    addressPort.sin_addr.s_addr = INADDR_ANY;
    addressPort.sin_port = htons(atoi(port));
    
    listenerSockDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    succeeded = false;

    if (listenerSockDescriptor == 0) {
        printf("Socket failed...\n");
    } else if (bind(listenerSockDescriptor, (struct sockaddr *) &addressPort, sizeof(addressPort)) < 0) {
        printf("Bind failed...\n");
    } else if (listen(listenerSockDescriptor, MAX_PENDING_CONNECTIONS) < 0) {
        printf("Listen failed...\n");
    } else {
        succeeded = true;
        printf(
            "FTP server with IP address: %s is waiting at port: %s for connection.........\n"
            ,getHostIPAddress()
            ,port
        );
    }
}


bool isListenerSocketReady(int sockDescriptor, 
                           int timeoutSec, 
                           int timeoutUSec, 
                           bool& isError, 
                           bool& isTimedout) {
    return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
}


void acceptClientConnection(int listenerSockDescriptor, 
                            int& clientSockDescriptor) {
    struct sockaddr_in addressPort;
    int addrSize = sizeof(addressPort);

    clientSockDescriptor = accept(listenerSockDescriptor, (struct sockaddr *) &addressPort, (socklen_t *) &addrSize);

    if (clientSockDescriptor != -1) {
        printf("Client connection accepted....\n");
    }
}


void closeListenerSocket(int& listenerSockDescriptor) {
    closeSocket(listenerSockDescriptor);
}
