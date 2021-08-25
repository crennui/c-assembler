#ifndef TRANSLATION_UTILS
#define TRANSLATION_UTILS

#include <stdio.h>
/*The maximum command length is 80 and you need , for seperation so it will be less then 40 for sure*/
#define MAX_TOKENS 40

/*translates a string argumets with register to register number
  returns -1 if invalid.*/
int strToRegNum(char* source);

/*Allocates a new string that contains all chars between "" */
char* extractStr(char* str);

/*Converts course into an int that must be in the range of */
short strToImmed16Num(char* source);

/* Converts str to number, returns -1 and changes erroCode when invalid */
long strToNum(char* str);

/* Check the given number limits if fits 2 bytes returns TRUE or FALSE*/
char isValidShort(long num);

/* Check the given number limits if fits 1 byte returns TRUE or FALSE*/
char isValidByte(long num);

/* Check the given number limits if fits 4 bytes returns TRUE or FALSE*/
char isValidDW(long num); 

/* 
Modifies the given string word and removed whitespaces from start and end,
if more then one word is given, returns NULL*/
char* trimWord(char* str);

/*Tokenize the given args string according to configured delimiter
  delimiter cannot be on the start, end or have multiple delimiters in a row
  that is why I canno't use strtok. returns the number of arguments and -1 if invalid.*/
size_t tokenizeArgs(char* args, char** buffer, size_t buffetSize);

#endif