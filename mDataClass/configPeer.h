#ifndef CONFIGPEER_H
#define CONFIGPEER_H

#include <iostream>
#include <string>
#include <cpprest/json.h>
#include <cstdlib>

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

std::string GetJsonString(json::value &jval, string_t key);
int GetJsonInt(json::value &jval, string_t key);

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

	json::value GetJsonFromFile(std::string file);
	void affData();
};

#endif