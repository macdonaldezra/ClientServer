#ifndef FTP_CLIENT_CONNECTION_H
#define FTP_CLIENT_CONNECTION_H


/**
 * @brief      Sends a connection request on severPort of a sever whose IP
 *             address is equal to serverIp. If a connection has been
 *             established as a result of the request sets the connection
 *             descriptor value to reference 'socketDescriptor' and sets
 *             reference 'isConnected' to true.
 *
 * @param      socketDescriptor  The socket descriptor
 * @param      isConnected       Indicates if connected
 * @param      serverIp          The server ip
 * @param      serverPort        The server port
 */
void connectToServer(int& socketDescriptor, bool& isConnected, const char* serverIp, int serverPort);

/**
 * @brief      Closes network connection represented by reference
 *             'socketDescriptor' and sets reference 'isConnected' to false.
 *
 * @param      socketDescriptor  The socket descriptor
 * @param      isConnected       Indicates if server is connected 
 */
void disconnectFromServer(int& socketDescriptor, bool& isConnected);

/**
 * @brief      Sends 'message' of length 'messageLength' bytes to the server on
 *             the network connection represented by 'sockDescriptor'.
 *
 * @param      sockDescriptor  The sock descriptor
 * @param      message         The message to send
 * @param      messageLength   The length of the message
 *
 * @return     Number of bytes sent; -1 if error
 */
int sendToRemote(int sockDescriptor, const char* message, int messageLength);

/**
 * @brief      Receives 'message' of length 'messageLength' bytes from the
 *             server on the network connection represented by 'sockDescriptor'.
 *
 * @param      sockDescriptor  The sock descriptor
 * @param      message         The message buffer
 * @param      messageLength   The maxsize of message buffer
 *
 * @return     The number of bytes actually received from remote; -1 if error; 
 *             0 if remote has closed the connection
 */
int receiveFromRemote(int sockDescriptor, char* message, int messageLength);

#endif