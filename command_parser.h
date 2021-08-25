#ifndef COMMAND_PARSER
#define COMMAND_PARSER
#include "commands_table.h"
#include "commands.h"
#include "common.h"

/*
The parsed commad describes one line commad splited into 3 main part that each command 
could have. LABEL, COMMAND and arguments. each command translation and argumet parsing 
is different and happens later. this struct make it easier the parse the command later and 
is used for the decision flow of the program, like knowing if a commad has a label or not before I need to know
if it is actualy a command. 
*/


/* Creates a new command struct, returns NULL if allocation failed.*/
parsedCommand_p newParsedCommand();

/*
  Parses the command line into a command struct.
  Returnes 0 if succeeded and error code otherwise.*/
int parseCommand(char * commandLine, parsedCommand_p command); 

/* Frees the allocated memory of a parsed command at all it's object */
void freeParsedCommand(parsedCommand_p command);

#endif