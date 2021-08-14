#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include "command.h" 
#include <stdlib.h>

int CodeMusk = 1; 
int EntryMusk = 2; 
int ExternalMusk = 4;
int DataMusk = 8; 

/*---------------------------------------*/
struct Label {
    char * name;
    size_t value; 
    int attributes = 0;  
}; 

typedef struct Label* label_p;
/*---------------------------------------*/

/*---------------------------------------*/
struct Symbols {

}; 

typedef struct Symbols* symbols_p; 
/*---------------------------------------*/


#endif