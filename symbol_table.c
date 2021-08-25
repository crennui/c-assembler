#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "common.h"
#include "errors.h"
#include <ctype.h>

extern int errorCode;
/*Allcates memory for a new Symbol*/
symbol_p newSymbol(const char* name, size_t location, int attributes){ 
    symbol_p symbol; 
    size_t i = 0;
    /*validating label name*/
    if (isalpha(name[0]) == 0 ){errorCode = NOT_VALID_LABEL_ERROR_CODE; return NULL;}  
     while (name[i] != '\0'){
         if (isalpha(name[i]) == 0 && isdigit(name[i]) == 0){
             return NULL;
         }
         i++; 
    }
    symbol = malloc(sizeof(struct Symbol));
    if (symbol != NULL){ 
        strcpy(symbol->name, name);
        symbol -> location = location; 
        symbol -> attributes = attributes; 
        symbol -> instances = NULL;
    } else { errorCode = MEMORY_ALLOCATION_ERROR_CODE; }
    return symbol;  
}

void freeInstances(symbolInstance_p instance){
    if (instance == NULL){return;}
    if (instance->next != NULL){
        freeInstances(instance->next); 
    }
    free(instance);
}

symbolInstance_p newSymbolInstance(size_t address){
    symbolInstance_p newInstance = malloc(sizeof(struct SymbolInstance));
    if (newInstance == NULL){errorCode = MEMORY_ALLOCATION_ERROR_CODE; return NULL;}
    newInstance -> address = address;
    newInstance -> next = NULL; 
    return newInstance; 
}

int addSymbolInstance(symbol_p symbol, size_t address){
    symbolInstance_p newInstance = newSymbolInstance(address);
    symbolInstance_p tmp;
    if (newInstance == NULL){errorCode = MEMORY_ALLOCATION_ERROR_CODE; return -1;}
    if (symbol->instances == NULL){
        symbol->instances = newInstance;
        return 0;
    }
    tmp = symbol->instances; 
    while(tmp->next != NULL){ tmp = tmp->next;}
    tmp->next = newInstance; 
    return 0;
}

/*Allocates memory for a new symbolTable*/
symbolsTable_p newSymbolTable(){
    symbolsTable_p symbolsTable;
    HashTable_p table = newHashTable(); 
    if (table == NULL){ return NULL;}
    symbolsTable = malloc(sizeof(struct SymbolsTable));

    if (symbolsTable != NULL){
        symbolsTable ->_private_table = table;
        symbolsTable ->_private_size = 0;  
    }
    return symbolsTable; 
}

void freeSymbol(symbol_p symbol){
    if(symbol == NULL){return;}
    freeInstances(symbol->instances);
    free(symbol);
}

/*free table memory and all beneath*/
void freeSymbolTable(symbolsTable_p symbolsTable){
    Entry_p *bucket = symbolsTable -> _private_table-> buckets;
    size_t i;
    Entry_p currEntry;
    symbol_p currSymbol; 
    for (i=0;i<BUCKETS_IN_TABLE;i++){
        currEntry = bucket[i];
        while(currEntry != NULL){
            currSymbol = currEntry->value;
            freeSymbol(currSymbol);
            currEntry = currEntry->next;
        }
    }
    freeHashTable(symbolsTable -> _private_table);
    free(symbolsTable);
}

/*Adds new symbol to table if symbol name is valid*/
int addSymbol(symbolsTable_p symbolTable, symbol_p symbol, char shouldOverride){
    symbol_p tempSymbol; 
    tempSymbol = get(symbolTable -> _private_table, symbol-> name);
    if (tempSymbol != NULL && shouldOverride == FALSE) { return -1; }
    put(symbolTable -> _private_table, symbol-> name, symbol);
    return 0; 
}

/*returns a symbol pointer according to it's name*/
symbol_p getSymbol(symbolsTable_p symbolsTable, char* name){
    return get(symbolsTable ->_private_table, name);
}

/*removes symbol entry from table accodring to its name*/
int removeSymbol(symbolsTable_p symbolsTable, char* name){
    return removeEntry(symbolsTable -> _private_table, name);
}

int makeEntry(symbolsTable_p table, char* name){
    symbol_p  symbol = getSymbol(table, name);  
    if (symbol == NULL){ errorCode = LABEL_DOES_NOT_EXIST; return -1; }
    symbol -> attributes = (symbol -> attributes | ENTRY_MASK);
    return 0; 
}


void increaseDataCounter(symbolsTable_p symbolsTable, size_t ic){

   Entry_p *buckets = symbolsTable ->_private_table->buckets;
   size_t i;
   symbol_p currSymbol;
   Entry_p currEntry; 
   for (i=0; i<BUCKETS_IN_TABLE; i++){
       currEntry = buckets[i]; 
       while(currEntry != NULL){
           currSymbol = currEntry->value;
           if(((currSymbol->attributes) & DATA_MASK) > 0){
               currSymbol->location += ic;
           }
          currEntry = currEntry->next; 
       }
   }
}
/*---------------------------------------*/