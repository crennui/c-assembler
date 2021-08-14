

#include "hash_table.h"
#include "tu_mem.h"
#include "command.h"
#include "symbol_table.h"
#include "commands_table.h"

static HashTable_p table; 



void initCommandsTable(){
    table = newHashTable();

    AsmCommnad_p add = {Instruction, NULL}; 
    put(table, "add", add);


}
