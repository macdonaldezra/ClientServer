#include "../include/ftp_server_net_util.hpp"


#include <iostream>
#include <cstring>
#include <sys/types.h> 
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <netdb.h> 

using namespace std;


void closeSocket(int& sockDescriptor) {
    close(sockDescriptor);
}


int getPortFromSocketDescriptor(int sockDescriptor) {
    struct sockaddr_in inputSocket;
    socklen_t socketLen = sizeof(sockaddr_in);
    if (getsockname(sockDescriptor, (struct sockaddr *) &inputSocket, &socketLen) == -1) {
        cout << "Unable to determine port number.\n";
        return -1;
    }
    return ntohs(inputSocket.sin_port);
}


bool isSocketReadyToRead(int sockDescriptor, int timeoutSec, int timeoutUSec, bool& isError, bool& isTimedout) {
    // instantiate time value for select operation
    struct timeval selTimeout;
    selTimeout.tv_sec = timeoutSec;
    selTimeout.tv_usec = timeoutUSec;

    fd_set read_fd_set;
    FD_ZERO(&read_fd_set);
    FD_SET(sockDescriptor, &read_fd_set);

    int connect = select(sockDescriptor+1, &read_fd_set, NULL, NULL, &selTimeout);
    if (connect == -1) {
        isError = true;
        return false;
    } else if (connect == 0) {
        isTimedout = true;
        return false;
    }

    return true;
} 


char* getHostIPAddress() {
    struct hostent* hostEntry;
    char hostArr[MAX_IP_ADDRESS_LENGTH];

    gethostname(hostArr, sizeof(hostArr));
    hostEntry = gethostbyname(hostArr);
    return inet_ntoa(*((struct in_addr *) hostEntry->h_addr_list[0])); 
}
