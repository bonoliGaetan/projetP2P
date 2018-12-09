#ifndef CLIENT_H
#define CLIENT_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
#include<map>
#include<cpprest/json.h>

#include "../mInterfaceP2P/serClientP2P.h"
#include "../mDataClass/peer.h"
#include "../mDataClass/configPeer.h"


#if __OPSYS == linux
	#define SL "/"
#elif __OPSYS == windows
	#define SL "\\"
#endif

using namespace web;

class Client
{
	private:
	std::string url;
	
	public:
	Client();
	Client(ConfigPeer* cf);
	~Client();
	
	ConfigPeer* configuration;
	SerClientP2P serviceP2P;

	int enregistrement(std::string param, json::value entree, json::value& sortie);
	int desenregistrement(std::string urlPair, json::value entree, json::value& sortie);
	
	void obtenir_liste_pair_client(std::string dest);
	void obtenir_liste_fichier_client(std::string dest);
	void obtenir_fichier_client(std::string dest, std::string id);
	void supprimer_fichier_client(std::string dest,std::string id);
	void sauvegarder_fichier_client(std::string dest, File file);
	void enregistrer_pair_client(std::string dest, std::string url);
	void desenregistrer_pair_client(std::string dest, std::string url);
	void maj_fichier_client(std::string dest, File file);
	
	std::string affecter_id(int pairId, std::string nomFic, int tailleFic, int tailleCle);

	int suppr_peer_if_notfound(std::string url);
	
	std::vector<File> obtenir_liste_fichier_d_un_pair(std::string url);
};


#endif
