#ifndef CLIENT_H
#define CLIENT_H
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<cpprest/json.h>

#include "../main.h"
#include"../mInterfaceP2P/serviceP2P.h"
#include"../mDataClass/configPeer.h"

#include"../mDataClass/peer.h"

using namespace web;

class Client
{
	private:
	std::string url;
	std::vector<File> listeFichier;
	ConfigPeer configuration;
	ServiceP2P serviceP2P;
	
	public:
	Client();
	Client(ConfigPeer &cf, ServiceP2P &spp);
	~Client();
	
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
	
	std::vector<File> obtenir_liste_fichier_d_un_pair(std::string url);
};
#endif
