#include"serveur.h"

Serveur::Serveur(ConfigPeer config, ServiceP2P service)
{
	std::cout<<"DEBUT CLIENT"<<std::endl;
	serviceP2P = service;
	configuration = config;
	
	ajouter_liste_fichier();
	ajouter_liste_pair();
	ajouter_pair();
	supprimer_pair();
	ajouter_fichier();
	supprimer_fichier();
	enregistrer_fichier();
	maj_fichier();
	
}


int Serveur::obtenir_liste_fichier(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des meta donnees
	sortie = liste_fichier_vers_json(listeFichier);
}

int Serveur::obtenir_liste_pair(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des pair
	sortie = serviceP2P.ListPeerToJson(listePair);
}

void Serveur::ajouter_liste_fichier()
{
	serviceP2P.WaitGetFileList(int obtenir_liste_fichier(std::string, json::value, json::value&));
}

void Serveur::ajouter_liste_pair()
{
	serviceP2P.WaitGetPeerList(int obtenir_liste_pair(std::string, json::value, json::value&));
}

void Serveur::ajouter_pair()
{
	serviceP2P.WaitRegister(int enregistrement(std::string, json::value, json::value&));
}

void Serveur::supprimer_pair()
{
	serviceP2P.WaitUnregister(int desenregistrement(std::string, json::value, json::value&));
}

int Serveur::enregistrement(std::string param, json::value entree, json::value& sortie)
{
	// On ajoute un pair a notre liste de pair
	Peer nouvPaire = serviceP2P.JsonToPeer(entree);
	listePair.push_bock(nouvPaire);
}

int Serveur::desenregistrement(std::string urlPair, json::value entree, json::value& sortie)
{
	// On supprime un pair de notre liste de pair
	for(int i = 0; i < listePair.size(); i++)
	{
		if(listePair[i].url == urlPair)
		{
			listePair.erase(i);
			break;
		}
	}
}

void Serveur::ajouter_fichier()
{
	serviceP2P.WaitGetFile(int donner_fichier(std::string nomFichier, json::value entree, json::value& sortie));
}

int Serveur::donner_fichier(std::string nomFichier, json::value entree, json::value& sortie)
{
	std::string chemin = configuration.repServer;
	chemin = chemin  + SL + nomFichier;
	std::ifstream fichier(chemin,std::ifstream::in);
	
	for(int i = 0; i < listeFichier.size(); i++)
	{
		if(listeFichier[i].name == nomFichier)
		{
			sortie["size"] = listeFichier[i].size();
			break;
		}
	}
	
	char* buffer;
	
	try
	{
		fichier.read(buffer,lenght);
		std::string contenu = buffer.c_str();
	}
	catch(std::exception e)
	{
		cout<<"Fichier trop gros"<<endl;
		return 0;
	}
	
	sortie["body"] = utility::conversions::to_string_t(contenu);
	
}

void Serveur::supprimer_fichier()
{
	serviceP2P.WaitDeleteFile(int supression_fichier(std::string idFichier, json::value entree, json::value& sortie));
}

int Serveur::supression_fichier(std::string idFichier, json::value entree, json::value& sortie)
{
	std::string nomFichier;
	
	for(int i = 0; i < listeFichier.size(); i++)
	{
		if(listeFichier[i].id == idFichier)
		{
			nomFichier = listeFichier[i].name;
			break;
		}
	}
	
	std::string chemin = configuration.repServer + SL + nomFichier;
	
	char* cheminC = chemin.c_str();
	
	int i = remove(cheminC);
}

void Serveur::enregistrer_fichier()
{
	serviceP2P.WaitSaveFile(int sauvegarder_fichier(std::string param, json::value entree, json::value& sortie));
}

int Serveur::sauvegarder_fichier(std::string param, json::value entree, json::value& sortie)
{
	File fichier = serviceP2P.JsonToFile(entree);
	
	int max = 0;
	int actu;
	
	if(listeFichier.empty())
	{
		fichier.id = "0";
	}
	else
	{
		for(int i = 0; i < listeFichier.size(); i++)
		{
			actu = std::stoi(listeFichier[i].id,nullptr,10);
			
			if(actu > max)
			{
				max = actu;
			}
		}
		
		std::string nouvId = std::to_string(max + 1);
		
		fichier.id = nouvId;
	}
	listeFichier.push_back(fichier);
}

void Serveur::maj_fichier()
{
	serviceP2P.WaitUpdateFile(int rafraichir_fichier(std::string idFichier, json::value entree, json::value& sortie));
}

int Serveur::rafraichir_fichier(std::string idFichier, json::value entree, json::value& sortie)
{
	// A Completer du stagiaire
}
