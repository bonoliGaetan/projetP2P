CC=g++
CFLAGS=-O2 -Wall 
LIBS=

CLIENTLIST=mInterfaceP2P.o mDataClass.o mClient.o
SERVEURLIST=mInterfaceP2P.o mServeurMain.o mDataClass.o
TESTLIST=

all: clean client server

client: main.cpp $(CLIENTLIST)
	$(CC) $(FLAGS) -o client.exe $<

serveur: $(SERVEURLIST)
	$(CC) $(FLAGS) -o serveur.exe $<

test: $(TESTLIST)
	$(CC) $(FLAGS) -o test.exe $<

%.o:
	./make.sh $(PWD)/$(*) $(PWD) all
	

clean:
	rm -f *.o client.exe serveur.exe test.exe

