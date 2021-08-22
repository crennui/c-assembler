#ifndef COMMANDS_TABLE
#define COMMANDS_TABLE

#include "hash_table.h"
#include "tu_mem.h"
#include "symbol_table.h"
#include "commands.h"
#include "data.h"

typedef enum commandType {Data = 1, Instruction = 2, Directive = 3} commandType; 
typedef command_p (*InstructionTranslator)(parsedCommand_p parsedCommand, symbolsTable_p symbols);
typedef dataBlock_p (*DataTranslator)(parsedCommand_p parsedCommand);

int initCommandsTable();


/*receives 3 registers on arguments*/
command_p arithmeticTranslator(parsedCommand_p parsedCommand, symbolsTable_p symbols); 

/*receives 2 registers on arguments*/
command_p moveTranslator(parsedCommand_p parsedCommand, symbolsTable_p symbols); 

typedef struct CommandHandler {
    InstructionTranslator translator; 
    int opcode;
    int funct; 
} commandHandler;

/**/
dataBlock_p translateData(parsedCommand_p parsedCommand);
/*This fucntion will get from the table the right commandHandler and will run 
  the translator if exists, will return the correct command_p with the correct opcode*/
command_p translateInstruction(parsedCommand_p parsedCommand, symbolsTable_p);

commandType getCommandType(const char* commandName); 

int destroy(int status); 
#endif