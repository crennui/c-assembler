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
			/*After processing the file, calling the file creation functions with currentFileTuMem if return status is ok*/
		} else {
			printf("%s\n","handaling errors ... "); 
		}
		/*After processing the file, calling the file creation functions with currentFileTuMem if return status is ok*/
		fclose(fp);
	}

	return 0;
}





