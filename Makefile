CC=g++
CFLAGS=-O2 -Wall 
LIBS=

CLIENTLIST=interfaceP2P.o dataClass.o clientMain.o graphique.o
SERVEURLIST=interfaceP2P.o serveurMain.o dataClass

all: clean client server

client: main.cpp $(CLIENTLIST)
	$(CC) $(FLAGS) -o client.exe $<

serveur: $(SERVEURLIST)
	$(CC) $(FLAGS) -o serveur.exe $<

%.o:
	./make.sh $(PWD)/$(*) $(PWD) all
	

clean:
	rm -f *.o client.exe serveur.exe

