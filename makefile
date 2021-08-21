CC=gcc
assembler : assembler.o general_utils.o command.o
	$(CC) -Wall -pedantic -ansi -m32 -g --std=c90 *.c *.h -o assembler


clean:
	rm *.o assembler 