CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=*.o

all: mGraphique.o clean

mGraphique.o: $(FILES)
	ld -r $^ -o ../mGraphique.o

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS) $(LIBS)

clean:
	rm -f *.o