#include <iostream>
#include "mInterfaceP2P/serviceP2P.h"

using namespace web::json;  

int testhandler(json::value dataIn, json::value &dataOut)
{
	dataOut = dataIn;
}

int main(void)
{	
	ServiceP2P s("65534");

	std::cout << s.myIpAddr << ":" << s.myPort << std::endl;

	s.WaitRegister(&testhandler);

	//s.GetPeerList("http://" +s.myIpAddr +":" +s.myPort);

	sleep(15);

	return 0;
}