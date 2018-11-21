CC=g++
CFLAGS=-O2 -Wall 
LIBS=-std=c++11 -std=gnu++11 -lcpprest

FILES=client.o

all: mClient.o clean

mClient.o: $(FILES)
	ld -r $^ -o ../mClient.o

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS) $(LIBS)

clean:
	rm -f *.o
