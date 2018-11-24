#ifndef SERVEUR_H
#define SERVEUR_H
#include<iostream>
#include<string>
#include<stdio.h>
#include"../mInterfaceP2P/serviceP2P.h"
#include"../mDataClass/configPeer.h"

class Serveur
{
	public:
	int obtenir_liste_fichier(std::string, json::value, json::value&);
	int obtenir_liste_pair(std::string param, json::value entree, json::value& sortie);
	int enregistrement(std::string param, json::value entree, json::value& sortie)
	int desenregistrement(std::string urlPair, json::value entree, json::value& sortie)
	int donner_fichier(std::string nomFichier, json::value entree, json::value& sortie)
	int supression_fichier(std::string idFichier, json::value entree, json::value& sortie)
	int sauvegarder_fichier(std::string param, json::value entree, json::value& sortie)
	int rafraichir_fichier(std::string idFichier, json::value entree, json::value& sortie)

	ServiceP2P serviceP2P;
	ConfigPeer configuration;
	
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
