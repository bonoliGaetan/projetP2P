CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=client.o main.o

all: clean clientMain.o

clientMain.o: $(FILES)
	$(CC) $(CFLAGS) -c -o clientMain.o $<  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o