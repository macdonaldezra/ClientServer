#ifndef FTP_SERVER_PASSIVE_H
#define FTP_SERVER_PASSIVE_H

#define PASSIVE_DEFAULT_PORT "0"
#define DATA_CONNECTION_TIME_OUT_SEC 20
#define DATA_CONNECTION_TIME_OUT_USEC 0


/**
 * @brief   Starts a passive connection listener and sends an appropriate 
 *              response to the client.
 *          Waits for a specific time interval for the client to send 
 *              a connection request on the listener.
 *          Accepts client's connection request, if there is any, and opens 
 *              a data connection with the client.
 *          Closes the connection listener after opening the data connection
 *              with the client by calling 'closeListenerSocket()' function 
 *              from 'ftp_server_connection_listener.hpp'.
 *          Sends appropriate response to the client using control connection.
 *
 * @param   argument                       Unused.
 * @param   controlSockDescriptor          Control socket descriptor.
 * @param   passiveListenerSockDescriptor  Passive listener socket descriptor.
 * @param   dataSockDescriptor             Data sock descriptor.
 */
void enteringIntoPassive(char* argument, 
                         const int controlSockDescriptor, 
                         int& passiveListenerSockDescriptor, 
                         int& dataSockDescriptor);


/**
 * @brief   Starts a passive listener socket that can listen for connection 
 *              requests from the remote computer.
 *
 * @param   listenerSockDescriptor  The listener sock descriptor.
 * @param   succeeded               Set to true if successful; otherwise set 
 *                                      to false.
 */
void startPassiveListener(int& listenerSockDescriptor, bool& succeeded);


/**
 * @brief   Creates a Passive success response.
 *          Includes both the IP address and the port number into passive 
 *              success response according to RFC.    
 *
 * @param   response                       Buffer to put response into.
 * @param   passiveListenerSockDescriptor  The passive listener sock descriptor.
 */
void createPassiveSuccessResponse(char* response, 
                                  const int passiveListenerSockDescriptor);

#endif
