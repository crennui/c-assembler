#include "data.h"
#include <stdlib.h>
#include "errors.h"
#include "string.h"


dataBlock_p createDataBlock(char* value, size_t size){
    dataBlock_p dataBlock = malloc(sizeof(struct DataBlock));
    if (dataBlock == NULL){ errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL; }
    strcpy(dataBlock -> value, value);
    dataBlock -> size = size; 
    dataBlock -> next = NULL; 
    return dataBlock; 
} 

void freeDataBlocks(dataBlock_p db_p){
     free(db_p); 
}