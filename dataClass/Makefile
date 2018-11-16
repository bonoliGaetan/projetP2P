CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=file.o peer.o

all: clean dataClass.o

dataClass.o: $(FILES)
	$(CC) $(CFLAGS) -c -o dataClass.o $<  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o