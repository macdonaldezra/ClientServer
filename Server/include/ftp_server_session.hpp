#ifndef FTP_SERVER_SESSION_H
#define FTP_SERVER_SESSION_H

#define FTP_CLIENT_SESSION_TIMEOUT_SEC 600 // 10 minutes
#define FTP_CLIENT_SESSION_TIMEOUT_USEC 0


/**
 * @brief   Starts a client FTP session against a client control connection 
 *              represented by 'controlSockDescriptor'.
 *          Keeps track of the states of the session using various local 
 *              variables including 'controlSockDescriptor'.
 *          Waits for client's FTP request for 
 *              FTP_CLIENT_SESSION_TIMEOUT_SEC + 
 *              0.000001 * FTP_CLIENT_SESSION_TIMEOUT_USEC 
 *              time calling 'isConnectionReadyToRead()' function from 
 *              'ftp_server_connection.hpp'.
 *          If a request comes before the timeout, reads the request.
 *          Interprets the request, takes appropriate action, and sends 
 *              appropriate response to the client by calling 
 *              'interpreteCommand()' function from 'ftp_server.command.hpp'.
 *          If timeout or error happens before a FTP request comes, sends 
 *              an appropriate response to the client and closes all 
 *              connections calling 'closeAllConnections()' function 
 *              from 'ftp_server_connection.hpp'.
 *
 * @param   controlSockDescriptor  Client control connection socket descriptor.
 */
void startClientFTPSession(int& controlSockDescriptor);

#endif
