.SUFFIXES: .c .o .out .h

LIB_NAME = SemaforyiPamiec
LIB_DIR = ./lib
LIB_STAT = lib$(LIB_NAME).a
LIB_SHAR = lib$(LIB_NAME).so
LIB_OBJS = sem.o pam.o
 
HEADS2 = sem.h 
HEADS3 = pam.h

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
all: glownys.out glownyd.out

$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)
	
$(LIB_SHAR): $(LIB_OBJS) 
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS) 
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)
	
glownys.out: glowny.o $(LIB_STAT) producent.o konsument.o
	$(LD) -o $@ $(LFLAGS) glowny.o -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
	$(LD) -o producent.out $(LFLAGS) producent.o -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
	$(LD) -o konsument.out $(LFLAGS) konsument.o -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)
	
glownyd.out: glowny.o $(LIB_SHAR) producent.o konsument.o
	$(LD) -o $@ $(LFLAGS) glowny.o -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
	$(LD) -o producent.out $(LFLAGS) producent.o -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)
	$(LD) -o konsument.out $(LFLAGS) konsument.o -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

glowny.o: $(HEADS3) $(HEADS2)

producent.o: $(HEADS3) $(HEADS2)

konsument.o: $(HEADS3) $(HEADS2)

.PHONY: uruchomstat uruchomdyn
uruchomstat: glownys.out
	./glownys.out
uruchomdyn: glownyd.out
	./glownyd.out
	
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.out cel.txt; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf "Ćwiczenie_7_Paweł_Kędzior.tar.gz"  "Ćwiczenie 7" )