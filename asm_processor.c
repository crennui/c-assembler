#include <stdlib.h>
#include <stdio.h>
#include "asm_processor.h"
#include "command_parser.h"
#include "symbol_table.h"
#include "errors.h"
#include "commands_table.h"
#include "hash_table.h"
#include "translation_utils.h"

int processFile(FILE* fp, tuMem_p tm, symbolsTable_p symbols){
    int status; 
    status = firstIteration(fp, tm, symbols); 
    if (status != 0) {return status;}
    fseek(fp, 0, SEEK_SET);
    return secondIteration(fp, tm, symbols);
}


int firstIteration(FILE* fp, tuMem_p tm, symbolsTable_p symbols){
	char currentLine [MAX_LINE_SIZE + 1]; /*TODO check array is copied and not used. */
    int errorStatus = 0, lineCounter = 0;
    char* externLable; 
    char isValidRun = TRUE; 
    size_t ic = CODE_SEGMENT_START; 
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
            freeParsedCommand(command);
            return errorStatus; 
        }
        if (command -> isEmptyOrCommet == TRUE){ freeParsedCommand(command);  continue; }
        type = getCommandType(command -> commandName); 
        if (command -> hasLabel == TRUE && type == Data) {
            currentSymbol = newSymbol(command->label, tm -> DC, DATA_MASK); 
            if (currentSymbol == NULL){printf("Couldn't create symbol\n"); freeParsedCommand(command); continue; }
            errorStatus = addSymbol(symbols, currentSymbol, FALSE);
        }
          if (command -> hasLabel == TRUE && type == Instruction) {
            currentSymbol = newSymbol(command->label, ic, CODE_MASK); 
            if (currentSymbol == NULL){printf("Couldn't create symbol\n"); freeParsedCommand(command);  continue; }
            errorStatus = addSymbol(symbols, currentSymbol, FALSE);
        }        
    
        switch(type){
            case Data:
                currentDataBlock =  translateData(command); 
                if (currentDataBlock == NULL ){ printf("Error parsing data\n"); freeParsedCommand(command);  continue;}
                errorStatus = appendData(tm, currentDataBlock); /*taranslate data should return the data block struct and receives only parsed command*/ 
                if (errorStatus != 0){ printf("Print the correct error\n"); freeParsedCommand(command);  continue; }
                break; 
            case Instruction:
                ic += SIZE_OF_INSTRUCTION; 
                break; 
            case EntryDirective: 
                break;
            case ExternDirective:
                externLable = trimWord(command -> arguments);
                if (externLable == NULL){ printf("Not a valid label on line %d \n", lineCounter); isValidRun = FALSE;  freeParsedCommand(command); continue;}
                currentSymbol = newSymbol(externLable, 0, EXTERNAL_MASK); 
                if (currentSymbol == NULL){printf("Couldn't create symbol\n"); freeParsedCommand(command);  continue; }
                errorStatus = addSymbol(symbols, currentSymbol, FALSE);
                if (errorStatus != 0){ printf("Couldn't declare lablel %s extern on line %d \n", externLable, lineCounter); freeParsedCommand(command);  continue; }
                break; 
            default : 
                isValidRun = FALSE; 
                printf("Unknown command %s on line : %d \n", command -> commandName, lineCounter); 
                break;   
        }

        freeParsedCommand(command);
    }
    printf("%d\n", isValidRun);
    increaseDataCounter(symbols, ic);
    if (isValidRun != TRUE) {return -1;}
    return 0; 
}


int secondIteration(FILE* fp, tuMem_p tm ,symbolsTable_p symbols){
    char currentLine [MAX_LINE_SIZE + 1];
    int lineCounter = 0, errorStatus = 0; 
    char* tmpLabel; 
    char isValidRun = TRUE; 
    commandType type; 
    parsedCommand_p command;
    command_p currentInstruction; 

     while (fgets(currentLine, MAX_LINE_SIZE +1, fp) != NULL){
        lineCounter++; 
        command = newParsedCommand(); 
        if (command == NULL){/*TODO handler error code*/ return -1; }

        errorStatus = parseCommand(currentLine, command);
        if (errorStatus != 0){
            printf("Error while parsing command on line %d \n", lineCounter);
            isValidRun = FALSE; 
            freeParsedCommand(command);
            continue; 
        }
        if (command -> isEmptyOrCommet == TRUE){freeParsedCommand(command); continue; }
        type = getCommandType(command -> commandName); 

        if (type == Instruction){
            currentInstruction = translateInstruction(command, symbols, tm);
            if (currentInstruction == NULL){ printf("couldn't translate instruction on line: %d\n", lineCounter); isValidRun = FALSE;  freeParsedCommand(command); continue; }
            errorStatus = appendInstruction(tm, currentInstruction);
        }
        if (errorStatus != 0){
            printf("Error while reading instruction on line %d \n ", lineCounter);
            isValidRun = FALSE; 
            freeParsedCommand(command);
            continue; 
        }
 
        if (type == EntryDirective){ 
            tmpLabel = trimWord(command -> arguments);
            if (tmpLabel == NULL){ printf("Not a valid label on line %d \n", lineCounter); isValidRun = FALSE;  freeParsedCommand(command); continue;}
            errorStatus = makeEntry(symbols, tmpLabel);
            if (errorStatus != 0 ){printf("Error while making the lable %s as entry on line %d\n ", tmpLabel, lineCounter);}
        }
            
        if (errorStatus != 0){ isValidRun = FALSE;  freeParsedCommand(command); continue;}
     }
     printf("%d\n", isValidRun);
     if (isValidRun != TRUE){return -1;}
    return 0; 
}
