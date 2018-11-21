#ifndef CLIENT_H
#define CLIENT_H
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<cpprest/json.h>


#include"../mDataClass/peer.h"

using namespace web::json;

class Client
{
	private:
	std::string url;
	std::map<std::string,std::string> listeOption;
	std::vector<Peer> listePaire;
	// TODO => fonction dans un thread qui utilise waitRequestedClient et quiva traiter les donnes recues.
	
	public:
	Client();
	~Client();
	// MAYBY TODO => void sauvegarde_fichier(std::string chemin);
	
	std::map<std::string,std::string> get_liste_option(); // getter
	void init_liste_option(); // lis le fichier de la liste des option
	void changer_liste_option(std::string nomOption,std::string nouvelleValeur);
	
	void json_vers_fichier(json::value fichier);
	void json_vers_pair(json::value fichier);
	
	void json_vers_liste_pair(json::value fichier);
	void json_vers_liste_fichier(json::value fichier);
	
	void ajouter_liste_fichier();
	void ajouter_liste_pair();
	
	void ajouter_pair();
	void ajouter_fichier();
};
#endif
