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
	command -> hasLabel = FALSE; 
	return command; 
}


int parseCommand(char* commandLine, parsedCommand_p command ){
	char *labelSuffixP;
	int i=0, extractedValues = 0; 
	size_t lineLength = strlen(commandLine);
	for (i=0; i <  lineLength && isspace(commandLine[i]) != 0; i++){}

	if (commandLine[i] == COMMENT_PREFIX){
		command -> isEmptyOrCommet = TRUE;
		return 0;
	}
	if (i == lineLength){
		command -> isEmptyOrCommet = TRUE;
		return 0; 
	}

	labelSuffixP = strchr(commandLine, LABEL_SUFFIX);
	if (labelSuffixP == NULL){
		 extractedValues = sscanf(commandLine + i, "%s%[^*]", command -> commandName, command -> arguments); 

	} else {

		 extractedValues = sscanf(commandLine + i, "%[^:]:%s%[^*]", command -> label, command -> commandName , command -> arguments); 
		 command -> hasLabel = 1; 
	}

	if (extractedValues == EOF || extractedValues == -1){
		return -1; 
	}
	
	command -> isEmptyOrCommet = FALSE; 
	return 0; 

}



void freeParsedCommand(parsedCommand_p command){
	free(command);
}