#include "../include/ftp_server_passive.hpp"
#include "../include/ftp_server_connection_listener.hpp"
#include "../include/ftp_server_connection.hpp"
#include "../include/ftp_server_net_util.hpp"
#include "../include/ftp_server_command.hpp"
#include "../include/ftp_server_string_util.hpp"
#include "../include/ftp_server_response.hpp"

#include <iostream>
#include <cstring>

using namespace std;


void enteringIntoPassive(char* argument, 
                         const int controlSockDescriptor, 
                         int& passiveListenerSockDescriptor, 
                         int& dataSockDescriptor) {

    bool succeeded = false;
    startPassiveListener(passiveListenerSockDescriptor, succeeded);

    if (!succeeded) {
        sendToRemote(controlSockDescriptor, PASSIVE_ERROR_RESPONSE, strlen(PASSIVE_ERROR_RESPONSE));
    } else {
        char response[FTP_RESPONSE_MAX_LENGTH];
        createPassiveSuccessResponse(response, passiveListenerSockDescriptor);
        sendToRemote(controlSockDescriptor, response, strlen(response));

        bool isError = false;
        bool isTimedout = false;

        isListenerSocketReady(
            passiveListenerSockDescriptor, 
            DATA_CONNECTION_TIME_OUT_SEC, 
            DATA_CONNECTION_TIME_OUT_USEC, 
            isError, 
            isTimedout
        );

        if (isError) {
            sendToRemote(controlSockDescriptor, PASSIVE_ERROR_RESPONSE, strlen(PASSIVE_ERROR_RESPONSE));
        } else if (isTimedout) {
            sendToRemote(controlSockDescriptor, PASSIVE_ERROR_TIMEOUT_RESPONSE, strlen(PASSIVE_ERROR_TIMEOUT_RESPONSE));
        } else {
            acceptClientConnection(passiveListenerSockDescriptor, dataSockDescriptor);
            sendToRemote(controlSockDescriptor, DATA_CONNECTION_SUCCESS_RESPONSE, strlen(DATA_CONNECTION_SUCCESS_RESPONSE));
        }

        closeListenerSocket(passiveListenerSockDescriptor);
    }
}


void startPassiveListener(int& listenerSockDescriptor, bool& succeeded) {
    startListenerSocket(const_cast<char*>(PASSIVE_DEFAULT_PORT), listenerSockDescriptor, succeeded);
}

   
void createPassiveSuccessResponse(char* response, 
                                  const int passiveListenerSockDescriptor) {
    
    int portNumber = getPortFromSocketDescriptor(passiveListenerSockDescriptor);
    char* ipAddress = getHostIPAddress();
    replaceCharWith(ipAddress, '.', ',');
    
    int portHigh = portNumber >> 8;
    int portLow = portNumber - (portHigh << 8);

    sprintf(
        response
        ,PASSIVE_SUCCESS_RESPONSE
        ,ipAddress
        ,portHigh
        ,portLow
    );
}
