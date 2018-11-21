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


void Client::json_vers_fichier(json::value fichier)
{
	printf("LECTURE JSSSSSOOOOOONNNNN\n");
	
	utility::string_t size = "Size";
	utility::string_t name = "Name";
	utility::string_t id = "Id";
	utility::string_t data = "Data";
	
	json::value a = fichier.at(size);
	json::value b = fichier.at(name);
	json::value c = fichier.at(id);
	json::value d = fichier.at(data);
	
	std::cout<<a<<std::endl<<b<<std::endl<<c<<std::endl<<d<<std::endl;
}

/*void Client::ajouter_liste_fichier()
{
	json::value entree;
	json::value sortie;
	
	WaitFileList(int fctTraitement("???", entree, sortie));
	
	File = json_vers_fichier(sortie);
	
	// Ajouter le fichier dans le chemin client
}

void Client::ajouter_liste_pair()
{
	json::value entree;
	json::value sortie;
	
	WaitPeerList(int fctTraitement("???", entree, sortie));
	
	std::vector<Peer> liste = json_vers_liste_paire(sortie);
	
	for(int i = 0; i < listePair.size(); i++)
	{
		listePaire.push_back(liste[i]);
	}
}

void Client::ajouter_pair()
{
	json::value entree;
	json::value sortie;
	
	WaitRegister(int fctTraitement("???", entree, sortie));
	
	Peer paire = json_vers_pair(sortie);
	
	listePaire.push_back(paire);
}

void Client::supprimer_pair()
{
	json::value entree;
	json::value sortie;
	
	WaitUnregister(int fctTraitement("???", entree, sortie));
	
	Peer paire = json_vers_pair(sortie);
	
	listePaire.push_back(paire);
	
	for(int i = 0; i < listePaire.size(); i++)
	{
		if(pair.url == listePaire[i].url)
		{
			listePaire.erase(i);
			break;
		}
	}
	
	
}*/





