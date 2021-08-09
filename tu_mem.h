#ifndef TU_MEM
#define TU_MEM

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

struct TuMem {
	int IC; 
	int DC; 

};
typedef struct TuMem* tuMemp; 


int appendInstruction(); 
int appendData(); 
int appendLabel(); 

int updateInstruction(); 
int updateData(); 
int updateLable(); 

#endif