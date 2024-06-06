.PHONY = clean

CC = gcc

all: mips.c
	${CC} -o programa mips.c
	./programa

run: programa
	./programa

clean:
	rm -f programa.o
