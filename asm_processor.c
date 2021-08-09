#include "asm_processor.h"



int processFile(fp *File, tm tuMemp){

}


int firstIteration(fp *File, tm tuMemp ){ /*Add symbols table.*/
	char * line = NULL;
	size_t len = 0; 
	ssize_t read; 

	while ((read = getline(&line, &len, fp)) != -1) {

		
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        if (line) free(line);
    }
}


int secondIteration(fp *File, tm tuMemp){

}