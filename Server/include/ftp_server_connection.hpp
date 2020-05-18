#ifndef FTP_SERVER_CONNECTION_H
#define FTP_SERVER_CONNECTION_H


/**
 * @brief   Sends 'message' of length 'messageLength' to the remote computer 
 *              using a stream socket, represented by 'sockDescriptor'.
 *
 * @param   sockDescriptor  The socket descriptor.
 * @param   message         The message to send.
 * @param   messageLength   The message length.
 *
 * @return  The actual number of bytes sent; -1 if error occurs.
 */
int sendToRemote(int sockDescriptor, const char* message, int messageLength);


/**
 * @brief   Returns true if there is any remote connection request on the 
 *              stream socket represented by 'sockDescriptor'.
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
 * @return  True if there is any remote connection request on the stream
 *              socket; false otherwise.
 */
bool isConnectionReadyToRead(int sockDescriptor, 
                             int timeoutSec, 
                             int timeoutUSec, 
                             bool& isError, 
                             bool&isTimedout);


/**
 * @brief   Receives data from the remote computer using a stream socket, 
 *              represented by 'sockDescriptor'.
 *          Data is loaded into the buffer, 'message'.
 *
 * @param   sockDescriptor  The socket descriptor.
 * @param   message         The message buffer.
 * @param   messageLength   The length of the message buffer.
 *
 * @return  The number of bytes of data received.
 */
int receiveFromRemote(int sockDescriptor, char* message, int messageLength);


/**
 * @brief   Closes the stream socket, represented by 'sockDescriptor'.
 *
 * @param   sockDescriptor  The sock descriptor
 */
void closeConnection(int& sockDescriptor);


/**
 * @brief   Closes all the stream sockets, represented by 
 *              'controlSockDescriptor', 'dataListenerSockDescriptor', 
 *              and 'dataSockDescriptor'.
 *          Sets 'isClientConnected' to 'false'.
 *
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           Indicates if client connected.
 */
void closeAllConnections(int& controlSockDescriptor, 
                         int& dataListenerSockDescriptor, 
                         int& dataSockDescriptor, 
                         bool& isClientConnected);

#endif
