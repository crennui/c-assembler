#include "hash_table.h"
#include "tu_mem.h"
#include "commands_table.h"
#include "errors.h"

static HashTable_p CommandTypesTable; 
static HashTable_p CommandsTranslatorsTable; 
static HashTable_p DataTranslatorsTable;

static char Instructions [][MAX_COMMAND_NAME_SIZE] = {"add","sub","and","or","nor", "move", "mvhi", "mvlo", "addi", "subi", "andi", "ori", "nori", "beq", "bne", "blt", "bgt", "lb", "sb", "lw", "sw", "lh", "sh", "jmp", "la", "call", "stop"};
static char DataCommands [][MAX_COMMAND_NAME_SIZE] = {".dh", "dw", "db", ".asciz"}; 
static char Directives [][MAX_COMMAND_NAME_SIZE] = {".entry", ".extern"};

static commandHandler addHandler = {&arithmeticTranslator, 0, 0};

command_p arithmeticTranslator(parsedCommand_p parsedCommand, symbolsTable_p symbols){
    return NULL; 
}

int initCommandsTable(){
    int status = 0; 
    size_t i = 0; 

    CommandTypesTable = newHashTable(); 

    if (CommandTypesTable == NULL){ return -1; }
    
    for (i=0; i< sizeof(Instructions) / sizeof(Instructions[0]); i++){
        status = put (CommandTypesTable, Instructions[i], (void*)Instruction); 
        if (status != 0){ return destroy(-1);}
    }
     for (i=0; i< sizeof(DataCommands) / sizeof(DataCommands[0]); i++){
        status = put (CommandTypesTable, DataCommands[i], (void*)Data); 
        if (status != 0){ return destroy(-1);}
    }
       for (i=0; i< sizeof(Directives) / sizeof(Directives[0]); i++){
        status = put (CommandTypesTable, Directives[i], (void*)Directive); 
        if (status != 0){ return destroy(-1);}
    }

    CommandsTranslatorsTable = newHashTable();
    if (CommandsTranslatorsTable == NULL){ return destroy(-1); };

    put(CommandsTranslatorsTable, "add", &addHandler);

    DataTranslatorsTable = newHashTable(); 
    if (DataTranslatorsTable == NULL){ return destroy(-1); };
    return 0; 
}


int destroy(int status){
    if (CommandTypesTable != NULL){ freeHashTable(CommandTypesTable); }
    if (CommandsTranslatorsTable != NULL){ freeHashTable(CommandsTranslatorsTable); }
    if (DataTranslatorsTable != NULL){ freeHashTable(DataTranslatorsTable); }
    return status; 
}
commandType getCommandType(const char * name){
    return (commandType)get(CommandTypesTable, name);
}

dataBlock_p translateData(parsedCommand_p parsedCommand){
    return NULL; /*TODO implement*/
}
/*This fucntion will get from the table the right commandHandler and will run 
  the translator if exists, will return the correct command_p with the correct opcode*/
command_p translateInstruction(parsedCommand_p parsedCommand, symbolsTable_p symbols) {
    return NULL; /*TODO implement*/
}

