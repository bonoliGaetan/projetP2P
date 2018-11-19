#include <iostream>

#include "serviceP2P.h"


StError new_StError()
{
	StError ret;
	ret.code = 0;
	ret.codeString = std::string();
	ret.message = std::string();

	return ret;
}

ServiceP2P::ServiceP2P()
{
	this->lastError = new_StError();
	this->clientListeners.empty();
	this->serverListeners.empty();
}

ServiceP2P::~ServiceP2P() {}

json::value ServiceP2P::RequestHttp(std::string pdest,std::string pmethod, std::string ppath, json::value pbody)
{
	std::ofstream logFile(HTTPLOGS,std::ios::app);

	string_t dest = utility::conversions::to_string_t(pdest);
	string_t method = utility::conversions::to_string_t(pmethod);
	string_t path = utility::conversions::to_string_t(ppath);

	logFile << "Client:Envoyer\n" << pmethod << ": " << pdest << ppath << std::endl;
	logFile << pbody.as_string() << std::endl << std::endl;

	logFile.close();

	try {
		return http_client(dest).request(method,path,pbody)
		.then([](http_response response) 
		{	
			std::ofstream logFile(HTTPLOGS,std::ios::app);
			logFile << "Client:Recu\n";

			logFile << std::endl;
			logFile.close();
			return response.extract_json();
		})
		.get();
	} catch(http_exception e)
	{
		logFile.open(HTTPLOGS,std::ios::app);
		logFile << "Erreur: " << e.what() << std::endl << std::endl;
		logFile.close();
	} 

	return json::value::string(U(""));
}

json::value ServiceP2P::GetPeerList(std::string dest)
{
	std::string path("/peers");
	std::string method("GET");
	json::value body = json::value::string("");

	return  RequestHttp(dest,method,path,body);
}

int ServiceP2P::WaitRegister(int fctTraitement(json::value,json::value&))
{
	http_listener* myListener = new http_listener(U("http://localhost:12345/peers"));

	this->SetListenerMethod(*myListener,U("GET"),fctTraitement);

	myListener->open().wait();

	return 0; //clientListeners.add(myListener);
}

void ServiceP2P::SetListenerMethod(http_listener &plistener, string_t pmethod, int fctTraitement(json::value,json::value&))
{
	plistener.support(pmethod, [=] (http_request req) {
		json::value dataIn = req.extract_json().get();
		json::value dataOut;

		std::ofstream logFile(HTTPLOGS,std::ios::app);
		logFile <<"Serveur:Recu\n" << dataIn.as_string() << std::endl  << std::endl;
		logFile.close();

		int ret = fctTraitement(dataIn,dataOut);

		logFile.open(HTTPLOGS,std::ios::app);
		logFile <<"Serveur:Renvoyer\n" << dataOut.as_string() << std::endl  << std::endl;
		logFile.close();
		try {
			req.reply(status_codes::OK,dataOut);
		}catch(http_exception e)
		{
			logFile.open(HTTPLOGS,std::ios::app);
			logFile << "Erreur: " << e.what() << std::endl << std::endl;
			logFile.close();
		}
		
	});

}

void ServiceP2P::CloseWaitClient(int id)
{
	//this->clientListeners.delete(id);
}



