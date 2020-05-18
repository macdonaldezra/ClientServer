#ifndef FTP_SERVER_CONNECTION_LISTENER_H
#define FTP_SERVER_CONNECTION_LISTENER_H

#define MAX_PENDING_CONNECTIONS 10


/**
 * @brief   Starts a listener socket that can listen for connection requests 
 *              from the remote computer.
 *
 * @param   port                    The port number.
 * @param   listenerSockDescriptor  The listener socket descriptor.
 * @param   succeeded               Set to true if listener is successfully 
 *                                      set up; set to false otherwise.
 */
void startListenerSocket(char* port, 
                         int& listenerSockDescriptor, 
                         bool& succeeded);


/**
 * @brief   Returns true if there is any remote connection request on the 
 *              listener socket represented by 'sockDescriptor'.
 *          Waits for a connection request for
 *              'timeoutSec' + 0.000001 * 'timeoutUsec' time.
 *          If no connection request has been received before the wait time 
 *              times out, sets 'isTimedout' value to 'true'.
 *          If any error occurs, sets 'isError' value to 'true'.
 *
 * @param   sockDescriptor  The socket descriptor.
 * @param   timeoutSec      The timeout seconds.
 * @param   timeoutUSec     The timeout microseconds.
 * @param   isError         Set to true if error occurs; false otherwise.
 * @param   isTimedout      Set to true if time out occurs; false otherwise.
 *
 * @return  True if there is any remote connection request on the listener 
 *              socket; false otherwise.
 */
bool isListenerSocketReady(int sockDescriptor, 
                           int timeoutSec, 
                           int timeoutUSec, 
                           bool& isError, 
                           bool&isTimedout);


/**
 * @brief   Accepts a connection request on the listener socket represented by 
 *              'listenerSockDescriptor'.
 *          Opens the connection to the remote computer and represents the 
 *              connection by 'clientSockDescriptor'.
 *
 * @param   listenerSockDescriptor  The listener socket descriptor.
 * @param   clientSockDescriptor    The client socket descriptor.
 */
void acceptClientConnection(int listenerSockDescriptor, 
                            int& clientSockDescriptor);


/**
 * @brief   Closes the listener socket represented by 'listenerSockDescriptor'.
 *
 * @param   listenerSockDescriptor  The listener socket descriptor.
 */
void closeListenerSocket(int& listenerSockDescriptor);

#endif
