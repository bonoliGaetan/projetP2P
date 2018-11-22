#ifndef SERVEUR_H
#define SERVEUR_H
#include<iostream>
#include<string>
#include<stdio.h>

class Serveur
{
	public:
	int obtenir_liste_fichier(std::string, json::value, json::value&);
	int obtenir_liste_pair(std::string param, json::value entree, json::value& sortie);
	
	
};




#endif
