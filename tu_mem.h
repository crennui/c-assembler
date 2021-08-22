#ifndef TU_MEM
#define TU_MEM
#include "commands.h"
#include "data.h"
/*
This struct is representing all the nessecary output for a single .as file 
I call it "translation unit"

It holds the :
- code segment.
- data segment.
- counter (IC and DC).
- entries table. 
- external table.  
- symbol table ? 


The processing functions will use this struct to save their output and at the end 
this struct is used to output all the nessecary files for a specific .as file.    
*/
struct TuMem {
	int IC; 
	int DC; 
	command_p firstCommend; 
	dataBlock_p firstDataBlock; 
	command_p lastCommend; 
	dataBlock_p lastDataBlock; 
};

typedef struct TuMem* tuMem_p; 

tuMem_p newTuMem(); 

int appendInstruction(tuMem_p tm, command_p instruction); 
int appendData(tuMem_p tm, dataBlock_p dataBlock); 

#endif