#ifndef FTP_SERVER_STR_UTIL_H
#define FTP_SERVER_STR_UTIL_H


/**
 * @brief      Replaces all the occurrences of 'find' character in 'str' with
 *             'replace' character.
 *
 * @param      str      String to search.
 * @param      find     Char to find and replace in 'str'.
 * @param      replace  Char to replace 'find' with in 'str'.
 */
void replaceCharWith(char* str, char find, char replace);


/**
 * @brief      Returns true if 'str' starts with 'prefix'.
 *
 * @param      prefix  Substring to find in 'str'.
 * @param      str     String being searched.
 *
 * @return     True if 'str' starts with 'prefix'; Otherwise False.
 */
bool startsWith(const char* prefix, const char* str);


/**
 * @brief      Changes all characters of 'str' to uppercase.
 *
 * @param      str   The string to turn uppercase.
 */
void toUpper(char* str);


/**
 * @brief      Removes all the spaces (' \t\n\v\f\r'), if there is any, from 
 *             the beginning of 'str'.
 *
 * @param      str   String to lstrip spaces from.
 *
 * @return     A copy of 'str' with spaces stripped from the start.
 */
char* stripSpaceAtStart(char* str);


/**
 * @brief      Removes newline character ('\n'), if there is any, from the end
 *             of 'str'.
 *
 * @param      str   String to have '\n' removed from its end.
 */
void stripNewlineAtEnd(char* str);

#endif
