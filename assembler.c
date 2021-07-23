#include <stdio.h>

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



		in main all you want to have is the code where you get the command line arguments and call on each file the 

		Other files I need to make : 
		- update the make file 


	*/
int main () {
	int i = 0; 

	for (i=0; i< 5; i++){
		printf("%s%d\n", "hello world", i);
	}

	printf("%u \n", (unsigned int)sizeof(int));
	return 0;
}

