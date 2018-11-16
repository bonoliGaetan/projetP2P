CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=*.o

all: clean graphique.o

graphique.o: $(FILES)
	$(CC) $(CFLAGS) -c -o graphique.o $<  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o