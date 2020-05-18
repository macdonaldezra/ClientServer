#include "../include/ftp_client_ui.hpp"
#include "../include/ftp_client_control.hpp"
#include "../include/ftp_client_command.hpp"
#include <string>
#include <iostream>

using namespace std;


void getUserCommand() {
    vector<string> command;
    string user_string;
    string argument;

    cout << FTP_CLIENT_PROMPT;
    getline(cin, user_string);

    for (char c : user_string) {
        if (c == ' ') {
            if (!argument.empty()) {
                command.push_back(argument);
                argument.clear();
            }
        } else {
            argument += string(1, c);
        }
    }

    if (!argument.empty()) {
        command.push_back(argument);
    }

    interpretUserCommand(command);
}


void interpretUserCommand(vector<string> &command) {
    int argCount = command.size();

    if (argCount == 0) {
        cout << "No command entered...\n";
    } else if (command.front() == FTP_CLIENT_USER_COMMAND_HELP) {
        handleCommandHelp();
    } else if (command.front() == FTP_CLIENT_USER_COMMAND_USER) {
        if (argCount > 1) {
            handleCommandUser(command.at(1));
        } else {
            printf(
                "%s requires the argument %s\n"
                ,FTP_CLIENT_USER_COMMAND_USER
                ,FTP_CLIENT_USER_COMMAND_USER_ARG
            );
        }
    } else if (command.front() == FTP_CLIENT_USER_COMMAND_PASSWORD) {
        if (argCount > 1) {
            handleCommandPassword(command.at(1));
        } else {
            printf(
                "%s requires the argument %s\n"
                ,FTP_CLIENT_USER_COMMAND_PASSWORD
                ,FTP_CLIENT_USER_COMMAND_PASSWORD_ARG
            );
        }
    } else if (command.front() == FTP_CLIENT_USER_COMMAND_PRINT_DIRECTORY) {
        handleCommandPrintDirectory();
    } else if (command.front() == FTP_CLIENT_USER_COMMAND_DIRECTORY) {
        handleCommandDirectory();
    } else if (command.front() == FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY) {
        if (argCount > 1) {
                    handleCommandChangeDirectory(command.at(1));
                } else {
                    printf(
                        "%s requires the argument %s\n"
                        ,FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY
                        ,FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_ARG
                    );
                }
    } else if (command.front() == FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_UP) {
        handleCommandChangeDirectoryUp();
    } else if (command.front() == FTP_CLIENT_USER_COMMAND_GET) {
        if (argCount > 1) {
            handleCommandGetFile(command.at(1));
        } else {
            printf(
                "%s requires the argument %s\n"
                ,FTP_CLIENT_USER_COMMAND_GET
                ,FTP_CLIENT_USER_COMMAND_GET_ARG
            );
        }
    } else if (command.front() == FTP_CLIENT_USER_COMMAND_QUIT) {
        handleCommandQuit();
    } else { // Invalid Command
        printf("Invalid ftp command...\n");
    } 
}


void showFtpResponse(string response) {
    cout << response;
}


void showFtpDirResponse(string response) {
    cout << response;
}
