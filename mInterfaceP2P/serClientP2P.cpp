#include "serClientP2P.h"

StError new_StError(int c, std::string s)
{
	StError ret;
	ret.code = c;
	ret.codeString = std::string();
	ret.message = s;

	return ret;
}

SerClientP2P::SerClientP2P() {}

SerClientP2P::SerClientP2P(ConfigPeer* pcf)
{
	this->lastResponse = new_StError(0,"");
	this->cf = pcf;

	this->myIpAddr_t = utility::conversions::to_string_t(cf->myAddress);
	this->myPort_t = utility::conversions::to_string_t(cf->myPort);

	std::ofstream logFile(HTTPLOGS,std::ios::trunc);
	logFile << "";
	logFile.close();
}

SerClientP2P::~SerClientP2P() {}

json::value SerClientP2P::RequestHttp(std::string pdest,std::string pmethod, std::string ppath, json::value &pbody)
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

	} catch(std::exception e)
	{
		logFile.open(HTTPLOGS,std::ios::app);
		logFile << "Erreur Client Reply: " << e.what() << std::endl;
		logFile.close();
		this->lastResponse = new_StError(-1,e.what());
	} 

	return json::value::object();
}

std::vector<Peer> SerClientP2P::GetPeerList(std::string dest)
{
	std::string path("/peers");
	std::string method("GET");
	json::value body = json::value();

	json::value response = RequestHttp("http://"+dest,method,path,body);

	return JsonToListPeer(response);
}

File SerClientP2P::GetFile(std::string dest, std::string id)
{
	std::string path("/files/" + id);
	std::string method("GET");
	json::value body = json::value();

	json::value response = RequestHttp("http://"+dest,method,path,body);

	File fret;
	try {

		if(lastResponse.code == -1)
		{
			fret.id = -1;
			fret.name = "";
			fret.body = "";
			fret.size = 0;

			return fret;
		}

		fret.name = GetJsonString(response,"name");
		fret.body = REPTMP +id +"_" +fret.name;
		
		std::ofstream sfile(fret.body,std::ios::out);
	   	sfile << GetJsonString(response,"content");	   	
	    sfile.close();

	    std::ifstream ifile(fret.body,std::ios::in);
	    ifile.seekg (0, ifile.end);
	    fret.size = ifile.tellg();
	    ifile.seekg (0, ifile.beg);
	    ifile.close();

	    fret.id = id;
	}catch(std::ofstream::failure ioe)
	{
		std::cerr << "Erreur d'écriture du fichier : " << fret.body << std::endl;
		return File();
	}

	return fret;
}

void SerClientP2P::DeleteFile(std::string dest, std::string id)
{
	std::string path("/files/" + id);
	std::string method("DELETE");
	json::value body = json::value();

	RequestHttp("http://"+dest,method,path,body);
}

void SerClientP2P::SaveFile(std::string dest, File file)
{
	std::string path("/files");
	std::string method("POST");
	json::value body = file.ToJson(0);

	std::ifstream sfile(file.body,std::ios::in);
	sfile.seekg (0, sfile.end);
	file.size = sfile.tellg();
	sfile.close();

	json::value response = RequestHttp("http://"+dest,method,path,body);

	if(lastResponse.code == -1)
		return;

	UpdateFile(dest,file);
}

void SerClientP2P::UpdateFile(std::string dest, File file)
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
 
	    body["content"] = json::value::string(buffer);

	    delete[] buffer;

	}catch(std::ifstream::failure ioe)
	{
		std::cerr << "Erreur de lecture du fichier : " << file.body << std::endl;
		return;
	}

	RequestHttp("http://"+dest,method,path,body);
}

void SerClientP2P::RegisterPeer(std::string dest, std::string url)
{
	std::string path("/peers");
	std::string method("POST");
	json::value body;
	body["url"] = json::value::string(url); 

	RequestHttp("http://"+dest,method,path,body);
}

void SerClientP2P::UnregisterPeer(std::string dest, std::string url)
{
	std::string path("/peers");
	std::string method("DELETE");
	json::value body;
	body["url"] = json::value::string(url);  

	RequestHttp("http://"+dest,method,path,body);
}

std::vector<File> SerClientP2P::GetFileList(std::string dest)
{
	std::string path("/files");
	std::string method("GET");
	json::value body = json::value();

	json::value response = RequestHttp("http://"+dest,method,path,body);

	if(lastResponse.code == -1)
		return std::vector<File>();

	return JsonToListFile(response);
}