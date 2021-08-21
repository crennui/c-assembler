#ifndef COMMANDS_TABLE
#define COMMANDS_TABLE


#include "hash_table.h"
#include "tu_mem.h"
#include "symbol_table.h"
#include "commands.h"
#include "data.h"

typedef enum commandType {EmptyCommand, Data, Instruction, Comment, Directive} commandType; 

struct CommandHandler{
    commandType type; 
    command_p (*translator)(tuMem_p, symbolsTable_p);  /*change the return type from void to the command union object.*/ 
};

struct DataHandler {
    commandType type; 
    dataBlock_p dataBlock; 
};
typedef struct DataHandler * dataHandler_p; 


typedef struct CommandHandler * commandHandler_p;  

void initCommandsTable();


commandType getCommandType(char* commandName); 
#endif