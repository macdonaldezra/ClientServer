#ifndef FTP_SERVER_NLIST_H
#define FTP_SERVER_NLIST_H

#define DEFAULT_DIRECTORY_PATH "./"


/**
 * @brief   Determines and sends the list of current directory entries to 
 *              the client using the data connection, represented by 
 *              'dataSockDescriptor'.
 *          Returns the count of entries to the caller.
 *
 * @param   dataSockDescriptor  The data socket descriptor.
 *
 * @return  Number of entries in directory.
 */
int listDirEntries(int dataSockDescriptor);

#endif