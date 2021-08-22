#include <stdlib.h>
#include <stdio.h>
#include "asm_processor.h"
#include "command_parser.h"
#include "symbol_table.h"
#include "errors.h"
#include "commands_table.h"
#include "hash_table.h"

int processFile(FILE* fp, tuMem_p tm, symbolsTable_p symbols){
    int status; 
    status = firstIteration(fp, tm, symbols); 
    if (status != 0) {return status;}
    fseek(fp, 0, SEEK_SET);
    status = secondIteration(fp, tm, symbols);
   return 0;
}


int firstIteration(FILE* fp, tuMem_p tm, symbolsTable_p symbols){
	char currentLine [MAX_LINE_SIZE + 1]; /*TODO check array is copied and not used. */
    int errorStatus = 0;
    int ic = 100, lineCounter = 0; 
    commandType type; 
    dataBlock_p currentDataBlock; 
    parsedCommand_p command;
    symbol_p currentSymbol; 
    
    while (fgets(currentLine, MAX_LINE_SIZE +1, fp) != NULL){
        lineCounter++; 
        command = newParsedCommand(); 
        if (command == NULL){/*TODO handler error code*/ return -1; }

        errorStatus = parseCommand(currentLine, command);
        if (errorStatus != 0){
            freeCommand(command);
            return errorStatus; 
        }
        if (command -> isEmptyOrCommet == TRUE){ continue; }
        type = getCommandType(command -> commandName); 
        if (command -> hasLabel == TRUE && type == Data) {
            currentSymbol = newSymbol(command->commandName, tm -> DC, DATA_MASK); 
            if (currentSymbol == NULL){printf("Couldn't create symbol"); continue; }
            errorStatus = addSymbol(symbols, currentSymbol, FALSE);
        }
          if (command -> hasLabel == TRUE && type == Instruction) {
            currentSymbol = newSymbol(command->commandName, ic, CODE_MASK); 
            if (currentSymbol == NULL){printf("Couldn't create symbol"); continue; }
            errorStatus = addSymbol(symbols, currentSymbol, FALSE);
        }        
        if (errorStatus != 0){printf("error ... "); continue; }
        switch(type){
            case Data:
                currentDataBlock =  translateData(command); 
                if (currentDataBlock == NULL ){ printf("Error parsing data"); continue;}
                errorStatus = appendData(tm, currentDataBlock); /*taranslate data should return the data block struct and receives only parsed command*/ 
                if (errorStatus != 0){ printf("Print the correct error"); continue; }
                break; 
            case Instruction:
                ic += SIZE_OF_INSTRUCTION; 
                break; 
            case Directive: /*TODO maybe split to entry and extern if it is entry ignore and continue*/
                break;
            default : 
                printf("Unknown command %s on line : %d \n", command -> commandName, lineCounter); 
                break;   
        }
        freeCommand(command); /*TODO change name to parse command*/
    }
    return 0; 
}


int secondIteration(FILE* fp, tuMem_p tm ,symbolsTable_p symbols){
    char currentLine [MAX_LINE_SIZE + 1];
    int lineCounter = 0, errorStatus = 0; 
    commandType type; 
    parsedCommand_p command;
    command_p currentInstruction; 

     while (fgets(currentLine, MAX_LINE_SIZE +1, fp) != NULL){
        lineCounter++; 
        command = newParsedCommand(); 
        if (command == NULL){/*TODO handler error code*/ return -1; }

        errorStatus = parseCommand(currentLine, command);
        if (errorStatus != 0){
            freeCommand(command);
            return errorStatus; 
        }
        if (command -> isEmptyOrCommet == TRUE){ continue; }
        type = getCommandType(command -> commandName); 

        if (type == Instruction){
            currentInstruction = translateInstruction(command, symbols);
            if (currentInstruction == NULL){ printf("couldn't translate instruction on line: %d\n", lineCounter); continue; }
            errorStatus = appendInstruction(tm, currentInstruction); /*TODO change function signature*/ 
        }
        if (type == Directive){ /*in case of the .entry command and maybe extern*/
            makeEntry(symbols, command -> arguments); /*TODO make sure it parses it correctly*/
        }
            
        if (errorStatus != 0){ printf("error...."); continue;}
     }
    return 0; 
}
