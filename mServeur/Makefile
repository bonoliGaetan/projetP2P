CC=g++
CFLAGS=-O2 -Wall 
LIBS=-std=c++11 -std=gnu++11 -lcpprest
OS=

FILES=serveur.o

all: mServeur.o clean

mServeur.o: $(FILES)
	ld -r $^ -o ../mServeur.o

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS) $(LIBS) -D__OPSYS=$(OS)

clean:
	rm -f *.o