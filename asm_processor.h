#ifndef ASM_PROCESSOR
#define ASM_PROCESSOR
#include <stdio.h>
#include "tu_mem.h"
#include "symbol_table.h"
#include "common.h"

/*The function receives a File pointer and a TuMem (translation unit memory) pointer 
  It updates the TuMem according to the input file.
  The function returns 0 if no error accrued and error code otherwise. */
int processFile(FILE* fp, tuMem_p tm, symbolsTable_p symbols);
int firstIteration(FILE* fp, tuMem_p tm, symbolsTable_p symbols);
int secondIteration(FILE* fp, tuMem_p tm ,symbolsTable_p symbols);

#endif