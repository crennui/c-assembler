#ifndef DATA_SEGMENT
#define DATA_SEGMENT

struct DataBlock {

    char * value; 
    DataBlock* next; 
}; 
typedef struct DataBlock* dataBlock_p; 

void freeDataBlocks(dataBlock_p db_p);

#endif