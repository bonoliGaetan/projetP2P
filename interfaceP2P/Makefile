CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=serviceP2P.o

all: clean interfaceP2P.o

interfaceP2P.o: $(FILES)
	$(CC) $(CFLAGS) -c -o interfaceP2P.o $<  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o