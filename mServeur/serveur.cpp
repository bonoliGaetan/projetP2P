#include"serveur.h"

Serveur::Serveur(ConfigPeer &config, ServiceP2P &service)
{
	std::cout<<"DEBUT CLIENT"<<std::endl;
	serviceP2P = service;
	configuration = config;
	
	std::cout << "Le serveur écoute sur : " << config.myUrl << std::endl;

	ajouter_liste_fichier();
	ajouter_liste_pair();
	ajouter_pair();
	supprimer_pair();
	ajouter_fichier();
	supprimer_fichier();
	enregistrer_fichier();
	maj_fichier();
	
}

Serveur::Serveur() { }
Serveur::~Serveur() { }

int Serveur::obtenir_liste_fichier(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des meta donnees
	sortie = serviceP2P.ListFileToJson(listeFichier);
	return 0;
}

int Serveur::obtenir_liste_pair(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des pair
	sortie = serviceP2P.ListPeerToJson(listePair);
	return 0;
}

void Serveur::ajouter_liste_fichier()
{
	serviceP2P.WaitGetFileList(&(Serveur::obtenir_liste_fichier));
}

void Serveur::ajouter_liste_pair()
{
	serviceP2P.WaitGetPeerList(&(Serveur::obtenir_liste_pair));
}

void Serveur::ajouter_pair()
{
	serviceP2P.WaitRegister(&(Serveur::enregistrement));
}

void Serveur::supprimer_pair()
{
	serviceP2P.WaitUnregister(&(Serveur::desenregistrement));
}

int Serveur::enregistrement(std::string param, json::value entree, json::value& sortie)
{
	// On ajoute un pair a notre liste de pair
	Peer nouvPaire = serviceP2P.JsonToPeer(entree);
	listePair.push_back(nouvPaire);
	return 0;
}

int Serveur::desenregistrement(std::string urlPair, json::value entree, json::value& sortie)
{
	// On supprime un pair de notre liste de pair
	for(unsigned int i = 0; i < listePair.size(); i++)
	{
		if(listePair[i].url == urlPair)
		{
			listePair.erase(listePair.begin()+i);
			break;
		}
	}
	return 0;
}

void Serveur::ajouter_fichier()
{
	serviceP2P.WaitGetFile(&(Serveur::donner_fichier));
}

int Serveur::donner_fichier(std::string nomFichier, json::value entree, json::value& sortie)
{
	std::string chemin = configuration.repServer;
	chemin = chemin  + SL + nomFichier;
	std::ifstream fichier(chemin,std::ifstream::in);
	
	for(unsigned int i = 0; i < listeFichier.size(); i++)
	{
		if(listeFichier[i].name == nomFichier)
		{
			sortie["size"] = listeFichier[i].size;
			break;
		}
	}
	
	
	
	try
	{	
		fichier.seekg (0, fichier.end);
	    int length = fichier.tellg();
	    fichier.seekg (0, fichier.beg);

	    char* buffer = new char[length];

		fichier.read(buffer,length);
		std::string contenu(buffer);
		sortie["body"] = json::value::string(contenu);

		delete [] buffer;
	}
	catch(std::exception e)
	{
		std::cout<<"Fichier trop gros"<<std::endl;
		return 0;
	}
	
	

	return 0;
	
}

void Serveur::supprimer_fichier()
{
	serviceP2P.WaitDeleteFile(&(Serveur::supression_fichier));
}

int Serveur::supression_fichier(std::string idFichier, json::value entree, json::value& sortie)
{
	std::string nomFichier;
	
	for(unsigned int i = 0; i < listeFichier.size(); i++)
	{
		if(listeFichier[i].id == idFichier)
		{
			nomFichier = listeFichier[i].name;
			break;
		}
	}
	
	std::string chemin = configuration.repServer + SL + nomFichier;
	
	remove(chemin.c_str());
	return 0;
}

void Serveur::enregistrer_fichier()
{
	serviceP2P.WaitSaveFile(&(Serveur::sauvegarder_fichier));
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
		for(unsigned int i = 0; i < listeFichier.size(); i++)
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
	return 0;
}

void Serveur::maj_fichier()
{
	serviceP2P.WaitUpdateFile(&(Serveur::rafraichir_fichier));
}

int Serveur::rafraichir_fichier(std::string idFichier, json::value entree, json::value& sortie)
{
	// A Completer du stagiaire
	return 0;
}
