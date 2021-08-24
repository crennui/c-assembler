#ifndef COMMAND_PARSER
#define COMMAND_PARSER
#include "commands_table.h"
#include "commands.h"
#include "common.h"


/*Creates a new command struct, returns NULL if allocation failed.*/
parsedCommand_p newParsedCommand();

/*Parses the command line into a command struct.
  Returnes 0 if succeeded and error code otherwise.*/
int parseCommand(char * commandLine, parsedCommand_p command); 

void freeParsedCommand(parsedCommand_p command);

#endif