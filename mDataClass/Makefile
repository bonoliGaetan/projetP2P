CC=g++
CFLAGS=-O2 -Wall 
LIBS=-std=c++11 -std=gnu++11
OS=

FILES=file.o peer.o configPeer.o

all: mDataClass.o clean

mDataClass.o: $(FILES)
	ld -r $^ -o ../mDataClass.o

%.o: %.cpp %.h
	$(CC) -o $(*).o -c $(*).cpp $(CFLAGS) $(LIBS) -D__OPSYS=$(OS)

clean:
	rm -f *.o