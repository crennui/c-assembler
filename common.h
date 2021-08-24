
#ifndef ASSEMBLER_COMMON
#define ASSEMBLER_COMMON

typedef int* dummy;

#define CODE_SEGMENT_START 100
#define FILE_SUFFIX ".as"
#define TRUE 1
#define FALSE 0
#define MAX_LABEL_SIZE 32 
#define MAX_COMMAND_NAME_SIZE 10
#define COMMENT_PREFIX ';'
#define LABEL_SUFFIX ':'
#define ARGUMENT_DELIMITER ','
#define STR_PRE_AND_POST '"'
#define SIZE_OF_INSTRUCTION 4
#define DECIMAL_BASE 10 
/*It is impossible to have more then 40. (line size - command) / 2 (because commas)*/
#define MAX_ARGUMENTS 40
#define MAX_LINE_SIZE 81
#define MAX_REGISTER_NUM 31
#define MEMORY_SIZE 33554432
#endif