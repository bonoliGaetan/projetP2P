#include <iostream>
#include "mInterfaceP2P/serviceP2P.h"

using namespace web::json;  

int testhandler(std::string paramUrl, json::value dataIn, json::value &dataOut)
{
	std::cout << paramUrl << std::endl;
	dataOut.parse(dataIn.serialize());
	dataOut["request"] = json::value(paramUrl);
	std::cout << dataOut.serialize() << std::endl;
}

int main(void)
{	
	ServiceP2P s("8080");
	//s.myIpAddr = "192.168.1.16";
	
	s.WaitGetFile(&testhandler);

	s.GetFile("http://" +s.myIpAddr +":" +s.myPort,"aaa");
	
	return 0;
}