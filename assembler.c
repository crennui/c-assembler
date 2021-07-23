#include <stdio.h>
#include "general_utils.h"


#define FILE_SUFFIX ".as"
	/*	
		look at the design you did and see what do you really need to do and where to start ?

		you need a way to save the table of information of each essembly command. 
		
		you need to iterate on all the files, call a read file function and then 
		call the process file function. 
		as you designed the design should be that the process function will return a struct
        that contains 3 data structures : 
        - the memory.
        - the data segment.
        - the entry and export table. 
		
-----------------------------------------------------------------------

		here I am only iteating the files and calling the run asm_process function.
		and I get and error code and it should fill the correct data in the 
		tu_mem struct (that we also create on main). 
		after I create the tm_mem I am passing it to the asm_processor 
		the asm_processor should contain a symbol table and two main functions : 
		- first iteration. (fills the skeleton commands and the symbol table.)
			receives a file, read each line. call the command_parser to return a parsed command with flags like is empty and command type. 
			a lot of ifs  
			* check line type. 
				* has label. (the asm_processor will have a flag if symbol)
				* is data defenition 
		
			if command then call the command translator. receives the parsed command struct and returnes the the parsed 
			(we need command translator) returns the command binery code according to the command struct. (with or without label flag)
			here I want to use a map between the command id to it's translator function. long ass shit. 

			(data translator) (returns the binary code of the variable)  (I think linked list will be good here)

			return an error code and updates the tu_mem as should. (think about how are you going to call the update command on the second iteration)
			

		- second iteration. 
			The second iteration uses all the tu data that we collected from the first iteration and updates all missing 
			when updating on the second iteration I need somehow to use the symbol table to update the tu_mem struct. 

		

		after the two iterations you can convert the tu_mem into the real files. 
		which should be easier then this. 
		
		what is the order that we should work ? flow from start to finish ? down to up ? 
		start to finish is here. 
	
	
	first tasks : create the 
	*/

int main (int argc, char *argv[]) {
	int i; 

	for (i=1; i < argc; i++)
	{
		if (endsWith(argv[i], FILE_SUFFIX) != 0)
		{
			printf("Invalid asm file : %s \n", argv[i]);
			continue; 
		} 
		printf("processing : %s ...\n", argv[i]); 
	}

	return 0;
}

