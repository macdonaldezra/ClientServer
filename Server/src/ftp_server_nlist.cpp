#include "../include/ftp_server_nlist.hpp"
#include "../include/ftp_server_connection.hpp"
#include "../include/ftp_server_response.hpp"

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <dirent.h>

using namespace std;


int listDirEntries(int dataSockDescriptor) {
    char* currentDirName = get_current_dir_name();
    int fileCount = 0;
    
    struct dirent* file;
    struct stat fileStat;

    char fileType;
    char lineItem[550];
    char dirList[(10 * FTP_RESPONSE_MAX_LENGTH) + 1];
    dirList[0] = '\0';
    char filePath[520];
    DIR* currentDir = opendir(currentDirName);
    while((file = readdir(currentDir)) != NULL)
    {
        sprintf(filePath, "%s/%s", currentDirName, file->d_name);
        stat(filePath, &fileStat);

        if (S_ISREG(fileStat.st_mode) == 1) {
            fileType = 'F';
        } else if (S_ISDIR(fileStat.st_mode) == 1) {
            fileType = 'D';
        } else if (S_ISLNK(fileStat.st_mode) == 1) {
            fileType = 'L';
        } else if (S_ISFIFO(fileStat.st_mode) == 1) {
            fileType = 'P';
        } else if (S_ISSOCK(fileStat.st_mode) == 1) {
            fileType = 'S';
        } else if (S_ISCHR(fileStat.st_mode) == 1) {
            fileType = 'C';
        } else if (S_ISBLK(fileStat.st_mode) == 1) {
            fileType = 'B';
        } else {
            fileType = '?';
        }

        sprintf(lineItem, "%c\t%-30s\t%zu\n", fileType, file->d_name, fileStat.st_size);
        strcat(dirList, lineItem);
        fileCount++;
    }
    closedir(currentDir);

    sendToRemote(dataSockDescriptor, dirList, strlen(dirList));

    return fileCount;
}
