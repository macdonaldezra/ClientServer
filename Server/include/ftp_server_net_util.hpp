#ifndef FTP_SERVER_NET_UTIL_H
#define FTP_SERVER_NET_UTIL_H

#define MAX_IP_ADDRESS_LENGTH 1024


/**
 * @brief   Closes the stream socket, represented by 'sockDescriptor'.
 *
 * @param   sockDescriptor  The socket descriptor.
 */
void closeSocket(int& sockDescriptor);


/**
 * @brief   Determines and returns the associated port number from a given 
 *              socket descriptor.
 *
 * @param   sockDescriptor  The socket descriptor.
 *
 * @return  The port from socket descriptor; -1 on error.
 */
int getPortFromSocketDescriptor(int sockDescriptor);


/**
 * @brief   Returns true if there is any data sent by the remote computer on 
 *              the stream socket represented by 'sockDescriptor'.
 *          Waits for the data for 'timeoutSec' + 0.000001 * 'timeoutUsec' time.
 *          If no data has been sent before the wait time times out, sets 
 *              'isTimedout' value to 'true'.
 *          If any error occurs, sets 'isError' value to 'true'.
 *
 * @param   sockDescriptor  The sock descriptor.
 * @param   timeoutSec      The timeout seconds.
 * @param   timeoutUSec     The timeout microseconds.
 * @param   isError         Set to true if error occurs; otherwise false.
 * @param   isTimedout      Set to true if time out occurs; otherwise false.
 *
 * @return  True if there is any data sent by the remote computer; false if
 *              error or timeout occurs.
 */
bool isSocketReadyToRead(int sockDescriptor, 
                         int timeoutSec, 
                         int timeoutUSec, 
                         bool& isError, 
                         bool& isTimedout); 


/**
 * @brief   Determines and returns an IP address of the local host.
 *
 * @return  The host ip address.
 */
char* getHostIPAddress();

#endif
