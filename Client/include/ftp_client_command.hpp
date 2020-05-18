#ifndef FTP_CLIENT_COMMAND_H
#define FTP_CLIENT_COMMAND_H

#include <string>
using namespace std;

#define FTP_CLIENT_PROMPT "csci460Ftp>> "

#define FTP_COMMAND_MAX_LENGTH 512

#define FTP_CLIENT_USER_COMMAND_HELP "help"
#define FTP_CLIENT_USER_COMMAND_USER "user"
#define FTP_CLIENT_USER_COMMAND_USER_ARG "<username>"
#define FTP_CLIENT_USER_COMMAND_PASSWORD "pass"
#define FTP_CLIENT_USER_COMMAND_PASSWORD_ARG "<password>"
#define FTP_CLIENT_USER_COMMAND_DIRECTORY "dir"
#define FTP_CLIENT_USER_COMMAND_PRINT_DIRECTORY "pwd"
#define FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY "cwd"
#define FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_ARG "<dirname>"
#define FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_UP "cdup"
#define FTP_CLIENT_USER_COMMAND_GET "get"
#define FTP_CLIENT_USER_COMMAND_GET_ARG "<filename>"
#define FTP_CLIENT_USER_COMMAND_QUIT "quit"

#define FILE_OPEN_MODE "a"
#define DATA_SOCKET_RECEIVE_BUFFER_SIZE 65536 //64K


/**
 * @brief      Enumeration pasvNextCmd is used to pass parameter to function
 *             handlePassive() to keep track what will be the next command after
 *             the passive command.
 */
enum pasvNextCmd {
    PASV_NLST, 
    PASV_RETR
}; 


/**
 * @brief      Displays help information to the user terminal
 */
void handleCommandHelp();

/**
 * @brief      Sends a 'USER <username>' request meesage to the FTP Server.
 *             Receives response from FTP Server. Reacts and informs the user
 *             about the response. Calls function handleSimpleCommandResponse()
 *             with "checkAuthentication" parameter true to perform the
 *             activities mentioned above.
 *
 * @param[in]  username  Username of user to authenticate
 */
void handleCommandUser(string username);

/**
 * @author     Matthew Hird/Ezra MacDonald
 *
 * @brief      Sends a 'PASS <password>' request message to the FTP Server.
 *             Receives response from FTP Server. Reacts and informs the user
 *             about the response. Calls function handleSimpleCommandResponse()
 *             with "checkAuthentication" parameter true to perform the
 *             activities mentioned above.
 *
 * @param[in]  password  The password for the authenticated user
 */
void handleCommandPassword(string password);

/**
 *
 * @brief      First sends a 'PASV' request message to the FTP server. Receives
 *             the response against PASV request message from the server. If the
 *             response is a successful one, retrives data-connection listener
 *             port number form the response. Requests a data connection to the
 *             server on the listener port at the server. Calls function
 *             handlePassive() to perform the activities mentioned above. If the
 *             data connection is successful, sends a 'NLST' request message to
 *             the server on the control connection. Receives the response
 *             against NLST request from the server on the control connection.
 *             If the response is successful, retrieves the list of entries in
 *             server's current directory on the data connection. Displays the
 *             list of entries to the user. Calls function handleNLIST() to
 *             perform the activities mentioned above.
 */
void handleCommandDirectory();

/**
 *
 * @brief      Sends a 'PWD' request message to FTP Server. Receives the
 *             response from the server. If the response is successful, displays
 *             the name of the current working directory of the server. Calls
 *             function handleSimpleCommandResponse() with "checkAuthentication"
 *             parameter false to perform the activities mentioned above.
 */
void handleCommandPrintDirectory();

/**
 *
 * @brief      Sends a 'CWD <path>' request message to the FTP Server. Receives
 *             the response from the server and displays the response to the
 *             user. Calls function handleSimpleCommandResponse() with
 *             "checkAuthentication" parameter false to perform the activities
 *             mentioned above.
 *
 * @param[in]  path  Relative path of directory to change to
 */
void handleCommandChangeDirectory(string path);

/**
 *
 * @brief      Sends a 'CDUP' request message to FTP Server. Receives the
 *             response from the server and displays the response to the user.
 *             Calls function handleSimpleCommandResponse() with
 *             "checkAuthentication" parameter false to perform the activities
 *             mentioned above.
 */
void handleCommandChangeDirectoryUp();

/**
 *
 * @brief      First sends a 'PASV' request message to the FTP server. Receives
 *             the response against PASV request message from the server. If the
 *             response is a successful one, retrives data-connection listener
 *             port number form the response. Requests a data connection to the
 *             server on the listener port at the server. Calls function
 *             handlePassive() to perform the activities mentioned above. If the
 *             data connection is successful, sends a 'RETR <filename>' request
 *             message to the server on the control connection. Receives the
 *             response against RETR request from the server on the control
 *             connection. If the response is successful, retrieves the content
 *             of the file on the data connection. Saves the file in the local
 *             directory at the client computer. Calls function handleRETR() to
 *             perform the activities mentioned above.
 *
 * @param[in]  filename  The filename of the file to get
 */
void handleCommandGetFile(string filename);

/**
 * @brief      Sends a 'QUIT' request message to FTP Server. Calls function
 *             handleSimpleCommandResponse() with "checkAuthentication"
 *             parameter false to send 'QUIT' request message. Quits from the
 *             application.
 */
void handleCommandQuit();

/**
 * @brief      Sends a 'PASV' request message to the FTP server. Receives the
 *             response against PASV request message from the server. If the
 *             response is a successful one, retrives data-connection listener
 *             port number form the response. Retrives data-connection listener
 *             port number form the response using function
 *             getHostIPAndPortFromPassiveSuccessResponse(). Requests a data
 *             connection to the server on the listener port at the server.
 *
 * @param[in]  pasvNext  The pasv next
 *
 * @return     0  success; -1 if unsuccessful
 */
void handlePassive(pasvNextCmd pasvNext);

/**
 * @brief      Sends a 'NLST' request message to the server on the control
 *             connection. Receives the response against NLST request from the
 *             server on the control connection. If the response is successful,
 *             retrieves the list of entries in server's current directory on
 *             the data connection. Displays the list of entries to the user.
 */
void handleNLST();

/**
 * @brief      Sends a 'RETR <filename>' request message to the server on the
 *             control connection. Receives the response against RETR request
 *             from the server on the control connection. If the response is
 *             successful, retrieves the content of the file on the data
 *             connection. Saves the file in the local directory at the client
 *             computer.
 *
 * @param[in]  filename  The filename
 */
void handleRETR(string filename);

/**
 * @brief      Sends 'ftpCommand' request message to FTP server on the control
 *             connection. Receives the response from the server against the
 *             request. Displays the response to the user. If the response is
 *             unsuccessful and checkAuthentication parameter value is true,
 *             quits the application.
 *
 * @param[in]  ftpCommand           The ftp command
 * @param[in]  checkAuthentication  The check authentication
 */
void handleSimpleCommandResponse(string ftpCommand, bool checkAuthentication);

/**
 * @brief      Retrieves IP address of FTP Server from the response string into
 *             reference 'hostIp'. Retrives data-connection listening port
 *             number of FTP server from the response string into reference
 *             'hostPort'. The example of a successful response message is
 *             "227 Entering Passive Mode (192,168,1,65,202,143)." From the
 *             above response message 'hostIp' will be 192.168.1.65 and
 *             'hostPort' will be (202x256 + 143) or 51855.
 *
 * @param      response  The response
 * @param      hostIp    The host ip
 * @param      hostPort  The host port
 */
void getHostIPAndPortFromPassiveSuccessResponse(char* response, char* hostIp, int& hostPort);

#endif
