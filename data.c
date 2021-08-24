#include "data.h"
#include <stdlib.h>
#include "errors.h"
#include "string.h"


dataBlock_p createDataBlock(unsigned char* value, size_t size, char isStr){
    unsigned char* val; 
    dataBlock_p dataBlock;
    if (isStr == TRUE){
        val = malloc (sizeof(char) * size + 1);
        if (val == NULL){ errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
        val[size] = '\0';
    } else {
        val = malloc (sizeof(char) * size);
        if (val == NULL){ errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    }
    memcpy(val, value, size);
    dataBlock = malloc(sizeof(struct DataBlock));
    if (dataBlock == NULL){ errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    dataBlock -> value = val;
    dataBlock -> size = size; 
    dataBlock -> isStr = isStr;
    dataBlock -> next = NULL; 
    return dataBlock; 
} 

void freeDataBlock(dataBlock_p db_p){
    if (db_p == NULL){ return;}
    free(db_p -> value);
    free(db_p); 
}

void freeDataBlocks(dataBlock_p db_p){
    if (db_p != NULL && db_p->next != NULL){
        freeDataBlocks(db_p -> next); 
    }
    freeDataBlock(db_p);
}