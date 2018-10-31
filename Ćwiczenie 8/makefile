.SUFFIXES: .c .o .out .h

LIB_NAME = KolejkiKomunikatów
LIB_DIR = ./lib
LIB_STAT = lib$(LIB_NAME).a
LIB_SHAR = lib$(LIB_NAME).so
LIB_OBJS = kol.o
 
HEAD = kol.h

CFLAGS = -Wall -O -fPIC
CO = gcc

LFLAGS = -Wall -O
LDLIBS = -lm
LD = $(CO)

AR = ar
ARFLAGS = rv

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
	
.PHONY: all	
all: klient.out serwer.out
	
$(LIB_SHAR): $(LIB_OBJS) 
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS) 
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)
	
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)	
	
klient.out: klient.o $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) klient.o -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
	
serwer.out: serwer.o $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) serwer.o -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

klient.o: $(HEAD)

serwer.o: $(HEAD)

.PHONY: uruchom
uruchom: klient.out serwer.out
#	xterm -hold -title SERWER -bg black -e ./serwer.out &
	xterm -hold -title KLIENT -bg black -e ./klient.out &
	xterm -hold -title KLIENT -bg black -e ./klient.out &
	xterm -hold -title KLIENT -bg black -e ./klient.out &
	
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.so *.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf "Ćwiczenie_8_Paweł_Kędzior.tar.gz"  "Ćwiczenie 8" )