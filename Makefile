CC=g++
CFLAGS=-O2 -Wall 
LIBS= -lboost_system -lcrypto -lssl -lcpprest
CLIENTLIST=mInterfaceP2P.o mDataClass.o mClient.o
SERVEURLIST=mInterfaceP2P.o mServeurMain.o mDataClass.o
TESTLIST=mInterfaceP2P.o mDataClass.o

all: clean client server

client: $(CLIENTLIST)
	$(CC) $(FLAGS) -o client.exe $^ $(LIBS)

serveur: $(SERVEURLIST)
	$(CC) $(FLAGS) -o serveur.exe $^ $(LIBS)

test: $(TESTLIST) mainTest.cpp
	$(CC) $(FLAGS) -o test.exe $^ $(LIBS)

%.o:
	./make.sh $(PWD)/$(*) $(PWD) all
	

clean:
	rm -f */*.o client.exe serveur.exe test.exe

