#include"client.h"

Client::Client()
{
	std::cout<<"DEBUT"<<std::endl;
	init_liste_option();
}

Client::~Client()
{
	std::cout<<"FIN"<<std::endl;
}

void Client::init_liste_option()
{
	// Ouverture du fichier contenant la liste des pairs.
	std::ifstream fichier("listeOption.txt",std::ifstream::in);
	
	if(fichier)
	{
		std::cout<<"Le fichier listeOption.txt s'est ouvert"<<std::endl;
		
		std::string clef;
		std::string egale;
		std::string valeur;
		
		while(fichier >> clef && fichier >> egale) // On lis tout le fichier
		{	
			// On enregistre contenue dans la liste des pair
			if(egale == "==")
			{
				std::string valeurFinal = "";
				
				while(fichier >> valeur)
				{
					if(valeur == "\"") break;
					
					if(valeurFinal == "") valeurFinal = valeurFinal + valeur;
					
					else valeurFinal = valeurFinal + " " + valeur;
				}
				listeOption[clef] = valeurFinal;
			}
			else
			{
				fichier >> valeur;
				listeOption[clef] = valeur;
			}
		}
		
		fichier.close();
	}
	else
	{
		std::cout<<"Erreur lors de l'ouverture du fichier"<<std::endl;
	}
}

void Client::changer_liste_option(std::string nomOption,std::string nouvelleValeur)
{
	listeOption.erase(nomOption);
	listeOption[nomOption] = nouvelleValeur;
}

std::map<std::string,std::string> Client::get_liste_option()
{
	return listeOption;
}

void Client::ajouter_liste_fichier()
{
	WaitGetFileList(int obtenir_liste_fichier(std::string, json::value, json::value&));
}

void Client::ajouter_liste_pair()
{
	WaitGetPeerList(int obtenir_liste_pair(std::string, json::value, json::value&));
}

void Client::ajouter_pair()
{
	WaitRegister(int enregistrement(std::string, json::value, json::value&));
}

void Client::supprimer_pair()
{
	WaitUnregister(int desenregistrement(std::string, json::value, json::value&));
}

int Client::obtenir_liste_fichier(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des meta donnees
	sortie = liste_fichier_vers_json(listeFichier);
}

int Client::obtenir_liste_pair(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des pair
	sortie = liste_pair_vers_json(listePaire);
}

int Client::enregistrement(std::string param, json::value entree, json::value& sortie)
{
	// On ajoute un pair a notre liste de pair
	Peer nouvPaire = json_vers_pair(entree);
	listePaire.push_bock(nouvPaire);
}

int Client::desenregistrement(std::string urlPair, json::value entree, json::value& sortie)
{
	// On supprime un pair de notre liste de pair
	for(int i = 0; i < listePaire.size(); i++)
	{
		if(listePair[i].url == urlPair)
		{
			listePaire.erase(i);
			break;
		}
	}
}


