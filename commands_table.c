

#include "hash_table.h"
#include "tu_mem.h"
#include "commands_table.h"

static HashTable_p CommandTypesTable; 
static HashTable_p CommandsTable; 
static HashTable_p DataCommandsTable;

int initCommandsTable(){


    CommandTypesTable = newHashTable(); 

    if (CommandTypesTable == NULL){ return -1; }
    put (CommandTypesTable, "add", Instruction);
    put (CommandTypesTable, "sub", Instruction);
    put (CommandTypesTable, "add", Instruction);
    put (CommandTypesTable, "add", Instruction);
    put (CommandTypesTable, "add", Instruction);
    put (CommandTypesTable, "add", Instruction); 
    put (CommandTypesTable, "add", Instruction);
    put (CommandTypesTable, "add", Instruction);
    put (CommandTypesTable, "add", Instruction);
    put (CommandTypesTable, "add", Instruction);


    struct CommandHandler add = {Instruction, NULL}; 
    CommandsTable = newHashTable();
    put(CommandsTable, "add", &add);

    return 0; 
}
