assembler : assembler.o general_utils.o command.o
	gcc -Wall -pedantic -ansi -m32 -g --std=c90 assembler.c general_utils.h general_utils.c command.c command.h asm_processor.c asm_processor.h -o assembler
