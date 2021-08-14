#ifndef COMMANDS_TABLE
#define COMMANDS_TABLE


#include "hash_table.h"
#include "tu_mem.h"
#include "command.h"
#include "symbol_table.h"

struct AsmCommnad{
    enum commandType type; 
    void (*translator)(tuMem_p, symbols_p); /*change the return type from void to the command union object.*/
}; 
typedef struct AsmCommand * AsmCommnad_p;  

void initCommandsTable();

#endif