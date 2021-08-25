#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "general_utils.h"
#include "asm_processor.h"
#include "tu_mem.h"
#include "symbol_table.h"
#include "errors.h"
#include "commands_table.h"
#include "file_exporter.h"

extern int errno; 
int errorCode = 0; 
	


/*
	This is the starting point of the project, high level explenation : 
	There are few main structs that hold the data. 
	- TuMem (translation unit memory): which holds all the commads and data declerations as linked lists
	each linked list has it's own struct type. (tu_mem.c file) 

	- symbols table:  which is using a hash table as it's main data stracture, <symbol name> -> symbol struct. 

	- Commands table: holds all that static mapping between the string command into it's command type and into the correct
	  "translator" (a function pointer that knows how to convert a parsedCommand struct into a command struct)


	The main function starts with reading the file names from agrv, initialize a symbols table and tuMem struct and passes them into 
	the process file function (in asm_processor.c file) which holds the first and second iteration logic. 
	when finised it calls the file exporter which knows how to convert the main data structs into the binary string and print it into a file.   	

	because of time limitations I didn't reach the error handlaing standart I wanted but I think you can still see that I am capable writing those
	parts in C. plus you might notice that the code style is trying to be simmilar to an OOP style.  
	And in most cases I write my comments in the header files and not in c files.
*/
int main (int argc, char *argv[]) {
	int i; 
	int status = 0;
	FILE *fp; 
	tuMem_p currentFileTuMem; 
	symbolsTable_p symbols;
	initCommandsTable(); 
	printf("Start error code is : %d\n", errorCode); 
	for (i=1; i < argc; i++)
	{
		if (endsWith(argv[i], FILE_SUFFIX) != 0)
		{
			printf("Invalid .as file : %s \n", argv[i]);
			continue; 
		}

		fp = fopen(argv[i], "r");

		if (fp == NULL){
			perror("Error : ");
			continue; 
		}

		symbols = newSymbolTable();
		if (symbols == NULL){ fclose(fp); continue;}
		currentFileTuMem = newTuMem(); 
		if (currentFileTuMem == NULL){ fclose(fp); freeSymbolTable(symbols);  continue;}

		printf("processing : %s ...\n", argv[i]); 
		if(processFile(fp, currentFileTuMem, symbols) == 0){
			printf("%s %s\n", "writing files for : ", argv[i]); 
			status = exportToFiles(argv[i], currentFileTuMem, symbols);
			if (status != 0){ printf("Error while exporting output files"); exit(-1);}
		} else {
			printf("%s\n","handaling errors ... "); 
		}
		freeSymbolTable(symbols);
		freeTuMem(currentFileTuMem);
		fclose(fp);
	}

	return 0;
}





