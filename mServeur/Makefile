CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=serveur.o

all: mServeur.o clean

mServeur.o: $(FILES)
	ld -r $^ -o ../mServeur.o

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS) $(LIBS)

clean:
	rm -f *.o