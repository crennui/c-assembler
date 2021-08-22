#ifndef DATA_SEGMENT
#define DATA_SEGMENT

#include "common.h"
#include <stdio.h>

struct DataBlock {
    size_t size;
    char value [MAX_LINE_SIZE]; 
    struct DataBlock* next; 
}; 
typedef struct DataBlock* dataBlock_p; 

dataBlock_p createDataBlock(char* value, size_t size); 
void freeDataBlocks(dataBlock_p db_p);

#endif