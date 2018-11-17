#include"client.h"

std::list<Peer> Client::get_pair_liste()
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
		
		std::string contenu;
		
		while(fichier >> contenu) // On lis tout le fichier
		{	
			// TODO => On enregistre contenue dans la liste des pair
			std::cout << contenu <<std::endl;
		}
		
		fichier.close();
	}
	else
	{
		std::cout<<"Erreur lors de l'ouverture du fichier"<<std::endl;
	}
}

void Client::ajout_pair_liste(std::list<Peer> liste)
{
	;
}
