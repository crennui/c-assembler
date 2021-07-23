assembler : assembler.o general_utils.o
	gcc -Wall -pedantic -ansi -m32 -g --std=c90 assembler.c general_utils.h general_utils.c -o assembler
