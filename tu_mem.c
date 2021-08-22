#include "tu_mem.h"
#include <stdlib.h>
#include "errors.h"

tuMem_p newTuMem(){
    tuMem_p tm = malloc(sizeof(struct TuMem));
    if (tm != NULL){
        tm -> DC = 0;
        tm -> IC = 100;
        tm -> firstCommend = NULL; 
        tm -> lastCommend = NULL; 
        tm -> firstDataBlock = NULL; 
        tm -> lastDataBlock = NULL; 
    } else { errorCode = MEMORY_ALLOCATION_ERROR_CODE; }  
    return tm; 
}


int appendInstruction(tuMem_p tm, command_p instruction){
    if (tm -> IC + tm -> DC + SIZE_OF_INSTRUCTION > MEMORY_SIZE){ errorCode = OUT_OF_MEMORY; return -1; }
    if (tm->firstCommend == NULL){
        tm -> firstCommend = instruction;
        tm -> lastCommend = instruction; 
        tm -> IC += SIZE_OF_INSTRUCTION; 
        return 0; 
    }
    tm -> lastCommend->next = instruction; 
    tm -> lastCommend = instruction; 
    tm -> IC += SIZE_OF_INSTRUCTION; 
    return 0; 
}

int appendData(tuMem_p tm, dataBlock_p dataBlock){
    if (tm -> IC + tm -> DC + SIZE_OF_INSTRUCTION > MEMORY_SIZE){ errorCode = OUT_OF_MEMORY; return -1; }
    if (tm -> firstDataBlock == NULL){
        tm -> firstDataBlock = dataBlock; 
        tm -> lastDataBlock = dataBlock; 
        tm -> DC += dataBlock -> size; 
        return 0; 
    }
    tm -> lastDataBlock -> next = dataBlock; 
    tm -> lastDataBlock = dataBlock; 
    tm -> DC += dataBlock -> size; 
    return 0; 
}