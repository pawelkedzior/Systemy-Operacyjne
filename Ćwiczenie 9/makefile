.SUFFIXES: .c .o .out .h
 
CFLAGS = -Wall -O -fPIC
CO = gcc

LFLAGS = -Wall -O -pthread
LD = $(CO)

%.o: %.c
	$(CO) $(CFLAGS) -c $<
	
.PHONY: all	
all: watki.out
	
watki.out: watki.o
	$(LD) -o $@ $(LFLAGS) watki.o

.PHONY: uruchom
uruchom: watki.out
	./watki.out
	
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.out
tar: clean
	(cd ../; tar -cvzf "Ćwiczenie_9_Paweł_Kędzior.tar.gz"  "Ćwiczenie 9" )