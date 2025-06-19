CC = gcc
SOURCES = mt19937ar.c
OBJECTS =$(SOURCES: .c=.o)

EXE = exe
all : $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) -o exe $(OBJECTS) -lm

mt19937ar.o : mt19937ar.c 
	$(CC) -c $<

clean : 
	rm -f $(OBJECTS)
run:
	./exe