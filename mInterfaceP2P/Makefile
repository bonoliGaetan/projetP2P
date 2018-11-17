CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=serviceP2P.o

all: clean mInterfaceP2P.o

mInterfaceP2P.o: $(FILES)
	$(CC) $(CFLAGS) -c -o mInterfaceP2P.o $<  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o