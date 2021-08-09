#ifndef COMMAND
#define COMMAND

#define MAX_LABEL_SIZE 32 
#define MAX_COMMAND_NAME_SIZE 10
#define COMMENT_PREFIX ';'
#define LABEL_SUFFIX = ':'
#define ARGUMENT_DELMITER

enum commandType {EmptyCommand, Data, Instruction, Comment}

struct Command {
	enum commandType; 
	char label[MAX_LABEL_SIZE];
	char commandName [MAX_COMMAND_NAME_SIZE]; 
	char * arguments; 
	int numOfArgs; 
}

typedef struct Command* commandp; 


/*Creates a new command struct, returns NULL if allocation failed.*/
commandp newCommand();

/*Parses the command line into a command struct.
  Returnes 0 if succeeded and error code otherwise.*/
int parseCommand(char * commandLine, command commandp); 

void freeCommand(command commandp);

#endif