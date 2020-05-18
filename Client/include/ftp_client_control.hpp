#ifndef FTP_CLIENT_CONTROL_H
#define FTP_CLIENT_CONTROL_H

#define FTP_CLIENT_DEFAULT_SERVER_IP "127.0.0.1"
#define FTP_CLIENT_DEFAULT_SERVER_PORT 21
#define BUFFER_SIZE 512


/**
 * @brief      Sends control connection request on serverPort to a server
 *             whose address is given by IP address.
 *
 * @param      serverIp    The command server ip
 * @param      serverPort  The command server port
 */
void connectToServerControl(const char* serverIp, int serverPort);

/**
 * @brief      Sends data connection request on serverPort to a server
 *             whose address is given by IP address and sets isDataConnected.
 *
 * @param      serverIp    The data server ip
 * @param      serverPort  The data server port
 */
void connectToServerData(const char* serverIp, int serverPort);

/**
 * @brief      Sends the info in the buffer of length equal to 'length' on 
 *             control connection. Returns the actual number of bytes sent.
 *
 * @param      buffer  The message buffer
 * @param      length  The length of message to send
 *
 * @return     The number of bytes sent; -1 if error
 */
int sendOnControl(const char* buffer, int length);


/**
 * @brief      Sends the info in the buffer of length equal to 'length' on data 
 *             connection. Returns the actual number of bytes sent.
 *
 * @param      buffer  The message buffer
 * @param      length  The length of message to send
 *
 * @return     The number of bytes sent; -1 if error
 */
int sendOnData(const char* buffer, int length);


/**
 * @brief      Receives the info in the buffer of length equal to 'length' on 
 *             control connection. Returns the actual number of bytes received.
 *
 * @param      buffer  The message buffer
 * @param      length  The max size of buffer
 *
 * @return     The number of  bytes received; -1 if error; 0 if disconnected
 */
int receiveOnControl(char* buffer, int length);


/**
 * @brief      Receives buffer of length equal to 'length' on data connection
 *
 * @param      buffer  The message buffer
 * @param      length  The max size of buffer
 *
 * @return     The number of bytes recieved; -1 if error; 0 if disconnected
 */
int receiveOnData(char* buffer, int length);


/**
 * @brief      Closes the opened control connection and sets isControlConnected
 *             to false.
 */
void disconnectControlConnection();


/**
 * @brief      Closes the opened data connection and sets isDataConnected to 
 *             false.
 */
void disconnectDataConnection();


/**
 * @author     Matthew Hird
 * 
 * @brief      Determines if control connection available.
 *
 * @return     True if connected to command server; False otherwise.
 */
bool isControlConnectionAvailable();


/**
 * @brief      Determines if data connection available.
 *
 * @return     True if connected to data server; False otherwise.
 */
bool isDataConnectionAvailable();

#endif
