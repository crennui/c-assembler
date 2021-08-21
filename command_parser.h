#ifndef COMMAND_PARSER
#define COMMAND_PARSER
#include "commands_table.h"
#include "common.h"

struct ParsedCommand {
	char label[MAX_LABEL_SIZE];
	char commandName [MAX_COMMAND_NAME_SIZE]; 
	char * arguments;  
	char hasLabel;
	char isEmptyOrCommet;  
};

typedef struct ParsedCommand* parsedCommand_p; 


/*Creates a new command struct, returns NULL if allocation failed.*/
parsedCommand_p newParsedCommand();

/*Parses the command line into a command struct.
  Returnes 0 if succeeded and error code otherwise.*/
int parseCommand(char * commandLine, parsedCommand_p command); 

void freeCommand(parsedCommand_p command);

#endif