#include "../include/ftp_server_string_util.hpp"

#include <iostream>
#include <cstring> 

using namespace std;


void replaceCharWith(char* str, char find, char replace) {
    char* next = strchr(str, find);
    while (next != nullptr) {
        *next = replace;
        next = strchr(str, find);
    }
}


bool startsWith(const char* prefix, const char* str) {
    return str == strstr(str, prefix);
}


void toUpper(char* str) {
    while (*str != '\0') {
        *str = toupper(*str);
        str++;
    }
}


char* stripSpaceAtStart(char* str) {
    size_t trimCharCount;

    trimCharCount = strspn(str, "\t\n\v\f\r ");
    if (trimCharCount > 0) {
        size_t inputLength = strlen(str);
        if (trimCharCount == inputLength) {
            str[0] = '\0';
        }
        else {
            memmove(
                str, 
                str + trimCharCount, 
                inputLength + 1 - trimCharCount
            );
        }
    }
    return str;
}


void stripNewlineAtEnd(char* str) {
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}
