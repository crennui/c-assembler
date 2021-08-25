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
#define EXTERN_FILE_SUFFIX ".ext"
#define ENTRY_FILE_SUFFIX ".ent"

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
    char hexByteBuffer[4];
    size_t memory = CODE_SEGMENT_START; 
    size_t i, k;
    unsigned char* dataValue;
    unsigned int command32BitsInt = 0;
    unsigned int tmp = 0; 
    FILE *fptr;
    char header[20]; 
    command_p currentCommand; 
    generalCommand currentGeneralCommand; 
    dataBlock_p currentDataBlock;
    if (newFileOBName == NULL){ return -1; }
    fptr = fopen(newFileOBName, "w");
    if (fptr == NULL){ free(newFileOBName); return -1; }
    sprintf(header, "     %u %u      \n", translationUnit->IC-CODE_SEGMENT_START, translationUnit->DC);
    fputs(header, fptr);    
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
    
    currentDataBlock = translationUnit ->firstDataBlock;
    i = 0;
    k = 0;
    while (currentDataBlock != NULL){
        dataValue = currentDataBlock ->value;

        for(k = 0; k<currentDataBlock->size; k++, i++){
            if (i%SIZE_OF_INSTRUCTION == 0){ 
                if (i!=0){
                fputc('\n', fptr);
                memory+=SIZE_OF_INSTRUCTION;
                }
                sprintf(memoryStrBuffer, "%04d ",memory);
                fputs (memoryStrBuffer, fptr);
            }
            sprintf(hexByteBuffer, "%02X ", dataValue[k]);
            fputs(hexByteBuffer, fptr);
        }
        currentDataBlock = currentDataBlock->next;
    }
    fclose(fptr); 

    exportEntryFile(fileName, symbolsTable);
    exportExternFile(fileName, symbolsTable);
    return 0;
}


char exportExternFile(char* fileName, symbolsTable_p symbols){
    size_t i;
    char* newExternFileName = generateNewFileName(fileName, EXTERN_FILE_SUFFIX);
    char externLineBuffer[60];
    char hadExternFlag = FALSE;
    symbolInstance_p tmpInstance;
    Entry_p *buckets = symbols->_private_table->buckets;
    Entry_p currEntry; 
    symbol_p currSymbol;
    FILE *fptr;
    /*TODO make it less nested*/
    for(i=0;i<BUCKETS_IN_TABLE; i++){
        currEntry = buckets[i];
        while(currEntry != NULL){
            currSymbol = currEntry->value;
            if (((currSymbol->attributes)&EXTERNAL_MASK) > 0){
                if (hadExternFlag == FALSE){
                    fptr = fopen(newExternFileName, "w");
                    if(fptr == NULL){ free(newExternFileName); return -1;}
                    hadExternFlag = TRUE;
                    }
                tmpInstance = currSymbol->instances;
                while (tmpInstance != NULL){
                sprintf(externLineBuffer,"%s %04u\n" ,currSymbol->name, tmpInstance->address);
                fputs(externLineBuffer, fptr);
                tmpInstance = tmpInstance->next;
                }
            }
            currEntry = currEntry->next; 
        }
    }
    if (fptr != NULL){
        fclose(fptr);
    }
    return hadExternFlag;
}

char exportEntryFile(char* fileName, symbolsTable_p symbols){
    size_t i;
    char* newEntryFileName = generateNewFileName(fileName, ENTRY_FILE_SUFFIX);
    char entryLineBuffer[60];
    char hadEntryFlag = FALSE;
    Entry_p *buckets = symbols->_private_table->buckets;
    Entry_p currEntry; 
    symbol_p currSymbol;
    FILE *fptr;
    /*TODO make it less nested*/
    for(i=0;i<BUCKETS_IN_TABLE; i++){
        currEntry = buckets[i];
        while(currEntry != NULL){
            currSymbol = currEntry->value;
            if (((currSymbol->attributes)&ENTRY_MASK) > 0){
                if (hadEntryFlag == FALSE){
                    fptr = fopen(newEntryFileName, "w");
                    if(fptr == NULL){ free(newEntryFileName); return -1;}
                    hadEntryFlag = TRUE;
                    }

                sprintf(entryLineBuffer,"%s %04u\n" ,currSymbol->name, currSymbol->location);
                fputs(entryLineBuffer, fptr); 
            }
            currEntry = currEntry->next; 
        }
    }
    if (fptr != NULL){
        fclose(fptr);
    }
    return hadEntryFlag;
}