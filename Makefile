CC=g++
CFLAGS=-O2 -Wall 
LIBS= -lboost_system -lcrypto -lssl -lcpprest -std=c++11 -std=gnu++11
CLIENTLIST=mInterfaceP2P.o mDataClass.o mClient.o
SERVEURLIST=mInterfaceP2P.o mServeurMain.o mDataClass.o

TESTLISTMAX=mInterfaceP2P.o mDataClass.o
TESTLISTGAE=
TESTLISTALE=mClient.o mDataClass.o

all: clean client server 

client: $(CLIENTLIST)
	$(CC) $(FLAGS) -o client.exe $^ $(LIBS)

serveur: $(SERVEURLIST)
	$(CC) $(FLAGS) -o serveur.exe $^ $(LIBS)

testmax: $(TESTLISTMAX) mainTestMax.cpp
	$(CC) $(FLAGS) -o testmax.exe $^ $(LIBS)

testgae: $(TESTLISTMAX) mainTestGae.cpp
	$(CC) $(FLAGS) -o testgae.exe $^ $(LIBS)

testale: $(TESTLISTMAX) mainTestAle.cpp
	$(CC) $(FLAGS) -o testale.exe $^ $(LIBS)

%.o:
	./make.sh $(PWD)/$(*) $(PWD) all

clean:
	rm -f client.exe serveur.exe test*.exe
	rm -f *.o

