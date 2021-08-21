#include <stdlib.h>
#include <stdio.h>
#include "asm_processor.h"
#include "command_parser.h"
#include "symbol_table.h"

int processFile(FILE* fp, tuMem_p tm, symbolsTable_p symbols){
    int status; 
    status = firstIteration(fp, tm, symbols); 
    if (status != 0) {return status;}
    fseek(fp, 0, SEEK_SET);
    status = secondIteration(fp, tm, symbols);
    /*
    - creating new symbol table
    - first iteration.
    - second iteration.
    - write results.
    */
   return 0;
}


int firstIteration(FILE* fp, tuMem_p tm, symbolsTable_p symbols){ /*Add symbols table.*/
	char currentLine [MAX_LINE_SIZE + 1];
    int errorStatus = 0;
    parsedCommand_p command;
    
    while (fgets(currentLine, MAX_LINE_SIZE +1, fp) != NULL){
        command = newCommand(); 
        if (command == NULL){
            return -1; 
        }
        errorStatus = parseCommand(currentLine, command);
        if (errorStatus != 0){
            freeCommand(command);
            return errorStatus; 
        }
        
        if (command -> isEmptyOrCommet == TRUE){
            continue; 
        }


        /*Here I need to use the command object*/
    }
    return 0; 
}


int secondIteration(FILE* fp, tuMem_p tm ,symbolsTable_p symbols){
    return 0; 
}
