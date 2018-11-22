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
	ServiceP2P s("8080","192.168.1.16");
	//s.myIpAddr = "192.168.1.16";
	json::value jval = json::value::parse("{\"size\":2,\"peerList\":[{\"url\":\"1.1.1.1:2255\",\"name\":\"ss\",\"fileList\":{\"size\":2,\"fileList\":[{\"size\":1234,\"name\":\"monFichier1\",\"id\":\"0\"},{\"size\":1234,\"name\":\"monFichierX\",\"id\":\"N-1\"}]}},{\"url\":\"4.4.4.4:6611\",\"size\":1,\"fileList\":{\"size\":1,\"fileList\":[{\"size\":1234,\"name\":\"monFichier1\",\"id\":\"3\"}]}}]}");
	std::cout << jval.serialize() << std::endl;

	std::vector<Peer> lp = s.JsonToListPeer(jval);



	json::value jval2 = s.ListPeerToJson(lp);

	std::cout << jval2.serialize() << std::endl;

	//s.WaitGetFile(&testhandler);

	//s.GetFile("http://" +s.myIpAddr +":" +s.myPort,"aaa");
	
	return 0;
}