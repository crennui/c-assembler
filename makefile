CC=gcc
SRC=$(wildcard *.c)
assembler : $(SRC)
	$(CC) -Wall -pedantic -ansi -m32 -g --std=c90 *.c *.h -o assembler


clean:
	rm *.o assembler 