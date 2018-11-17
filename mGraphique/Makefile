CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=*.o

all: clean mGraphique.o

mGraphique.o: $(FILES)
	$(CC) $(CFLAGS) -c -o mGraphique.o $<  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o