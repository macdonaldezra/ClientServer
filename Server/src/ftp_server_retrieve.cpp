#include "../include/ftp_server_retrieve.hpp"
#include "../include/ftp_server_connection.hpp"
#include "../include/ftp_server_response.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>

using namespace std;


int sendFile(char* filename, int& dataSockDescriptor) {
    char sendBuffer[DATA_SOCKET_SEND_BUFFER_SIZE];
    FILE *inFile = fopen(filename, FILE_OPEN_MODE);
    if (!inFile) {
        return -1;
    }

    int bytes;
    int totalSent = 0;
    while ( (bytes = fread(sendBuffer, 1, sizeof(sendBuffer), inFile)) > 0) {
        send(dataSockDescriptor, sendBuffer, bytes, 0);
        totalSent += bytes;
    }

    fclose(inFile);
    return totalSent;
}
