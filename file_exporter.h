#ifndef FILE_EXPORTER
#define FILE_EXPORTER

#include "tu_mem.h"
#include "symbol_table.h"
#define OB_FILE_SUFFIX ".ob"
#define BYTES_PER_LINE 4

/*This function should receive a translation unit memory struct that contains
  all the parsed commands and data and write it into a file called <fileName>.ob
  plus it will look at the symbols table, if entries exists it will write a file called 
  <fileName>.ent . if extern symbols exist it will write a file called <fileName>.ext
  with all the external symbols. returns -1 if fails and 0 if succeded.*/
int exportToFiles(char* fileName, tuMem_p translationUnit, symbol_p symbolsTable);
char* generateNewFileName(char* fileName, char* newSuffix);

#endif