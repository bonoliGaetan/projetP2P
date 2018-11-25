#ifndef SERVEUR_H
#define SERVEUR_H
#include<iostream>
#include<string>
#include<stdio.h>

#include "../mInterfaceP2P/serviceP2P.h"
#include "../mDataClass/configPeer.h"

#define METAF "metafile.json"


#if __OPSYS == linux
	#define SL "/"
	#define SERVEURLOGS "logs/serverlogs.txt"
#elif __OPSYS == windows
	#define SL "\\"
#endif

class Serveur
{
	public:

	Serveur(ConfigPeer &cf, ServiceP2P &spp);
	Serveur();
	~Serveur();

	std::vector<File> GetFileListFromFile(std::string file);

	static int obtenir_liste_fichier(std::string, json::value, json::value&);
	static int obtenir_liste_pair(std::string param, json::value entree, json::value& sortie);
	static int enregistrement(std::string param, json::value entree, json::value& sortie);
	static int desenregistrement(std::string urlPair, json::value entree, json::value& sortie);
	static int donner_fichier(std::string nomFichier, json::value entree, json::value& sortie);
	static int supression_fichier(std::string idFichier, json::value entree, json::value& sortie);
	static int sauvegarder_fichier(std::string param, json::value entree, json::value& sortie);
	static int rafraichir_fichier(std::string idFichier, json::value entree, json::value& sortie);

	static ServiceP2P serviceP2P;
	static ConfigPeer configuration;
	
	void ajouter_liste_fichier();
	void ajouter_liste_pair();
	void ajouter_pair();
	void supprimer_pair();
	void ajouter_fichier();
	void supprimer_fichier();
	void enregistrer_fichier();
	void maj_fichier();
	
	
};


#endif
