#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parsed_instruction.h"



/*Creates a new command struct, returns NULL if allocation failed.*/
command_p newCommand(){
	command_p command; 
	command = (command_p) malloc(sizeof(struct Command));
	if (command == NULL){
		return NULL; 
	}
	command -> type = EmptyCommand; 
	command -> arguments = NULL; 
	command -> hasLabel = 0; 
	return command; 
}


int parseCommand(char* commandLine, command_p command ){
	char *labelSuffixP;
	int i, extractedValues = 0; 
	char * arguments; 
	size_t lineLength = strlen(commandLine);
	for (i=0; i <  lineLength && isspace(commandLine[i]) != 0; i++){}

	if (commandLine[i] == COMMENT_PREFIX){
		command -> type = Comment;
		return 0;
	}
	if (i+1 == lineLength && isspace(commandLine[i]) != 0){
		command -> type = EmptyCommand;
		return 0; 
	}


	arguments = (char*)malloc(sizeof(char) * lineLength);
	if (arguments == NULL) {return -1;}


	labelSuffixP = strchr(commandLine, LABEL_SUFFIX);
	if (labelSuffixP == NULL){
		 extractedValues = sscanf(commandLine + i, "%s%[^*]", command -> commandName, arguments); 

	} else {

		 extractedValues = sscanf(commandLine + i, "%[^:]:%s%[^*]", command -> label, command -> commandName , arguments); 
		 command -> hasLabel = 1; 
	}

	if (extractedValues == EOF || extractedValues == -1){
		return -1; 
	}
	
	command -> type = getCommandType(command -> commandName); /*TODO: Imlement this function in the commands table*/

	command -> arguments = arguments; 
	return 0; 

}



void freeCommand(command_p command){
	free(command -> arguments);
	free(command);
}
	/*
	i=0; 

	while (arguments[i] != NULL){

		if (insideWordFlag == 0 && isspace(arguments[i]) != 0){
			i++; 
			continue; 
		}

		if (insideWordFlag != 0 && isspace(arguments[i]) != 0){
			return -1; 

		i++; 
	}


	extracting arguments.
	  setting command struct. */
 

/*
char ** buildArgList(char * arguments){
	int i; 
	char lastcha, insideWordFlag;

	 char * token = strtok(string, " ");
   // loop through the string to extract all other tokens
   while( token != NULL ) {
   		while(){}
      printf( " %s\n", token ); //printing each token
      token = strtok(NULL, " ");
   }

}*/
