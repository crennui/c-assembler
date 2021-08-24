#ifndef TRANSLATORS
#define TRANSLATORS
#include "commands.h"
#include "data.h"
#include "symbol_table.h"


typedef command_p (*InstructionTranslator)(parsedCommand_p parsedCommand, int funct, int opcode,symbolsTable_p symbols, size_t location);
typedef dataBlock_p (*DataTranslator)(parsedCommand_p parsedCommand);

dataBlock_p dbTranslator(parsedCommand_p parsedCommand);
dataBlock_p dhTranslator(parsedCommand_p parsedCommand);
dataBlock_p dwTranslator(parsedCommand_p parsedCommand); 
dataBlock_p strTranslator(parsedCommand_p parsedCommand);

/*receives 3 registers on arguments*/
command_p arithmeticTranslator(parsedCommand_p parsedCommand,  int funct, int opcode, symbolsTable_p symbols, size_t location); 

/*receives 2 registers on arguments*/
command_p moveTranslator(parsedCommand_p parsedCommand, symbolsTable_p symbols); 

command_p copyTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location);

command_p arithmeticITranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location);

command_p cmpJmpTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location);

command_p loadingTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location);

command_p jmpTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location);

command_p oneLableTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location);

command_p stopTranslator(parsedCommand_p parsedCommand, int funct, int opcode, symbolsTable_p symbols, size_t location);
#endif
