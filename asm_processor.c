#include <stdlib.h>
#include <stdio.h>
#include "asm_processor.h"
#include "parsed_instruction.h"


int processFile(FILE* fp, tuMem_p tu){
    /*
    - creating new symbol table
    - first iteration.
    - second iteration.
    */
}


int firstIteration(FILE* fp, tuMem_p tm){ /*Add symbols table.*/
	char currentLine [MAX_LINE_SIZE + 1];
    int errorStatus = 0;
    command_p command;
    
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
        
        /*Here I need to use the command object*/
    }

}


int secondIteration(FILE* fp, tuMem_p tm ){

}