#ifndef CLIENT_H
#define CLIENT_H
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<cpprest/json.h>


#include"../mDataClass/peer.h"

using namespace web;

class Client
{
	private:
	std::string url;
	std::map<std::string,std::string> listeOption;
	std::vector<Peer> listePaire;
	std::vector<File> listeFichier;
	// TODO => fonction dans un thread qui utilise waitRequestedClient et quiva traiter les donnes recues.
	
	public:
	Client();
	~Client();
	// MAYBY TODO => void sauvegarde_fichier(std::string chemin);
	// TODO => La fonction qui recurpere au constructeur la liste des meta donnes
	
	std::map<std::string,std::string> get_liste_option(); // getter
	void init_liste_option(); // lis le fichier de la liste des option
	void changer_liste_option(std::string nomOption,std::string nouvelleValeur);
	
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
	
	int obtenir_liste_fichier(std::string, json::value, json::value&);
	int obtenir_liste_pair(std::string param, json::value entree, json::value& sortie);
	int enregistrement(std::string param, json::value entree, json::value& sortie);
	int desenregistrement(std::string urlPair, json::value entree, json::value& sortie);
};
#endif
