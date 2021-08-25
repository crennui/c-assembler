#ifndef ASM_PROCESSOR
#define ASM_PROCESSOR
#include <stdio.h>
#include "tu_mem.h"
#include "symbol_table.h"
#include "common.h"

/*The function receives a File pointer, symbols table and a TuMem (translation unit memory) pointer 
  It updates the TuMem and symbols table according to the input file.
  The function returns 0 if no error accrued and error code otherwise.
  It uses the first and second iteration functions below */
int processFile(FILE* fp, tuMem_p tm, symbolsTable_p symbols);

/*The first iteration does two main thigs: 
  - builds the symbols table 
  - creates the dataBlocks and insert them into the tuMem
  at the end it updates the data symbols as should (+ Insruction counter)
  if fails, returns non 0 number; 
  */
int firstIteration(FILE* fp, tuMem_p tm, symbolsTable_p symbols);

/*
The second iteration uses the symbols table and the tranlators to create the commands
struct into tuMem, returns non 0 number if fails. 
*/
int secondIteration(FILE* fp, tuMem_p tm ,symbolsTable_p symbols);

#endif