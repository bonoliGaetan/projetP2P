#include"serveur.h"

int Serveur::obtenir_liste_fichier(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des meta donnees
	sortie = liste_fichier_vers_json(listeFichier);
}

int Serveur::obtenir_liste_pair(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des pair
	sortie = liste_pair_vers_json(listePaire);
}

void Serveur::ajouter_liste_fichier()
{
	WaitGetFileList(int obtenir_liste_fichier(std::string, json::value, json::value&));
}

void Serveur::ajouter_liste_pair()
{
	WaitGetPeerList(int obtenir_liste_pair(std::string, json::value, json::value&));
}

void Serveur::ajouter_pair()
{
	WaitRegister(int enregistrement(std::string, json::value, json::value&));
}

void Serveur::supprimer_pair()
{
	WaitUnregister(int desenregistrement(std::string, json::value, json::value&));
}

int Serveur::enregistrement(std::string param, json::value entree, json::value& sortie)
{
	// On ajoute un pair a notre liste de pair
	Peer nouvPaire = json_vers_pair(entree);
	listePaire.push_bock(nouvPaire);
}

int Serveur::desenregistrement(std::string urlPair, json::value entree, json::value& sortie)
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

void Serveur::ajouter_fichier()
{
	WaitGetFile(int donner_fichier(std::string nomFichier, json::value entree, json::value& sortie));
}

int Serveur::donner_fichier(std::string nomFichier, json::value entree, json::value& sortie)
{
	std::string chemin = listeOption['Repertoire_Serveur'];
	chemin = chemin  + "/" + nomFichier;
	std::ifstream fichier(chemin,std::ifstream::in);
	
	for(int i = 0; i < listeFichier.size(); i++)
	{
		if(listeFichier[i].name == nomFichier)
		{
			sortie["size"] = listeFichier[i].size();
			break;
		}
	}
	
	sortie["body"] = fichier;
	
}

void Serveur::supprimer_fichier()
{
	WaitDeleteFile(int supression_fichier(std::string idFichier, json::value entree, json::value& sortie));
}

int supression_fichier(std::string idFichier, json::value entree, json::value& sortie)
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
	
	std::string chemin = listeOption['Repertoire_Serveur'] + "/" + nomFichier;
	
	char* cheminC = chemin.c_str();
	
	int i = remove(cheminC);
}

void Serveur::enregistrer_fichier()
{
	WaitSaveFile(int sauvegarder_fichier(std::string param, json::value entree, json::value& sortie));
}

int Serveur::sauvegarder_fichier(std::string param, json::value entree, json::value& sortie)
{
	File fichier = JsonToFile(entree);
	listeFichier.push_back(fichier);
}

void Serveur::maj_fichier()
{
	WaitUpdateFile(int rafraichir_fichier(std::string idFichier, json::value entree, json::value& sortie));
}

int rafraichir_fichier(std::string idFichier, json::value entree, json::value& sortie)
{
	// A Completer du stagiaire
}
