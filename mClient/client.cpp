#include"client.h"

std::vector<Peer> Client::get_pair_liste()
{
	return pairListe;
}

void Client::sauvegarde_fichier(std::string param)
{
	;
}

void Client::init_pair_liste()
{
	// Ouverture du fichier contenant la liste des pairs.
	std::ifstream fichier("listePaire.txt",std::ifstream::in);
	
	if(fichier)
	{
		std::cout<<"Le fichier listePaire.txt s'est ouvert"<<std::endl;
		
		std::string url;
		std::string nom;
		
		while(fichier >> url && fichier >> nom) // On lis tout le fichier
		{	
			// On enregistre contenue dans la liste des pair
			Peer pair;
			pair.url = url;
			pair.nom = nom;
			
			pairListe.push_back(pair);
		}
		
		fichier.close();
	}
	else
	{
		std::cout<<"Erreur lors de l'ouverture du fichier"<<std::endl;
	}
}

void Client::ajout_pair_liste(std::vector<Peer> liste)
{
	;
}
