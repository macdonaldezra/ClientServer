#ifndef FTP_SERVER_COMMAND_H
#define FTP_SERVER_COMMAND_H

#define COMMAND_BUFFER_SIZE 512
#define COMMAND_CODE_CHARACTER_COUNT 5
#define COMMAND_ARG_MAX_CHARACTER_COUNT 256
#define COMMAND_DELIMITER " "

#define DEFAULT_USERNAME "csci460"
#define DEFAULT_USERNAME_LENGTH 7
#define DEFAULT_PASSWORD "460pass"
#define DEFAULT_PASSWORD_LENGTH 7

#define COMMAND_USER "USER"
#define COMMAND_PASSWORD "PASS"
#define COMMAND_PWD "PWD"
#define COMMAND_CWD "CWD"
#define COMMAND_CDUP "CDUP"
#define COMMAND_PASV "PASV"
#define COMMAND_NLST "NLST"
#define COMMAND_RETR "RETR"
#define COMMAND_QUIT "QUIT"

#define PATH_NOT_ALLOWED_CURRENT_DIRECTORY "./"
#define PATH_NOT_ALLOWED_PARENT_DIRECTORY "../"


/**
 * @brief   Interprets and handles command.
 *          Calls appropriate handling functions, passing the socket 
 *              descriptors and state variables.
 * 
 * @param   command                     The command to interpret.
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is currentlyconnected.
 * @param   isUser                      State variable; indicates if a valid 
 *                                          user has already been specified by
 *                                          the client.
 * @param   isLoggedIn                  State variable; indicates if client is
 *                                          currently logged in.
 * @param   rootDir                     The root directory of server program.
 */
void interpreteCommand(char* commandLine, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isUser, 
                       bool& isLoggedIn, 
                       const char* rootDir);


/**
 * @brief   Breaks the command line string that has been received through the 
 *              first argument 'commandLine' into its parts 'command' 
 *              and 'argument'.
 *          Assigns command part to reference parameter 'command' and argument
 *              part to reference parameter 'argument'.
 *          Caller retrieves the parts through the references ('command' 
 *              and 'argument').
 *
 * @param   commandLine  The full command.
 * @param   command      The command buffer.
 * @param   argument     The argument buffer.
 */
void parseCommandLine(char* commandLine, char* command, char* argument);


/**
 * @brief   Handles USER command by comparing 'username' with 
 *              the DEFAULT_USERNAME.
 *          If the 'username' matches, sets 'isUser' to True and sends 
 *              appropriate response to the client.
 *          If the 'username' does not match, sends appropriate response to 
 *              the client and closes all connections.
 *
 * @param   username                    The username.
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 * @param   isUser                      State variable; set to true if username
 *                                          matches DEFAULT_USERNAME.
 */
void handleCommandUSER(char* username, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isUser);


/**
 * @brief   Handles PASS command by comparing 'password' with the 
 *              DEFAULT_PASSWORD.
 *          If isUser is false, sends an appropriate response to the client and
 *              closes all connections.
 *          If the password matches, sets 'isLoggedIn' to True and sends 
 *              appropriate response to the client.
 *          If the password does not match, sends appropriate response to the 
 *              client and closes all connections.
 *
 * @param   password                    The password.
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 * @param   isUser                      State variable; indicates if a user 
 *                                          has been specified by the client.
 * @param   isLoggedIn                  State variable; set to true if isUser
 *                                          is true and if password matches 
 *                                          DEFAULT_PASSWORD.
 */
void handleCommandPASS(char* password, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isUser, 
                       bool& isLoggedIn);


/**
 * @brief   Handles PWD command.
 *          If isLoggedIn is false, sends an appropriate response to the client
 *              and closes all connections.
 *          If isLoggedIn is true, determines the current working directory and
 *              sends it to the client in an appropriate response.
 *
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 * @param   isLoggedIn                  State variable; indicates if a client 
 *                                          is logged in.
 */
void handleCommandPWD(int& controlSockDescriptor, 
                      int& dataListenerSockDescriptor, 
                      int& dataSockDescriptor, 
                      bool& isClientConnected, 
                      bool& isLoggedIn);


/**
 * @brief   Handles CWD command.
 *          If isLoggedIn is false, sends an appropriate response to the client
 *              and closes all connections.
 *          If isLoggedIn is true, determines whether the requested 'directory'
 *              is valid or not.
 *          A requested directory is valid only if it is a sub directory of the
 *              current working directory.
 *          If the requested directory is not a valid directory, sends an 
 *              appropriate response to the client.
 *          If the requested directory is valid, changes the current directory
 *              to the requested directory and sends an appropriate response 
 *              to the client.
 *
 * @param   directory                   The directory to change the current 
 *                                          directory to.
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 * @param   isLoggedIn                  State variable; indicates if a client 
 *                                          is logged in.
 */
void handleCommandCWD(char* directory, 
                      int& controlSockDescriptor, 
                      int& dataListenerSockDescriptor, 
                      int& dataSockDescriptor, 
                      bool& isClientConnected, 
                      bool& isLoggedIn);


/**
 * @brief   Handles CDUP command.
 *          If isLoggedIn is false, sends an appropriate response to the client
 *              and closes all connections.
 *          If isLoggedIn is true, determines whether moving up to the parent
 *              directory is not falling beyond the project's root directory.
 *          Project's root directory is passed in the last parameter 'rootDir'.
 *          If the move does not go beyond project's root directory, changes 
 *              the current working directory to the parent directory and sends
 *              an appropriate response to the client.
 *          If the the move goes beyond project's root directory, sends 
 *              an appropriate response to the client.
 *
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 * @param   isLoggedIn                  State variable; indicates if a client 
 *                                          is logged in.
 * @param   rootDir                     The server program's root directory.
 */
void handleCommandCDUP(int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isLoggedIn, 
                       const char* rootDir);


/**
 * @brief   Handles PASV command.
 *          If isLoggedIn is false, sends an appropriate response to the client
 *              and closes all connections.
 *          If the client is logged in, enters into passive mode.
 *          
 * @param   argument                    Unused.
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 * @param   isLoggedIn                  State variable; indicates if a client 
 *                                          is logged in.
 */
void handleCommandPASV(char* argument, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isLoggedIn);


/**
 * @brief   Handles NLST command.
 *          If isLoggedIn is false, sends an appropriate response to the client
 *              and closes all connections.
 *          If isLoggedIn is true, it checks whether the data connection has 
 *              already been established by a PASV command before this 
 *              NLST command.
 *          If a data connection has not been established, sends an 
 *              appropriate response to the user.
 *          If a data connection has already been established, prepares and 
 *              sends the list of current directory entries.
 *          Sends the count of entries in an appropriate response message to
 *              the client using the control connection.
 *          Closes the data connection.  
 *
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 * @param   isLoggedIn                  State variable; indicates if a client 
 *                                          is logged in.
 */
void handleCommandNLST(int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isLoggedIn);


/**
 * @brief   Handles RETR command.
 *          If isLoggedIn is false, sends an appropriate response to the client
 *              and closes all connections.
 *          If isLoggedIn is true, it checks whether the data connection has 
 *              already been established by a PASV command before this 
 *              RETR command.
 *          If a data connection has not been established, sends an appropriate
 *              response to the user.
 *          If a data connection has already been established, reads from the 
 *              file and sends the content of the file to the client on the 
 *              data connection.
 *          Sends the count of the bytes sent in an appropriate response 
 *              message to the client using the control connection.
 *          Closes the data connection.  
 *
 * @param   argument                    The file name of the file to send.
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 * @param   isLoggedIn                  State variable; indicates if a client 
 *                                          is logged in.
 */
void handleCommandRETR(char* argument, 
                       int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected, 
                       bool& isLoggedIn);


/**
 * @brief   Handles QUIT command by sending appropriate response to the client
 *              and closes all connections.
 *
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 */
void handleCommandQUIT(int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor,
                       bool& isClientConnected);


/**
 * @brief   Sends an appropriate response saying the requested command is 
 *              not supported by this FTP server.
 *
 * @param   controlSockDescriptor  The control socket descriptor.
 */
void handleCommandUnSupported(const int controlSockDescriptor);


/**
 * @brief   Sends an appropriate response saying the user is not logged in and
 *              closes all connections.
 *
 * @param   controlSockDescriptor       The control socket descriptor.
 * @param   dataListenerSockDescriptor  The data listener socket descriptor.
 * @param   dataSockDescriptor          The data socket descriptor.
 * @param   isClientConnected           State variable; indicates if a client 
 *                                          is connected.
 */
void handleNotLoggedIn(int& controlSockDescriptor, 
                       int& dataListenerSockDescriptor, 
                       int& dataSockDescriptor, 
                       bool& isClientConnected);

#endif
