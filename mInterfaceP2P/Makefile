CC=g++
CFLAGS=-O2 -Wall 
LIBS=-std=c++11 -std=gnu++11 -lcpprest
OS=

FILES=serviceP2P.o

all: mInterfaceP2P.o clean

mInterfaceP2P.o: $(FILES)
	ld -r $^ -o ../mInterfaceP2P.o

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS) $(LIBS) -D__OPSYS=$(OS)

clean:
	rm -f *.o