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

ServiceP2P::ServiceP2P(std::string port)
{
	this->lastError = new_StError();
	this->clientListeners.empty();
	this->serverListeners.empty();

	this->myIpAddr = getIPAddress();
	this->localhost = LOCALHOST;
	this->myPort = port;

	this->myIpAddr_t = utility::conversions::to_string_t(myIpAddr);
	this->localhost_t = utility::conversions::to_string_t(localhost);
	this->myPort_t = utility::conversions::to_string_t(myPort);

	std::ofstream logFile(HTTPLOGS,std::ios::trunc);
	logFile << "";
	logFile.close();
}

ServiceP2P::~ServiceP2P() {}

json::value ServiceP2P::RequestHttp(std::string pdest,std::string pmethod, std::string ppath, json::value pbody)
{
	std::ofstream logFile(HTTPLOGS,std::ios::app);

	string_t dest = utility::conversions::to_string_t(pdest);
	string_t method = utility::conversions::to_string_t(pmethod);
	string_t path = utility::conversions::to_string_t(ppath);

	logFile << "Client:Envoyer\n" << pmethod << ": " << pdest << ppath << std::endl;
	logFile << pbody.as_string() << std::endl;

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
		logFile << "Erreur: " << e.what() << std::endl;
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
	//string_t path = "http://0.0.0.0:" +this->myPort_t +"/peers";
	string_t path = U("http://*:") 
					+this->myPort_t
					+U("/peers");

	std::ofstream logFile(HTTPLOGS,std::ios::app);
	logFile << "SetListener:" << path << std::endl;
	logFile.close();

	http_listener* myListener = new http_listener(path);
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
		logFile <<"Serveur:Recu\n" << dataIn.as_string() << std::endl;
		logFile.close();

		int ret = fctTraitement(dataIn,dataOut);

		logFile.open(HTTPLOGS,std::ios::app);
		logFile <<"Serveur:Renvoyer\n" << dataOut.as_string() << std::endl;
		logFile.close();
		try {
			req.reply(status_codes::OK,dataOut);
		}catch(http_exception e)
		{
			logFile.open(HTTPLOGS,std::ios::app);
			logFile << "Erreur: " << e.what() << std::endl;
			logFile.close();
		}
		
	});

}


std::string ServiceP2P::getIPAddress()
{
	std::string myIpAddr = "";
	try {
	    string_t response = http_client(U("http://checkip.dyndns.com/"))
	    						.request(U("GET"))
	    						.then([] (http_response response) {
	    							return response.extract_string();
	    						}).get();

	    std::string body = utility::conversions::to_utf8string(response);
	    std::size_t pos = body.rfind(":");
	    myIpAddr = body.substr(pos+2);
	    pos = myIpAddr.find("<");
	    myIpAddr.resize(pos);

	}catch(http_exception e)
	{
		std::ofstream logFile(HTTPLOGS,std::ios::app);
		logFile << "Erreur Get IP: " << e.what() << std::endl;
		logFile.close();
		return "";
	}

    return myIpAddr;
}
