assembler : assembler.o
	gcc -Wall -pedantic -ansi -m32 -g --std=c90 assembler.c -o assembler
