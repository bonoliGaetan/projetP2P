#ifndef CLIENT_H
#define CLIENT_H
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<cpprest/json.h>
#include"../mInterfaceP2P/service.h"
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
	// TODO => fonction dans un thread qui utilise waitRequestedClient et quiva traiter les donnes recues.
	
	public:
	Client();
	~Client();
	
	File json_vers_fichier(json::value fichier);
	Peer json_vers_pair(json::value fichier);
	
	std::vector<Peer> json_vers_liste_pair(json::value fichier);
	std::vector<File> json_vers_liste_fichier(json::value fichier);
	
	json::value fichier_vers_json(File fichier);
	json::value pair_vers_json(Peer pair);
	
	json::value liste_pair_vers_json(std::vector<Peer> liste);
	json::value liste_fichier_vers_json(std::vector<File> liste);
	
	void ajouter_liste_fichier();
	void ajouter_liste_pair();
	
	void ajouter_pair();
	void ajouter_fichier();
	
	int enregistrement(std::string param, json::value entree, json::value& sortie);
	int desenregistrement(std::string urlPair, json::value entree, json::value& sortie);
	
	void obtenir_liste_pair_client(std::string dest);
	void obtenir_liste_fichier_client(std::string dest);
	void obtenir_fichier_client();
	void supprimer_fichier_client(std::string dest,std::string id);
	void sauvegarder_fichier_client(std::string dest, File file);
	void enregistrer_pair_client(std::string dest, std::string url);
	void desenregistrer_pair_client(std::string dest, std::string url);
};
#endif
