#include <stdlib.h>
#include "command.h"

#define MAX_LABEL_SIZE 32 
#define MAX_COMMAND_NAME_SIZE 10
#define COMMENT_PREFIX ';'
#define LABEL_SUFFIX = ':'

/*Creates a new command struct, returns NULL if allocation failed.*/
commandp newCommand(){
	commandp command; 
	command = (commandp) malloc(sizeof(Command));
	if (command == NULL){
		return NULL; 
	}

	command -> commandType = EmptyCommand; 
	command -> label = NULL;
	command -> commandName = NULL; 
	command -> arguments = NULL; 
	command -> numOfArgs = 0; 
	return command; 
}

/*Parses the command line into a command struct.
  Returnes 0 if succeeded and error code otherwise.*/
int parseCommand(char * commandLine, int lineLength, command commandp){
	char c; 
	int i; 
	char label [MAX_LABEL_SIZE];
	char insideWordFlag = 0, isComment = 0;  
	char* commandStr, commandStrHead;
	char* arguments; 

	if (command == NULL) {return -1;}


	arguments = (char*)malloc(sizeof(char) * lineLength);
	if (arguments == NULL) {free(commandStr); return -1;}


	sscanf("%s:%[^*]", label, commandStr, arguments); 


	for (i=0 ; i < lineLength ; i++) {

			c = commandLine[i];

			if ((isspace(c) != 0 || c  == LABEL_SUFFIX) && insideWordFlag != 0){
					break;
			}
			if (isspace(c) == 0 && insideWordFlag == 0){
					insideWordFlag = 1;
					if (c == COMMENT_PREFIX) { iscommnet = 1;}
			}
			if (insideWordFlag != 0 && isspace(c) == 0){
				*commandStr = c; 
				commandStr++ 
			}
	}

	if (iscommnet != 0){
		command -> commandType = Comment; 
		return 0; 
	}

	if (insideWordFlag == 0 && (i + 1) == lineLength) {
		command -> commandType = EmptyCommand; 
		return 0; 
	}

	if (c == LABEL_SUFFIX) {
		strncpy(command -> label, commandLine, i+1); 

	} else {
		strncpy(command -> commandName, commandLine, i+1); 
	}



	return 0; 
}





int parseCommand(char* commandLine, int lineLength, command commandp){
	char labelSuffixP;
	int i, extractedValues = 0; 
	char * arguments; 
	char ** splitedArguments;
	char insideWordFlag = 0; 
	char lastchar; 

	for (i=0; i <  lineLength && isspace(commandLine[i]) != 0; i++){}

	if (commandLine[i] == COMMENT_PREFIX){
		command -> commandType = Comment;
		return 0;
	}
	if (i+1 == lineLength && isspace(commandLine[i]) != 0){
		command -> commandType = EmptyCommand;
		return 0; 
	}


	arguments = (char*)malloc(sizeof(char) * lineLength);
	if (arguments == NULL) {free(commandStr); return -1;}


	labelSuffixP = strchr(commandLine, LABEL_SUFFIX);
	if (labelSuffixP == NULL){
		 extractedValues = sscanf(commandLine + i, "%s%[^*]", command -> commandName, arguments); 

	} else {

		 extractedValues = sscanf(commandLine + i, "%[^:]:%s%[^*]", command -> label, command -> commandName , arguments); 
	}

	if (extractedValues == EOF || extractedValues == -1){
		return -1; 
	}
	
	command -> arguments = arguments; 
	return 0; 

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
