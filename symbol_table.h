#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include <stdlib.h>
#include "common.h"
#include "hash_table.h" 

#define CODE_MASK 1 
#define ENTRY_MASK 2 
#define EXTERNAL_MASK 4
#define DATA_MASK 8 


/*
The symbols table holds a hash table that maps between the symbol string into
a symbol struct with the necessary data.
*/

struct SymbolInstance{
    size_t address;
    struct SymbolInstance* next; 
}; 
typedef struct SymbolInstance* symbolInstance_p;
void freeInstances(symbolInstance_p instance);

struct Symbol {
    char name[MAX_LABEL_SIZE];
    size_t location; 
    int attributes; 
    symbolInstance_p instances; 
}; 

typedef struct Symbol* symbol_p;

/* Adds a new symbol Instanse into the symbol instances list. (used for external symbol)*/
int addSymbolInstance(symbol_p symbol, size_t address);

/*Frees a symbol struct and its fields*/
void freeSymbol(symbol_p symbol);


/* Creates new lable funcion*/
struct SymbolsTable {
    HashTable_p _private_table; 
    size_t _private_size; 
};

typedef struct SymbolsTable* symbolsTable_p; 

/*Allcates memory for a new Symbol*/
symbol_p newSymbol(const char* name, size_t location, int attributes);

/*Allocates memory for a new symbolTable*/
symbolsTable_p newSymbolTable();

/*free table memory and all beneath*/
void freeSymbolTable(symbolsTable_p table);

/*Adds new symbol to table if symbol name is valid*/
int addSymbol(symbolsTable_p symbolTable, symbol_p symbol, char allowDuplications);

/*returns a symbol pointer according to it's name*/
symbol_p getSymbol(symbolsTable_p table, char* name);

/*removes symbol entry from table accodring to its name*/
int removeSymbol(symbolsTable_p table, char* name);

/*Changes the symbol attributes field and turn on the Entry attribute flag*/
int makeEntry(symbolsTable_p table, char* name); 

/*Increases all location field of symbols in table that has the DATA attribute by ic*/
void increaseDataCounter(symbolsTable_p symbolsTable, size_t ic);
/*---------------------------------------*/


#endif