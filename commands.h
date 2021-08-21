#ifndef COMMANDS
#define COMMANDS

#define R_COMMAND_TYPE 1
#define I_COMMAND_TYPE 2
#define J_COMMAND_TYPE 3


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
    unsigned int rt : 7; 
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

#endif