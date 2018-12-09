#include "serServerP2P.h"


SerServerP2P::SerServerP2P()
{

}

SerServerP2P::SerServerP2P(ConfigPeer* pcf)
{
	this->cf = pcf; 

	this->myIpAddr_t = utility::conversions::to_string_t(cf->myAddress);
	this->myPort_t = utility::conversions::to_string_t(cf->myPort);

	this->requestTree = json::value::object();
	requestTree["GET"] = json::value::object();
	requestTree["POST"] = json::value::object();
	requestTree["DELETE"] = json::value::object();

	std::ofstream logFile(HTTPLOGS,std::ios::trunc);
	logFile << "";
	logFile.close();

	std::ofstream logFile2(INTERLOGS,std::ios::trunc);
	logFile2<< "";
	logFile2.close();

	this->serverListener = new http_listener("http://0.0.0.0:" +cf->myPort);
		serverListener->support("GET",[=] (http_request req) { traiterRequete(req); });
		serverListener->support("POST",[=] (http_request req) { traiterRequete(req); });
		serverListener->support("DELETE",[=] (http_request req) { traiterRequete(req); });

	this->serverListener->open().wait();

	this->isClosed = true;
}

SerServerP2P::~SerServerP2P() 
{
	std::cout << "END SERVICE SERVEUR P2P" << std::endl;
	CloseListener();
}

void SerServerP2P::OpenListener()
{
	std::cout << "Le serveur écoute sur : " << this->cf->myUrl << std::endl;
	this->isClosed = false;
}
void SerServerP2P::CloseListener()
{
	std::cout << "Le serveur n'écoute plus sur : " << this->cf->myUrl << std::endl;
	this->isClosed = true;
}


void SerServerP2P::traiterRequete(http_request req)
{
	try 
	{
		std::string paramUrl;
		std::string url = req.relative_uri().to_string();
		std::string method = utility::conversions::to_utf8string(req.method());
		
		int iFctTrait = getRequestTree(url,method,paramUrl);
		
		if((iFctTrait == -1)||(this->isClosed))
		{
			req.reply(status_codes::NotFound, json::value());
			return;
		}

		TFctWait fctTrait = vFctTrait[iFctTrait];

		json::value dataIn = req.extract_json().get();
		json::value dataOut = json::value();

		std::ofstream logFile(HTTPLOGS,std::ios::app);
		logFile << "Serveur:Recu:" << paramUrl << std::endl <<  dataIn.serialize() << std::endl;
		logFile.close();
		
		int err = fctTrait(paramUrl,dataIn,dataOut);

		logFile.open(HTTPLOGS,std::ios::app);
		logFile <<"Serveur:Renvoyer\n" << dataOut.serialize() << std::endl;
		logFile.close();

		if(err == 0)
			req.reply(status_codes::OK, dataOut);
		else if(err == -1)
			req.reply(status_codes::NotFound, dataOut);

	}catch(http_exception he)
	{
		std::ofstream logFile(HTTPLOGS,std::ios::app);
		logFile << "Erreur HTTP: " << he.what() << std::endl;
		logFile.close();
	}

}

void SerServerP2P::WaitUnregister(int fctTraitement(std::string,json::value, json::value&))
{
	addRequestTree("peers","DELETE",fctTraitement);
}

void SerServerP2P::WaitRegister(int fctTraitement(std::string,json::value,json::value&))
{
	addRequestTree("peers","POST",fctTraitement);
}

void SerServerP2P::WaitGetPeerList(int fctTraitement(std::string, json::value, json::value&))
{
	addRequestTree("peers","GET",fctTraitement);
}

void SerServerP2P::WaitGetFileList(int fctTraitement(std::string, json::value, json::value&))
{
	addRequestTree("files","GET",fctTraitement);
}

void SerServerP2P::WaitGetFile(int fctTraitement(std::string, json::value, json::value&))
{
	addRequestTree("files/*","GET",fctTraitement);
}

void SerServerP2P::WaitDeleteFile(int fctTraitement(std::string, json::value, json::value&))
{
	addRequestTree("files/*","DELETE",fctTraitement);
}

void SerServerP2P::WaitSaveFile(int fctTraitement(std::string, json::value, json::value&))
{
	addRequestTree("files","POST",fctTraitement);
}

void SerServerP2P::WaitUpdateFile(int fctTraitement(std::string, json::value, json::value&))
{
	addRequestTree("files/*","POST",fctTraitement);
}


void SerServerP2P::addRequestTree(std::string url,std::string method, int fctTrait(std::string, json::value, json::value&))
{
	try {
		auto paths = uri::split_path(url);
		auto tmp = &(requestTree[method]);
		unsigned int cpt;
		
		for(cpt = 0; cpt < paths.size() ; ++cpt)
		{
			if((*tmp)[paths[cpt]] == json::value::null())
				(*tmp)[paths[cpt]] = json::value::object();
			tmp = &((*tmp)[paths[cpt]]);
		}
	
		vFctTrait.push_back(fctTrait);
		(*tmp)["fct"] = vFctTrait.size() -1;

		std::ofstream logFile(INTERLOGS,std::ios::app);
		logFile << "Nouveau arbre : " << this->requestTree.serialize() << std::endl;
		logFile.close();

	}catch(std::exception se)
	{

	}
}


int SerServerP2P::getRequestTree(std::string url, std::string method, std::string &paramUrl)
{
	try {
		auto paths = uri::split_path(url);
		auto tmp = requestTree[method];
		unsigned int cpt;
		
		for(cpt = 0; cpt < paths.size() ; ++cpt)
		{
			if(tmp[paths[cpt]] == json::value::null())
			{
				if(tmp["*"] != json::value::null())
				{
					paramUrl = paths[cpt];
					tmp = tmp["*"];
				} else
				{
					return -1;
				}
			} else
				tmp = tmp[paths[cpt]];
		}
		
		if(tmp["fct"] != json::value::null())
			return tmp["fct"].as_integer();

		return -1;
	}catch(std::exception se)
	{
		return -1;
	}
}