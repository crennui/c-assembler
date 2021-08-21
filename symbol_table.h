#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include <stdlib.h>
#include "common.h"
#include "hash_table.h" 

static int CodeMusk = 1; 
static int EntryMusk = 2; 
static int ExternalMusk = 4;
static int DataMusk = 8; 

/*---------------------------------------*/
struct Symbol {
    char name[MAX_LABEL_SIZE];
    size_t location; 
    int attributes;  
}; 

typedef struct Symbol* symbol_p;
/*---------------------------------------*/

/*create new lable funcion*/
struct SymbolsTable {
    HashTable_p _private_table; 
    size_t _private_size; 
};

typedef struct SymbolsTable* symbolsTable_p; 

/*Allcates memory for a new Symbol*/
symbol_p newSymbol(char* name, size_t location, int attributes);

/*Allocates memory for a new symbolTable*/
symbolsTable_p newSymbolTable();

/*free table memory and all beneath*/
void freeSymbolTable(symbolsTable_p table);

/*Adds new symbol to table if symbol name is valid*/
int addSymbol(symbolsTable_p table, symbol_p);

/*returns a symbol pointer according to it's name*/
symbol_p getSymbol(symbolsTable_p table, char* name);

/*removes symbol entry from table accodring to its name*/
int removeSymbol(symbolsTable_p table, char* name);
/*---------------------------------------*/


#endif