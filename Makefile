CC=g++
CFLAGS= -O2 -Wall -pthread 
LIBS= -lboost_system -lcrypto -lssl -lcpprest -std=c++11 -std=gnu++11 `pkg-config gtkmm-3.0 --cflags --libs`

APPLILIST= mDataClass.o mClient.o mInterfaceP2P.o mServeur.o mGraphique.o


all: clean appliLinux appliWindows

appliLinux: main.cpp $(APPLILIST) 
	$(CC) $(CFLAGS) -o appliLinux.exe $^ $(LIBS) -D__OPSYS=$(OS)

appliWindows: $(APPLILIST) main.cpp
	$(CC) $(CFLAGS) -o appliWindows.exe $^ $(LIBS) -D__OPSYS=$(OS)

%.o:
	make $(*).o -C $(*) OS=$(OS)

clean:
	rm -f *.exe
	rm -f *.o


