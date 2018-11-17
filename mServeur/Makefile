CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=serveur.o

all: clean mServeur.o

mServeur.o: $(FILES)
	$(CC) $(CFLAGS) -c -o mServeur.o $<  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o