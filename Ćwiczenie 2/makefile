CC=gcc

all: wykonywany glowny
	
wykonywany: wykonywany.c
	gcc wykonywany.c -o wykonywany.out -Wall -pedantic

glowny: glowny.c
	gcc glowny.c -o glowny.out -Wall -pedantic

clean:
	rm -f wykonywany.out glowny.out

.PHONY: all clean
