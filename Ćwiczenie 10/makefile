.SUFFIXES: .c .o .out .h
 
CFLAGS = -Wall -O -fPIC
CO = gcc

LFLAGS = -Wall -O -pthread
LD = $(CO)

%.o: %.c
	$(CO) $(CFLAGS) -c $<
	
.PHONY: all	
all: watki2.out
	
watki2.out: watki2.o
	$(LD) -o $@ $(LFLAGS) watki2.o

.PHONY: uruchom
uruchom: watki2.out
	./watki2.out
	
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.out
tar: clean
	(cd ../; tar -cvzf "Ćwiczenie_10_Paweł_Kędzior.tar.gz"  "Ćwiczenie 10" )