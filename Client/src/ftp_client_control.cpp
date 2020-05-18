#include "../include/ftp_client_control.hpp"
#include "../include/ftp_client_connection.hpp"

int controlSocket = -1;
int dataSocket = -1;
bool isControlConnected = false; 
bool isDataConnected = false;


void connectToServerControl(const char* serverIp, int serverPort) {
    connectToServer(controlSocket, isControlConnected, serverIp, serverPort);
}
 
void connectToServerData(const char* serverIp, int serverPort) {
    connectToServer(dataSocket, isDataConnected, serverIp, serverPort);
}

int sendOnControl(const char* buffer, int length) {
    return sendToRemote(controlSocket, buffer, length);
}

int sendOnData(const char* buffer, int length) {
    return sendToRemote(dataSocket, buffer, length);
}

int receiveOnControl(char* buffer, int length) {
    return receiveFromRemote(controlSocket, buffer, length);
}

int receiveOnData(char* buffer, int length) {
    return receiveFromRemote(dataSocket, buffer, length);
}

void disconnectControlConnection() {
    if (isControlConnected) {
        disconnectFromServer(controlSocket, isControlConnected);
    }
}

void disconnectDataConnection() {
    if (isDataConnected) {
        disconnectFromServer(dataSocket, isDataConnected);
    }
}

bool isControlConnectionAvailable() {
    return isControlConnected;
}

bool isDataConnectionAvailable() {
    return isDataConnected;
}
