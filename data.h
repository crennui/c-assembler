#ifndef DATA_SEGMENT
#define DATA_SEGMENT

#include "common.h"
#include <stdio.h>

struct DataBlock {
    size_t size;
    char isStr;
    unsigned char* value; 
    struct DataBlock* next; 
}; 
typedef struct DataBlock* dataBlock_p; 

dataBlock_p createDataBlock(unsigned char* value, size_t size, char isStr); 
void freeDataBlocks(dataBlock_p db_p);
void freeDataBlock(dataBlock_p db_p);

#endif