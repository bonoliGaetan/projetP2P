CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=file.o peer.o

all: clean mDataClass.o

mDataClass.o: $(FILES)
	$(CC) $(CFLAGS) -c -o mDataClass.o $<  $(LIBS)

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS)

clean:
	rm -f *.o