#ifndef TRANSLATION_UTILS
#define TRANSLATION_UTILS

#include <stdio.h>
/*The maximum command length is 80 and you need , for seperation so it will be less then 40 for sure*/
#define MAX_TOKENS 40

/*translates a string argumets with register to register number
  returns -1 if invalid.*/
int strToRegNum(char* source);

char* extractStr(char* str);

/*Converts course into an int that must be in the range of */
short strToImmed16Num(char* source);

long strToNum(char* str);

char isValidShort(long num);

char isValidByte(long num);

char isValidDW(long num); 

char* trimWord(char* str);
/*Tokenize the given args string according to configured delimiter
  delimiter cannot be on the start, end or have multiple delimiters in a row
  that is why I canno't use strtok. returns the number of arguments and -1 if invalid.*/
size_t tokenizeArgs(char* args, char** buffer, size_t buffetSize);




#endif