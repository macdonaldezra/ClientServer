#ifndef FTP_SERVER_DATA_H
#define FTP_SERVER_DATA_H

#define FILE_OPEN_MODE "r"
#define DATA_SOCKET_SEND_BUFFER_SIZE 65536  // 64K


/**
 * @brief   Checks whether the file with the 'filename' is accessible or not.
 *          If the file is accessible, opens the file, then reads and sends 
 *              the file content chunk by chunk to the client.
 *          DATA_SOCKET_SEND_BUFFER_SIZE is used as the chunk size (in bytes).
 *          Sends file chunks using data connection represented by 
 *              'dataSockDescriptor'.
 *          Returns the total number of bytes sent to the client.
 *
 * @param   filename            The filename of the file in the current working
 *                                  directory to send to the client.
 * @param   dataSockDescriptor  The data connection socket descriptor.
 *
 * @return  The number of bytes sent over data conection; -1 if there was an 
 *              error in reading or sending the file (data not sent).)
 */
int sendFile(char* filename, int& dataSockDescriptor);

#endif