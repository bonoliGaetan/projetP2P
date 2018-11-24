CC=g++
CFLAGS=-O2 -Wall 
LIBS=-std=c++11 -std=gnu++11 `pkg-config gtkmm-3.0 --cflags --libs` 
OS=

FILES=fenetre.o

all: mGraphique.o clean

mGraphique.o: $(FILES)
	ld -r $^ -o ../mGraphique.o

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS) $(LIBS) -D__OPSYS=$(OS)

clean:
	rm -f *.o