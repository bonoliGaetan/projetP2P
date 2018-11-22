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




