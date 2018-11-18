CC=g++
CFLAGS=-O2 -Wall 
LIBS=

FILES=file.o peer.o

all: mDataClass.o clean

mDataClass.o: $(FILES)
	ld -r $^ -o ../mDataClass.o

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS) $(LIBS)

clean:
	rm -f *.o