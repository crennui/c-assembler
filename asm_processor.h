#ifndef ASM_PROCESSOR
#define ASM_PROCESSOR
#include <stdio.h>
#include "tu_mem.h"
#include "symbol_table.h"

#define MAX_LINE_SIZE 81
/*The function receives a File pointer and a TuMem (translation unit memory) pointer 
  It updates the TuMem according to the input file.
  The function returns 0 if no error accrued and error code otherwise. */
int processFile(FILE* fp, tuMem_p tm, symbolsTable_p symbols);

#endif