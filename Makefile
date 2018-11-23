CC=g++
CFLAGS=-O2 -Wall 
LIBS= -lboost_system -lcrypto -lssl -lcpprest -std=c++11 -std=gnu++11
export OS

APPLILIST=mInterfaceP2P.o mDataClass.o

TESTLISTMAX=mInterfaceP2P.o mDataClass.o
TESTLISTGAE=mClient.o mDataClass.o
TESTLISTALE=

all: clean appliLinux appliWindows

appliLinux: $(APPLILIST) main.cpp
	$(CC) $(FLAGS) -o appliLinux.exe $^ $(LIBS) -D__OPSYS=$(OS)

appliWindows: $(APPLILIST) main.cpp
	$(CC) $(FLAGS) -o appliWindows.exe $^ $(LIBS) -D__OPSYS=$(OS)

testmax: $(TESTLISTMAX) mainTestMax.cpp
	$(CC) $(FLAGS) -o testmax.exe $^ $(LIBS)

testgae: $(TESTLISTGAE) mainTestGae.cpp
	$(CC) $(FLAGS) -o testgae.exe $^ $(LIBS)

testale: $(TESTLISTALE) mainTestAle.cpp
	$(CC) $(FLAGS) -o testale.exe $^ $(LIBS)

%.o:
	make $(*).o -C $(*) OS=$(OS)

clean:
	rm -f *.exe
	rm -f *.o
	rm -f */*.o


