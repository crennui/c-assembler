#include "hash_table.h"
#include "tu_mem.h"
#include "commands_table.h"
#include "errors.h"
#include "translation_utils.h"
#include "translators.h"

static HashTable_p CommandTypesTable; 
static HashTable_p CommandsTranslatorsTable; 
static HashTable_p DataTranslatorsTable;

static char Instructions [][MAX_COMMAND_NAME_SIZE] = {"add","sub","and","or","nor", "move", "mvhi", "mvlo", "addi", "subi", "andi", "ori", "nori", "beq", "bne", "blt", "bgt", "lb", "sb", "lw", "sw", "lh", "sh", "jmp", "la", "call", "stop"};
static char DataCommands [][MAX_COMMAND_NAME_SIZE] = {".dh", ".dw", ".db", ".asciz"}; 

static commandHandler addHandler = {&arithmeticTranslator, 0, 1};
static commandHandler subHandler = {&arithmeticTranslator, 0, 2};
static commandHandler andHandler = {&arithmeticTranslator, 0, 3};
static commandHandler orHandler = {&arithmeticTranslator, 0, 4};
static commandHandler norHandler = {&arithmeticTranslator, 0, 5};
static commandHandler moveHandler = {&copyTranslator, 1, 1};
static commandHandler mvhiHandler = {&copyTranslator, 1, 2};
static commandHandler mvloHandler = {&copyTranslator, 1, 3};
static commandHandler addiHandler = {&arithmeticITranslator, 10, -1};
static commandHandler subiHandler = {&arithmeticITranslator,11, -1};
static commandHandler andiHandler = {&arithmeticITranslator, 12, -1};
static commandHandler oriHandler = {&arithmeticITranslator, 13, -1};
static commandHandler noriHandler = {&arithmeticITranslator, 14, -1};
static commandHandler beqHandler = {&cmpJmpTranslator, 16, -1};
static commandHandler bneHandler = {&cmpJmpTranslator, 15, -1};
static commandHandler bltHandler = {&cmpJmpTranslator, 17, -1};
static commandHandler bgtHandler = {&cmpJmpTranslator, 18, -1};
static commandHandler lbHandler = {&loadingTranslator, 19, -1};
static commandHandler sbHandler = {&loadingTranslator, 20, -1};
static commandHandler lwHandler = {&loadingTranslator, 21, -1};
static commandHandler swHandler = {&loadingTranslator, 22, -1};
static commandHandler lhHandler = {&loadingTranslator, 23, -1};
static commandHandler shHandler = {&loadingTranslator, 24, -1};
static commandHandler jmpHandler = {&jmpTranslator, 30, -1};
static commandHandler laHandler = {&oneLableTranslator, 31, -1};
static commandHandler callHandler = {&oneLableTranslator, 32, -1};
static commandHandler stopHandler = {&stopTranslator, 63, -1};

static dataHandler dbHandler = {&dbTranslator};
static dataHandler dhHandler = {&dhTranslator};
static dataHandler dwHandler = {&dwTranslator}; 
static dataHandler strHandler = {&strTranslator}; 

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
    
    status = put (CommandTypesTable, ".entry", (void*)EntryDirective); 
    if (status != 0){ return destroy(-1);}
    status = put (CommandTypesTable, ".extern", (void*)ExternDirective); 
    if (status != 0){ return destroy(-1);}
    

    CommandsTranslatorsTable = newHashTable();
    if (CommandsTranslatorsTable == NULL){ return destroy(-1); };

    put(CommandsTranslatorsTable, "add", &addHandler);
    put(CommandsTranslatorsTable, "sub", &subHandler);
    put(CommandsTranslatorsTable, "and", &andHandler);
    put(CommandsTranslatorsTable, "or", &orHandler);
    put(CommandsTranslatorsTable, "nor", &norHandler);
    put(CommandsTranslatorsTable, "move", &moveHandler);
    put(CommandsTranslatorsTable, "mvhi", &mvhiHandler);
    put(CommandsTranslatorsTable, "mvlo", &mvloHandler);
    put(CommandsTranslatorsTable, "addi", &addiHandler);
    put(CommandsTranslatorsTable, "subi", &subiHandler);
    put(CommandsTranslatorsTable, "andi", &andiHandler);
    put(CommandsTranslatorsTable, "ori", &oriHandler);
    put(CommandsTranslatorsTable, "nori", &noriHandler);
    put(CommandsTranslatorsTable, "bne", &bneHandler);
    put(CommandsTranslatorsTable, "beq", &beqHandler);
    put(CommandsTranslatorsTable, "blt", &bltHandler);
    put(CommandsTranslatorsTable, "bgt", &bgtHandler);
    put(CommandsTranslatorsTable, "lb", &lbHandler);
    put(CommandsTranslatorsTable, "sb", &sbHandler);
    put(CommandsTranslatorsTable, "lw", &lwHandler);
    put(CommandsTranslatorsTable, "sw", &swHandler);
    put(CommandsTranslatorsTable, "lh", &lhHandler);
    put(CommandsTranslatorsTable, "sh", &shHandler);
    put(CommandsTranslatorsTable, "jmp", &jmpHandler);
    put(CommandsTranslatorsTable, "la", &laHandler);
    put(CommandsTranslatorsTable, "call", &callHandler);
    put(CommandsTranslatorsTable, "stop", &stopHandler);

    

    DataTranslatorsTable = newHashTable(); 
    if (DataTranslatorsTable == NULL){ return destroy(-1); };

    put (DataTranslatorsTable, ".db", &dbHandler);
    put (DataTranslatorsTable, ".dh", &dhHandler);
    put (DataTranslatorsTable, ".dw", &dwHandler);
    put (DataTranslatorsTable, ".asciz", &strHandler);
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
    dataHandler* t = (dataHandler*)get(DataTranslatorsTable, parsedCommand -> commandName); 
    if (t == NULL){errorCode = UNFAMILIAR_DATA_TYPE; return NULL; }
    return t->translator(parsedCommand);
}
/*This fucntion will get from the table the right commandHandler and will run 
  the translator if exists, will return the correct command_p with the correct opcode*/
command_p translateInstruction(parsedCommand_p parsedCommand, symbolsTable_p symbols, tuMem_p translationUnit){
    commandHandler* ch = get(CommandsTranslatorsTable, parsedCommand -> commandName); 
    return ch -> translator(parsedCommand, ch->funct, ch -> opcode, symbols, translationUnit->IC); 
}

