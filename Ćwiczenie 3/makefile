CC=gcc

all: wykonywany glowny
	
wykonywany: procesy.c
	gcc procesy.c -o obsluga.out -Wall -pedantic

glowny: glowny1.c
	gcc glowny1.c -o glowny.out -Wall -pedantic

clean:
	rm -f obsluga.out glowny.out

.PHONY: all clean
