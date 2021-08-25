#ifndef COMMANDS
#define COMMANDS

#include "common.h"

#define R_COMMAND_TYPE 1
#define I_COMMAND_TYPE 2
#define J_COMMAND_TYPE 3

/*
    This file holds few structs the help to describe each command 
    - command type enum (self explenatory).
    - ParsedCommand is a general way the program parses one line and help for the desicion flow of the program.
    - There are bitfield structs that describes each command type 
    - all of the command type structs are in a union call General command so I can 
    - store each command without caring about it's type. 
*/

typedef enum {Data = 1, Instruction = 2, ExternDirective = 3, EntryDirective = 4} commandType; 

struct ParsedCommand {
	char label[MAX_LABEL_SIZE];
	char commandName [MAX_COMMAND_NAME_SIZE]; 
	char arguments [MAX_LINE_SIZE];  
	char hasLabel;
	char isEmptyOrCommet;  
};

typedef struct ParsedCommand* parsedCommand_p; 


typedef struct CommandR{
    unsigned int opcode : 6; 
    unsigned int rs : 5; 
    unsigned int rt: 5;
    unsigned int rd : 5;
    unsigned int funct : 5;
    unsigned int unused : 6;
} Command_r; 


typedef struct CommandI{
    unsigned int opcode : 6;
    unsigned int rs : 5;  
    unsigned int rt : 5; 
    unsigned int immed : 16; 
} Command_i; 


typedef struct CommandJ{
unsigned int opcode :6; 
unsigned int reg : 1; 
unsigned int address : 25; 
} Command_j; 

typedef union GeneralCommand {
    Command_r cmd_r;
    Command_i cmd_i;
    Command_j cmd_j;

} generalCommand;

struct Command{
    int commandType;
    generalCommand command; 
    struct Command* next; 
};
typedef struct Command* command_p; 

/* Allocates new memory for a Command struct, NULL if fails*/
command_p newCommand(); 

/*Frees one command node.*/
void freeCommand(command_p cmd);

/*Frees all command nodes the are connected this the given command node.*/
void freeCommands(command_p cmd); 


#endif