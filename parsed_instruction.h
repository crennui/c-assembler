#ifndef COMMAND
#define COMMAND

#define MAX_LABEL_SIZE 32 
#define MAX_COMMAND_NAME_SIZE 10
#define COMMENT_PREFIX ';'
#define LABEL_SUFFIX ':'
#define ARGUMENT_DELMITER

/*Move this enum to the commands table and write */
enum commandType {EmptyCommand, Data, Instruction, Comment, Directive};

struct Command {
	enum commandType type;
	char label[MAX_LABEL_SIZE];
	char commandName [MAX_COMMAND_NAME_SIZE]; 
	char * arguments;  
	char hasLabel; 
};

typedef struct Command* command_p; 


/*Creates a new command struct, returns NULL if allocation failed.*/
command_p newCommand();

/*Parses the command line into a command struct.
  Returnes 0 if succeeded and error code otherwise.*/
int parseCommand(char * commandLine, command_p command); 

void freeCommand(command_p command);

#endif