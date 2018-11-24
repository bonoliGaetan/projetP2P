#include "configPeer.h"

ConfigPeer::~ConfigPeer() {}

ConfigPeer::ConfigPeer(std::string file)
{
	std::ofstream logFile(CONFIGLOGS,std::ios::trunc);
	logFile << "";
	logFile.close();

	this->file = file;

	json::value jconf = GetJsonFromFile(file);

	this->repClient = GetJsonString(jconf,REPC);
	this->repServer = GetJsonString(jconf,REPS);
	this->tailleMaxRepServer = GetJsonInt(jconf,TMAX);
	this->firstRegister = GetJsonString(jconf,IPIN);
	this->myAddress = GetJsonString(jconf,MYIP);
	this->maxPort = GetJsonInt(jconf,MAXP);
	this->minPort = GetJsonInt(jconf,MINP);
	this->myName = GetJsonString(jconf,NAME);

	int iPort = rand()%(maxPort - minPort +1) +minPort;
	this->myPort = std::to_string(iPort);

	this->myUrl = myAddress +":" +myPort;
}
ConfigPeer::ConfigPeer() {}

void ConfigPeer::affData()
{
	std::string s("");
	s += "repClient:" +this->repClient +"\n";
	s += "repServer:" +this->repServer;
	s += "tailleMaxRepServer:" +std::to_string(this->tailleMaxRepServer) +"\n";
	s += "firstRegister:" +this->firstRegister +"\n";
	s += "myAddress:" +this->myAddress +"\n";
	s += "maxPort:" +std::to_string(this->maxPort) +"\n";
	s += "minPort:" +std::to_string(this->minPort) +"\n";
	s += "myName:" +this->myName +"\n";
	s += "myUrl:" +this->myUrl +"\n";
	s += "myPort:" +this->myPort +"\n";

	std::cout << s;

}

json::value ConfigPeer::GetJsonFromFile(std::string file)
{
	try {

		std::ifstream sfile(file,std::ios::in);
	    // get length of file:
	    sfile.seekg (0, sfile.end);
	    int length = sfile.tellg();
	    sfile.seekg (0, sfile.beg);

	    char * buffer = new char [length];

	    // read data as a block:
	    sfile.read (buffer,length);
	    sfile.close();

	    std::ofstream logFile(CONFIGLOGS,std::ios::app);
	    logFile << buffer << std::endl;
		logFile.close();

	    string_t str(buffer);
	    // ...buffer contains the entire file...
	    json::value jret = json::value::parse(str);

	    logFile = std::ofstream(CONFIGLOGS,std::ios::app);
	    logFile << jret.serialize() << std::endl;
		logFile.close();

	    delete[] buffer;



	    return jret;
	}catch(json::json_exception je)
	{
		std::cout << "Erreur de lecture du fichier de configuration" << std::endl;
		exit(0);
	}
}

int GetJsonInt(json::value &jval, string_t key)
{
	int ret;
	try {
		ret = jval.at(key).as_integer();
	}catch(json::json_exception je) {
		ret = 0;
	} 
	return ret;
}

std::string GetJsonString(json::value &jval, string_t key)
{
	string_t ret_t;
	std::string ret;
	try {
		ret_t = jval.at(key).as_string();
		ret = utility::conversions::to_utf8string(ret_t);
	}catch(json::json_exception je) {
		ret = "";
	} 
	return ret;
}
