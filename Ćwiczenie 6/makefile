CC=gcc
CFLAGS=-Wall -pedantic
OBJS=sem.o powielacz.o dostep.o

all: sem

sem: $(OBJS)
	$(CC) -o wynik.out powielacz.o sem.o
	$(CC) -o dostep.out dostep.o sem.o
sem.o: sem.c
	$(CC) -c sem.c -o sem.o -Wall
powielacz.o: powielacz.c
	$(CC) -c powielacz.c -o powielacz.o $(CFLAGS)
dostep.o: dostep.c
	$(CC) -c dostep.c -o dostep.o $(CFLAGS)
clean:
	rm -f *.o *.out *~