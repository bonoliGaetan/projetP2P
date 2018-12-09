CC=g++
CFLAGS=-O2 -Wall 
LIBS= -lboost_system -lcrypto -lssl -lcpprest -std=c++11 -std=gnu++11 `pkg-config gtkmm-3.0 --cflags --libs`
OS=

APPLILIST= mDataClass.o mClient.o mInterfaceP2P.o mServeur.o mGraphique.o


all: clean appliLinux appliWindows

appliLinux: main.cpp $(APPLILIST) 
	$(CC) $(FLAGS) -o appliLinux.exe $^ $(LIBS) -D__OPSYS=$(OS)

appliWindows: $(APPLILIST) main.cpp
	$(CC) $(FLAGS) -o appliWindows.exe $^ $(LIBS) -D__OPSYS=$(OS)

%.o:
	make $(*).o -C $(*) OS=$(OS)

clean:
	rm -f *.exe
	rm -f *.o


