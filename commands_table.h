#ifndef COMMANDS_TABLE
#define COMMANDS_TABLE

#include "hash_table.h"
#include "tu_mem.h"
#include "symbol_table.h"
#include "commands.h"
#include "data.h"
#include "translators.h"

int initCommandsTable();

typedef struct CommandHandler {
    InstructionTranslator translator; 
    int opcode;
    int funct; 
} commandHandler;

typedef struct DataHandler{
  DataTranslator translator; 
} dataHandler; 

/**/
dataBlock_p translateData(parsedCommand_p parsedCommand);
/*This fucntion will get from the table the right commandHandler and will run 
  the translator if exists, will return the correct command_p with the correct opcode*/
command_p translateInstruction(parsedCommand_p parsedCommand, symbolsTable_p symbols, tuMem_p translationUnit);

commandType getCommandType(const char* commandName); 

int destroy(int status); 
#endif