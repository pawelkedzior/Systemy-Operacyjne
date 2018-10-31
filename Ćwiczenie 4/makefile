CC=gcc

all: glowny pisarz czytacz
	
glowny: pr1.c
	gcc pr1.c -o glowny.out -Wall -pedantic

pisarz: pisarz.c
	gcc pisarz.c -o pisarz.out -Wall -pedantic
	
czytacz: czytacz.c
	gcc czytacz.c -o czytacz.out -Wall -pedantic

clean:
	rm -f czytacz.out pisarz.out glowny.out

.PHONY: all clean
