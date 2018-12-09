#ifndef CONFIGPEER_H
#define CONFIGPEER_H

#include <iostream>
#include <string>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cstdlib>

#include "../mDataClass/peer.h"
#include "../mDataClass/file.h"
#include "../mDataClass/jsonUtility.h"


using namespace web::http;                  	// Common HTTP functionality
using namespace web::http::client;          	// HTTP client features 
using namespace web;
using namespace web::json;
using namespace utility; 

#if __OPSYS == linux
	#define CONFIGLOGS 	"logs/configlogs.txt"
	#define SL 			"/"
#elif __OPSYS == windows
	#define CONFIGLOGS 	"logs\\configlogs.txt"
	#define SL 			"\\"
#endif

#define REPC "Repertoire_Client"
#define REPS "Repertoire_Server"
#define TMAX "Taille_max_repertoire_Serveur"
#define IPIN "Ip_init_Serveur"
#define MYIP "Ip_address_client"
#define MINP "Port_min"
#define MAXP "Port_max"
#define NAME "Nom"
#define IDPR "id_pair"



json::value FileToJson(File file);
json::value ListFileToJson(std::vector<File> &filelist);
json::value PeerToJson(Peer peer);
json::value ListPeerToJson(std::vector<Peer> &peerList);

File JsonToFile(json::value file);
std::vector<File> JsonToListFile(json::value fileList);
Peer JsonToPeer(json::value peer);
std::vector<Peer> JsonToListPeer(json::value peerList);

std::string getIPAddress();


class ConfigPeer
{
public:
	ConfigPeer(std::string file);
	ConfigPeer();
	~ConfigPeer();

	std::string file;

	std::string repClient;
	std::string repServer;
	int tailleMaxRepServer;
	std::string firstRegister;
	std::string myAddress;
	std::string myPort;
	std::string myUrl;
	std::string myName;
	int maxPort;
	int minPort;
	int id;

	json::value GetJsonFromFile(std::string file);
	void affData();

	std::vector<Peer> listePair;
};

#endif