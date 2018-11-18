CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=client.o

all: clean mClient.o

mClient.o: $(FILES)
	$(CC) $(CFLAGS) -c -o mClient.o $^  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o