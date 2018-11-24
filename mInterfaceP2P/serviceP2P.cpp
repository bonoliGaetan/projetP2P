#include <iostream>

#include "serviceP2P.h"


StError new_StError(int c, std::string s)
{
	StError ret;
	ret.code = c;
	ret.codeString = std::string();
	ret.message = s;

	return ret;
}

ServiceP2P::ServiceP2P() {}

ServiceP2P::ServiceP2P(ConfigPeer &pcf)
{
	this->lastResponse = new_StError(0,"");
	this->serverListeners.empty();
	this->cf = pcf;

	this->myIpAddr_t = utility::conversions::to_string_t(cf.myAddress);
	this->myPort_t = utility::conversions::to_string_t(cf.myPort);

	std::ofstream logFile(HTTPLOGS,std::ios::trunc);
	logFile << "";
	logFile.close();
}

ServiceP2P::~ServiceP2P() {}

json::value ServiceP2P::RequestHttp(std::string pdest,std::string pmethod, std::string ppath, json::value &pbody)
{
	std::ofstream logFile(HTTPLOGS,std::ios::app);

	string_t dest = utility::conversions::to_string_t(pdest);
	string_t method = utility::conversions::to_string_t(pmethod);
	string_t path = utility::conversions::to_string_t(ppath);

	logFile << "Client:Envoyer\n" << pmethod << ": " << pdest << ppath << std::endl;
	logFile << pbody.serialize() << std::endl;

	logFile.close();

	try {
		json::value rep = http_client(dest).request(method,path,pbody)
		.then([=](http_response response) 
		{	
			
			lastResponse = new_StError(response.status_code(),response.reason_phrase());
			return response.extract_json();
		})
		.get();

		std::ofstream logFile(HTTPLOGS,std::ios::app);
		logFile << "Client:Recu\n" << rep.serialize() << std::endl;
		logFile.close();

		return rep;

	} catch(http_exception e)
	{
		logFile.open(HTTPLOGS,std::ios::app);
		logFile << "Erreur: " << e.what() << std::endl;
		logFile.close();
		this->lastResponse = new_StError(-1,e.what());
	} 

	return json::value();
}

std::vector<Peer> ServiceP2P::GetPeerList(std::string dest)
{
	std::string path("/peers");
	std::string method("GET");
	json::value body = json::value();

	json::value response = RequestHttp("http://"+dest,method,path,body);

	return JsonToListPeer(response);
}


std::vector<File> ServiceP2P::GetFileList(std::string dest)
{
	std::string path("/files");
	std::string method("GET");
	json::value body = json::value();

	json::value response = RequestHttp("http://"+dest,method,path,body);

	return JsonToListFile(response);
}

File ServiceP2P::GetFile(std::string dest, std::string id)
{
	std::string path("/files/" + id);
	std::string method("GET");
	json::value body = json::value();

	json::value response = RequestHttp("http://"+dest,method,path,body);

	File fret;
	try {
		fret.id = "-1";
		fret.size = GetJsonInt(response,"size");
		fret.body = REPTMP +id +"_" +std::to_string(fret.size);
		
		std::ofstream sfile(fret.body,std::ios::out);
	   	sfile << GetJsonString(response,"body");
	    sfile.close();

	}catch(std::ofstream::failure ioe)
	{
		std::cerr << "Erreur d'écriture du fichier : " << fret.body << std::endl;
		return File();
	}

	return fret;
}

void ServiceP2P::DeleteFile(std::string dest, std::string id)
{
	std::string path("/files/" + id);
	std::string method("DELETE");
	json::value body = json::value();

	RequestHttp("http://"+dest,method,path,body);
}

void ServiceP2P::SaveFile(std::string dest, File file)
{
	std::string path("/files");
	std::string method("POST");
	json::value body = FileToJson(file);

	json::value response = RequestHttp("http://"+dest,method,path,body);

	file.id = GetJsonString(response,"id");

	UpdateFile(dest,file);
}

void ServiceP2P::UpdateFile(std::string dest, File file)
{
	std::string path("/files/" + file.id);
	std::string method("POST");
	json::value body;
	try {
		std::ifstream sfile(file.body,std::ios::in);
	    
	    sfile.seekg (0, sfile.end);
	    int length = sfile.tellg();
	    sfile.seekg (0, sfile.beg);

	    char * buffer = new char [length];

	    sfile.read (buffer,length);
	    sfile.close();
 
 		body["size"] = length;
	    body["body"] = json::value::string(buffer);

	    delete[] buffer;

	}catch(std::ifstream::failure ioe)
	{
		std::cerr << "Erreur de lecture du fichier : " << file.body << std::endl;
		return;
	}

	RequestHttp("http://"+dest,method,path,body);
}

void ServiceP2P::WaitUnregister(int fctTraitement(std::string,json::value, json::value&))
{
	string_t path = "http://0.0.0.0:" +this->myPort_t +"/peers";

	http_listener* myListener = new http_listener(path);
	this->SetListenerMethod(*myListener,U("DELETE"),fctTraitement);
	
	myListener->open().wait();

	std::ofstream logFile(HTTPLOGS,std::ios::app);
	logFile << "SetListener:DELETE:" << path << std::endl;
	logFile.close();	

	serverListeners.push_back(myListener);
}

void ServiceP2P::WaitRegister(int fctTraitement(std::string,json::value,json::value&))
{
	string_t path = "http://0.0.0.0:" +this->myPort_t +"/peers";

	http_listener* myListener = new http_listener(path);
	this->SetListenerMethod(*myListener,U("POST"),fctTraitement);

	myListener->open().wait();

	std::ofstream logFile(HTTPLOGS,std::ios::app);
	logFile << "SetListener:POST:" << path << std::endl;
	logFile.close();	

	serverListeners.push_back(myListener);
}

void ServiceP2P::SetListenerMethod(http_listener &plistener, string_t pmethod, int fctTraitement(std::string,json::value,json::value&))
{
	try {
		plistener.support(pmethod, [=] (http_request req) {
			
			std::string paramUrl = req.relative_uri().to_string();

			json::value dataIn = req.extract_json().get();
			json::value dataOut = json::value();

			std::ofstream logFile(HTTPLOGS,std::ios::app);
			logFile << "Serveur:Recu:" << paramUrl << std::endl <<  dataIn.serialize() << std::endl;
			logFile.close();

			fctTraitement(paramUrl,dataIn,dataOut);

			logFile.open(HTTPLOGS,std::ios::app);
			logFile <<"Serveur:Renvoyer\n" << dataOut.serialize() << std::endl;
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
	} catch(http_listener::http_exception he)
	{
		std::cout << he.what() << std::endl;
	}

}

void ServiceP2P::RegisterPeer(std::string dest, std::string url)
{
	std::string path("/peers");
	std::string method("POST");
	json::value body;
	body["url"] = json::value::string(url); 

	RequestHttp("http://"+dest,method,path,body);
}

void ServiceP2P::UnregisterPeer(std::string dest, std::string url)
{
	std::string path("/peers");
	std::string method("DELETE");
	json::value body;
	body["url"] = json::value::string(url);  

	RequestHttp("http://"+dest,method,path,body);
}

void ServiceP2P::WaitGetPeerList(int fctTraitement(std::string, json::value, json::value&))
{
	string_t path = "http://0.0.0.0:" +this->myPort_t +"/peers";

	http_listener* myListener = new http_listener(path);
	this->SetListenerMethod(*myListener,U("GET"),fctTraitement);

	myListener->open().wait();

	std::ofstream logFile(HTTPLOGS,std::ios::app);
	logFile << "SetListener:GET:" << path << std::endl;
	logFile.close();	

	serverListeners.push_back(myListener);
}

void ServiceP2P::WaitGetFileList(int fctTraitement(std::string, json::value, json::value&))
{
	string_t path = "http://0.0.0.0:" +this->myPort_t +"/files";

	http_listener* myListener = new http_listener(path);
	this->SetListenerMethod(*myListener,U("GET"),fctTraitement);

	myListener->open().wait();

	std::ofstream logFile(HTTPLOGS,std::ios::app);
	logFile << "SetListener:GET:" << path << std::endl;
	logFile.close();	

	serverListeners.push_back(myListener);
}

void ServiceP2P::WaitGetFile(int fctTraitement(std::string, json::value, json::value&))
{
	string_t path = "http://0.0.0.0:" +this->myPort_t +"/files/";

	http_listener* myListener = new http_listener(path);
	this->SetListenerMethod(*myListener,U("GET"),fctTraitement);

	myListener->open().wait();

	std::ofstream logFile(HTTPLOGS,std::ios::app);
	logFile << "SetListener:GET:" << path << std::endl;
	logFile.close();	

	serverListeners.push_back(myListener);
}

void ServiceP2P::WaitDeleteFile(int fctTraitement(std::string, json::value, json::value&))
{
	string_t path = "http://0.0.0.0:" +this->myPort_t +"/files/";

	http_listener* myListener = new http_listener(path);
	this->SetListenerMethod(*myListener,U("DELETE"),fctTraitement);

	myListener->open().wait();

	std::ofstream logFile(HTTPLOGS,std::ios::app);
	logFile << "SetListener:DELETE:" << path << std::endl;
	logFile.close();	

	serverListeners.push_back(myListener);
}

void ServiceP2P::WaitSaveFile(int fctTraitement(std::string, json::value, json::value&))
{
	string_t path = "http://0.0.0.0:" +this->myPort_t +"/files";

	http_listener* myListener = new http_listener(path);
	this->SetListenerMethod(*myListener,U("POST"),fctTraitement);

	myListener->open().wait();

	std::ofstream logFile(HTTPLOGS,std::ios::app);
	logFile << "SetListener:POST:" << path << std::endl;
	logFile.close();

	serverListeners.push_back(myListener);
}

void ServiceP2P::WaitUpdateFile(int fctTraitement(std::string, json::value, json::value&))
{
	string_t path = "http://0.0.0.0:" +this->myPort_t +"/files/";

	http_listener* myListener = new http_listener(path);
	this->SetListenerMethod(*myListener,U("POST"),fctTraitement);

	myListener->open().wait();

	std::ofstream logFile(HTTPLOGS,std::ios::app);
	logFile << "SetListener:POST:" << path << std::endl;
	logFile.close();	

	serverListeners.push_back(myListener);
}

void ServiceP2P::CloseAllWaitServer()
{
	for(std::vector<http_listener*>::iterator it = this->serverListeners.begin() ; it != this->serverListeners.end(); ++it)
		delete *it;
}

json::value ServiceP2P::FileToJson(File file)
{
	json::value jret;

	jret["id"] = json::value::string(file.id);
	jret["name"] = json::value::string(file.name);
	jret["size"] = file.size;

	return jret;
}

json::value ServiceP2P::ListFileToJson(std::vector<File> fileList)
{
	if(fileList.size() <= 0)
		return json::value();

	json::value jret;
	jret["size"] = fileList.size();

	int cpt;
	std::vector<File>::iterator it;
	json::value jfileList = json::value::array();
	for(it = fileList.begin(), cpt = 0 ; it != fileList.end(); ++it, ++cpt )
	{
		jfileList[cpt] = FileToJson(*it);
	}
	jret["fileList"] = jfileList;

	return jret;
}

json::value ServiceP2P::PeerToJson(Peer peer)
{
	json::value jret;
	jret["url"] = json::value::string(peer.url);
	jret["name"] = json::value::string(peer.name);
	jret["fileList"] = ListFileToJson(peer.fileList);

	return jret;
}

json::value ServiceP2P::ListPeerToJson(std::vector<Peer> peerList)
{
	if(peerList.size() <= 0)
		return json::value();

	json::value jret;
	jret["size"] = peerList.size();

	int cpt ;
	std::vector<Peer>::iterator it;
	json::value jpeerList = json::value::array();
	for(it = peerList.begin(), cpt = 0 ; it != peerList.end(); ++it, ++cpt )
	{
		jpeerList[cpt] = PeerToJson(*it);
	}
	jret["peerList"] = jpeerList;

	return jret;
}


File ServiceP2P::JsonToFile(json::value val)
{
	File fret;
	fret.id = GetJsonString(val,"id");
	fret.name = GetJsonString(val,"name");
	fret.size = GetJsonInt(val,"size");

	return fret;
}

std::vector<File> ServiceP2P::JsonToListFile(json::value val)
{
	std::vector<File> lfret;
	int size = GetJsonInt(val,"size");
	if(size <= 0)
		return lfret;
	
	json::value jlist = val.at("fileList");
	int i;
	for(i = 0; i < size ; ++i)
		lfret.push_back(JsonToFile(jlist[i]));

	return lfret;
}

Peer ServiceP2P::JsonToPeer(json::value val)
{
	Peer pret;
	pret.url = GetJsonString(val,"url");
	pret.name = GetJsonString(val,"name");
	pret.fileList = JsonToListFile(val.at("fileList"));

	return pret;
}

std::vector<Peer> ServiceP2P::JsonToListPeer(json::value val)
{
	std::vector<Peer> lpret;
	int size = GetJsonInt(val,"size");
	if(size <= 0)
		return lpret;
	
	json::value jlist = val.at("peerList");
	int i;
	for(i = 0; i < size ; ++i)
		lpret.push_back(JsonToPeer(jlist[i]));

	return lpret;
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
