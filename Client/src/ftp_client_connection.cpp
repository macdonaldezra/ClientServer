#include "../include/ftp_client_connection.hpp"
#include <iostream>
#include <unistd.h> 
#include <sys/socket.h>
#include <arpa/inet.h> 

using namespace std;

void connectToServer(int& socketDescriptor, bool& isConnected, const char* serverIp, int serverPort) {
    int sock = 0;

    struct sockaddr_in serverAddress;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "\nSocket creation error.\n";
        return;
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverIp, &serverAddress.sin_addr) <= 0) {
        cout << "\nAddress not supported\n";
        return;
    }

    if (connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cout << "\nConnection failed\n";
        return;
    }

    socketDescriptor = sock;
    isConnected = true;
}

void disconnectFromServer(int& socketDescriptor, bool& isConnected) {
    close(socketDescriptor);
    isConnected = false;
}

int sendToRemote(int sockDescriptor, const char* message, int messageLength) {
    return send(sockDescriptor, message, messageLength, 0);
}

int receiveFromRemote(int sockDescriptor, char* message, int messageLength) {
    return recv(sockDescriptor, message, messageLength, 0);
}
