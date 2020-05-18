#ifndef FTP_CLIENT_UI_H
#define FTP_CLIENT_UI_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;


/**
 * @brief      Displays prompt, parses user command from stdin, and interpretes
 *             the command.
 */
void getUserCommand();

/**
 * @brief      Interprets user command and call appropriate function from
 *             'ftp_client_command.hpp'.
 *
 * @param      command  User command
 */
void interpretUserCommand(vector<string> &command);

/**
 * @brief      Displays server response to the user on the prompt.
 *
 * @param      response  The response to display
 */
void showFtpResponse(string response); 

/**
 * @brief      Displays server response to the user against user command 'dir'.
 *
 * @param      response  The response to display
 */
void showFtpDirResponse(string response);

#endif
