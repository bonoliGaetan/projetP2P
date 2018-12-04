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
	this->id = GetJsonInt(jconf,IDPR);

	srand(this->id);
	int iPort = rand()%(maxPort - minPort +1) +minPort;
	this->myPort = std::to_string(iPort);

	this->myUrl = myAddress +":" +myPort;

	this->listePair = std::vector<Peer>();
	this->listeFichier = std::vector<File>();

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
	s += "myId:" +std::to_string(this->id) +"\n";

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



json::value FileToJson(File file)
{
	json::value jret;

	jret["id"] = json::value::string(file.id);
	jret["name"] = json::value::string(file.name);
	jret["size"] = file.size;
	jret["body"] = json::value::string(file.body);

	return jret;
}

json::value ListFileToJson(std::vector<File> &fileList)
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

json::value PeerToJson(Peer peer)
{
	json::value jret;
	jret["url"] = json::value::string(peer.url);
	jret["name"] = json::value::string(peer.name);
	jret["fileList"] = ListFileToJson(peer.fileList);

	return jret;
}

json::value ListPeerToJson(std::vector<Peer> &peerList)
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


File JsonToFile(json::value val)
{
	File fret;
	fret.id = GetJsonString(val,"id");
	fret.name = GetJsonString(val,"name");
	fret.size = GetJsonInt(val,"size");
	fret.body = GetJsonString(val,"body");

	return fret;
}

std::vector<File> JsonToListFile(json::value val)
{
	std::vector<File> lfret;
	int size = GetJsonInt(val,"size");
	if(size <= 0)
		return lfret;
	
	json::value jlist = val.at("list");
	int i;
	for(i = 0; i < size ; ++i)
		lfret.push_back(File::FromJson(jlist[i]));

	return lfret;
}

Peer JsonToPeer(json::value val)
{
	Peer pret;
	pret.url = GetJsonString(val,"url");
	pret.name = GetJsonString(val,"name");
	pret.fileList = JsonToListFile(val.at("fileList"));

	return pret;
}

std::vector<Peer> JsonToListPeer(json::value val)
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

std::string getIPAddress()
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

	}catch(std::exception e)
	{
		std::ofstream logFile(CONFIGLOGS,std::ios::app);
		logFile << "Erreur Get IP: " << e.what() << std::endl;
		logFile.close();
		return "";
	}

    return myIpAddr;
}