CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=serveur.o main.o

all: clean serveurMain.o

serveurMain.o: $(FILES)
	$(CC) $(CFLAGS) -c -o serveurMain.o $<  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o