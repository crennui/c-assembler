#ifndef TU_MEM
#define TU_MEM
#include "commands.h"
#define INSTRUCTION_SIZE 4 
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
#define MEMORY_SIZE 33554432
struct TuMem {
	int IC; 
	int DC; 
	command_p firstCommend; 
	
	/*here I want an array of commands or linked list
	plus you want to */
};
typedef struct TuMem* tuMem_p; 

tuMem_p newTuMem(); 

int appendInstruction(); 
int appendData(); 
int appendLabel(); 

int updateInstruction(); 
int updateData(); 
int updateLable(); 

#endif