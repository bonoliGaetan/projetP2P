CC=g++
CFLAGS=-O2 -Wall 
LIBS= 

FILES=serviceP2P.o

all: mInterfaceP2P.o clean

mInterfaceP2P.o: $(FILES)
	ld -r $^ -o ../mInterfaceP2P.o

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS) $(LIBS)

clean:
	rm -f *.o