#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "../include/ftp_client_ui.hpp"
#include "../include/ftp_client_control.hpp"
#include "../include/ftp_client_command.hpp"
using namespace std;

#define FTP_RESPONSE_MAX_LENGTH 1024


void usage(const char* prog);
char* baseName(const char* pathname);

int main(int argc, char** argv) {
    if (argc < 2) {
        char* base_name = baseName(argv[0]);
        usage(base_name);
        return 1;
    }
    
    char* serverIp = argv[1];
    int serverPort = FTP_CLIENT_DEFAULT_SERVER_PORT;
    
    if (argc > 2) {
        serverPort = atoi(argv[2]);
    }
    
    printf(
        "Server IP: %s\n"
        "Server Port: %d\n"
        ,serverIp
        ,serverPort
    );

    connectToServerControl(serverIp, serverPort);
    
    if (isControlConnectionAvailable()) {
        usleep(5000);

        char* response = new char[FTP_RESPONSE_MAX_LENGTH];
        memset(response, '\0', FTP_RESPONSE_MAX_LENGTH);
        if (receiveOnControl(response, FTP_RESPONSE_MAX_LENGTH) != -1) {
            showFtpResponse(response);
        }
        delete [] response;
        while(1) {
            getUserCommand();
        }
    }
    else {
        cout << "Can't connect to the FTP server\n";
    }
    return 0;
}

void usage(const char* prog) {
    printf(
        "      Usage:  %s  <server_ip>  <server_port>\n"
        "      ****************** <server_port> is optional.\n"
        ,prog
    );
}

char* baseName(const char* pathname) {
    char* path_name = const_cast<char*>(pathname);
    char* base_name = path_name;
    if ((base_name=strrchr(path_name, '/')) != NULL) {
        ++base_name;
    }
    return base_name;
}
