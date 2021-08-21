#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "command_parser.h"
#include "common.h"

/*Creates a new command struct, returns NULL if allocation failed.*/
parsedCommand_p newParsedCommand(){
	parsedCommand_p command; 
	command = (parsedCommand_p) malloc(sizeof(struct ParsedCommand));
	if (command == NULL){
		return NULL; 
	}
	command -> isEmptyOrCommet = FALSE; 
	command -> arguments = NULL; 
	command -> hasLabel = FALSE; 
	return command; 
}


int parseCommand(char* commandLine, parsedCommand_p command ){
	char *labelSuffixP;
	int i, extractedValues = 0; 
	char * arguments; 
	size_t lineLength = strlen(commandLine);
	for (i=0; i <  lineLength && isspace(commandLine[i]) != 0; i++){}

	if (commandLine[i] == COMMENT_PREFIX){
		command -> isEmptyOrCommet = TRUE;
		return 0;
	}
	if (i+1 == lineLength && isspace(commandLine[i]) != 0){
		command -> isEmptyOrCommet = TRUE;
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
	
	command -> isEmptyOrCommet = FALSE; 
	command -> arguments = arguments; 
	return 0; 

}



void freeCommand(parsedCommand_p command){
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
