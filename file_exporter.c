#include "file_exporter.h"
#include "tu_mem.h"
#include "symbol_table.h"
#include "errors.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <string.h>
#include "data.h"
#include "commands.h"

#define NUM_CHARS_PER_BYTE 3

char* generateNewFileName(char* fileName, char* newSuffix){
    int fileNameLength = strlen(fileName); 
    char* newName = malloc(fileNameLength + 1 + strlen(newSuffix) - strlen(FILE_SUFFIX) );
    if (newName == NULL){ errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL;}
    strcpy(newName, fileName);
    strcpy(newName + fileNameLength - strlen(FILE_SUFFIX), newSuffix);  
    return newName;
}

/*This function should receive a translation unit memory struct that contains
  all the parsed commands and data and write it into a file called <fileName>.ob
  plus it will look at the symbols table, if entries exists it will write a file called 
  <fileName>.ent . if extern symbols exist it will write a file called <fileName>.ext
  with all the external symbols. returns -1 if fails and 0 if succeded.*/
int exportToFiles(char* fileName, tuMem_p translationUnit, symbolsTable_p symbolsTable){
    char* newFileOBName = generateNewFileName(fileName, OB_FILE_SUFFIX);
    unsigned char* currentCommandMem; 
    char instructionStrBuffer[SIZE_OF_INSTRUCTION * NUM_CHARS_PER_BYTE + 2];
    char memoryStrBuffer[8];
    size_t memory = 100; 
    int i;
    unsigned int command32BitsInt = 0;
    unsigned int tmp = 0; 
    FILE *fptr;
    command_p currentCommand; 
    generalCommand currentGeneralCommand; 
    dataBlock_p currentDataBlock;
    if (newFileOBName == NULL){ return -1; }
    fptr = fopen(newFileOBName, "w");
    if (fptr == NULL){ free(newFileOBName); return -1; }
    
    currentCommand = translationUnit -> firstCommend;

    while(currentCommand != NULL){
        currentGeneralCommand = currentCommand->command;
        switch (currentCommand -> commandType)
        {
        case R_COMMAND_TYPE:
            tmp = currentGeneralCommand.cmd_r.opcode; 
            command32BitsInt |=  (tmp << 26);
            tmp = currentGeneralCommand.cmd_r.rs;
            command32BitsInt |= (tmp << 21); 
            tmp = currentGeneralCommand.cmd_r.rt;
            command32BitsInt |= (tmp << 16);
            tmp = currentGeneralCommand.cmd_r.rd;
            command32BitsInt |= (tmp << 11); 
            tmp = currentGeneralCommand.cmd_r.funct;        
            command32BitsInt |= (tmp << 6); 
            tmp = currentGeneralCommand.cmd_r.unused;
            command32BitsInt |= (tmp);
            currentCommandMem = (unsigned char*)&command32BitsInt; 
            break; 
        case I_COMMAND_TYPE:
            tmp = currentGeneralCommand.cmd_i.opcode; 
            command32BitsInt |=  (tmp << 26);
            tmp = currentGeneralCommand.cmd_i.rs;
            command32BitsInt |= (tmp << 21); 
            tmp = currentGeneralCommand.cmd_i.rt;
            command32BitsInt |= (tmp << 16);
            tmp = currentGeneralCommand.cmd_i.immed;
            command32BitsInt |= (tmp);
            currentCommandMem = (unsigned char*)&command32BitsInt; 
            break;
        case J_COMMAND_TYPE:
            tmp = currentGeneralCommand.cmd_j.opcode; 
            command32BitsInt |=  (tmp << 26);
            tmp = currentGeneralCommand.cmd_j.reg;
            command32BitsInt |= (tmp << 25); 
            tmp = currentGeneralCommand.cmd_j.address;
            command32BitsInt |= (tmp);
            currentCommandMem = (unsigned char*)&command32BitsInt; 
            break;
        
        default:
            printf("Invalid command type\n");
            fclose(fptr);
            return -1;  
            break;
        }

        for (i = 0; i<SIZE_OF_INSTRUCTION ; i++){
            sprintf(&(instructionStrBuffer[i*NUM_CHARS_PER_BYTE]), "%02X ", currentCommandMem[i]);
        }
        instructionStrBuffer[i*NUM_CHARS_PER_BYTE] = '\n';
        instructionStrBuffer[i*NUM_CHARS_PER_BYTE+1] = '\0'; 
        sprintf(memoryStrBuffer, "%04d ",memory);
        fputs (memoryStrBuffer, fptr); 
        fputs(instructionStrBuffer, fptr); 
        command32BitsInt = 0; tmp = 0; 
        memory += SIZE_OF_INSTRUCTION; 
        currentCommand = currentCommand -> next;
    }
    
    fclose(fptr); 
    return 0;
}