#include "translation_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "common.h"
#include <limits.h>
#include <errno.h>
#include <ctype.h>

/*translates a string argumets with register to register number
  returns -1 if invalid.*/
int strToRegNum(char* source){
    int result = -1; 
    char* buffer = malloc(sizeof(char) * strlen(source));  
    if (buffer == NULL){ errorCode=MEMORY_ALLOCATION_ERROR_CODE; return -1; }
    if (sscanf(source, "$%s", buffer) != 1) {errorCode = INVALID_REGISTER; return -1; };
    result = atoi(buffer);
    if (result >= 0 && result <= MAX_REGISTER_NUM){
        return result;
    } 
    return -1; 
}

/*Tokenize the given args string according to configured delimiter
  delimiter cannot be on the start, end or have multiple delimiters in a row.
  returns the number of arguments or -1 if invalid.*/
size_t tokenizeArgs(char* args, char** buffer, size_t bufferSize){
    size_t i=0, counter = 0; 
    char * token; 
    char last; 
    if (args == NULL || args[0] == '\0' || args[0] == ARGUMENT_DELIMITER || args[strlen(args)-1] == ARGUMENT_DELIMITER){
         errorCode = INVALID_ARGUMETS; return -1; }
    last = args[0]; 
    do{
        if (isspace(args[i]) != 0) {
            i++; 
            continue; 
        } else if (last == ARGUMENT_DELIMITER && args[i] == ARGUMENT_DELIMITER){
            errorCode = INVALID_ARGUMETS; 
            return -1; 
        } else {
            last = args[i]; 
        }
        i++; 
    } while(args[i] != '\0'); 


    token = strtok(args, " \t\n,");
   
    while( token != NULL && counter < bufferSize) {
      buffer[counter] = token;
      counter++;  
      token = strtok(NULL, " \t\n,");
   }
   if(counter == bufferSize && token != NULL){ errorCode = TOO_MANY_ARGUMENTS; return -1; }
   return counter; 
}


char* extractStr(char* str){
    char * start = strchr(str, STR_PRE_AND_POST); 
    char * end = strrchr(str, STR_PRE_AND_POST);
    int bytes = end - start -1; 
    char * result = malloc(sizeof(char) * bytes);
    if (result == NULL){ errorCode = MEMORY_ALLOCATION_ERROR_CODE ; return NULL; } 
    strncpy(result, start+1, bytes);
    return result;
}

char isValidShort(long num){
    if (num <= SHRT_MAX && num >= SHRT_MIN){
        return TRUE; 
    }
    return FALSE;
}

long strToNum(char* str){
     char* ptr; 
    long result; 
    int errTmp = errno;
    errno = 0;  
    result = strtol(str, &ptr, DECIMAL_BASE);
    if (result == 0 && errno != 0){ errorCode = INVALID_NUM_ARGUMENT; return -1; }
    errno = errTmp; 
    if (strlen(ptr) != 0) {errorCode = INVALID_NUM_ARGUMENT; return -1; }
    return result;
}



short strToImmed16Num(char* source){
    char* ptr; 
    long result; 
    int errTmp = errno;
    errno = 0;  
    result = (strtol(source, &ptr, DECIMAL_BASE));
    if (result == 0 && errno != 0){ errorCode = INVALID_NUM_ARGUMENT; return -1; }
    errno = errTmp; 
    if (strlen(ptr) != 0) {errorCode = INVALID_NUM_ARGUMENT; return -1; }
    if (isValidShort(result) == TRUE){
        return (short)result; 
    }
    return -1; 
}

/*Trims a work (changes the given buffer) returns NULL if more then one word or no words*/
char* trimWord(char* str){
    char * token;
    char * tmp;  
    token = strtok(str, " \t\n"); 
    if (token == NULL){ errorCode = INVALID_LABEL; return NULL; }
    tmp  = strtok(NULL, " \t\n");
    if (tmp != NULL){errorCode = INVALID_LABEL; return NULL;} /*it is not a word*/ 
    return token;
}

char isValidByte(long num){
    if (num <= CHAR_MAX && num >= CHAR_MIN){
        return TRUE; 
    }
    return FALSE;
}

char isValidDW(long num){
    if (num <= INT_MAX && num >= INT_MIN){
        return TRUE; 
    }
    return FALSE;
}