#include"client.h"

std::vector<Peer> Client::get_pair_liste()
{
	return pairListe;
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
	int estDansListe = 0;
	
	for(unsigned int i = 0; i < liste.size(); i++)
	{
		for(unsigned int j = 0; j < pairListe.size(); j++)
		{
			if(liste[i].url == pairListe[j].url)
			{
				estDansListe = 1;
				break;
			}
			
		}
		
		if(estDansListe == 0)
		{
			std::cout<< liste[i].url << " A ETE AJOUTER"<<std::endl;
			pairListe.push_back(liste[i]);
		}
		else
		{
			std::cout<< liste[i].url << " est deja dans votre liste"<<std::endl;
			estDansListe = 0;
		}
	}
}

void Client::ecriture_fichier_liste_pair()
{
	std::ofstream fichier("listePaire.txt");
	
	if(fichier)
	{
		for(unsigned int i = 0; i < pairListe.size(); i++)
		{
			fichier<< pairListe[i].url << " " << pairListe[i].nom<<std::endl;
		}
	}
	else
	{
		std::cout<<"Probleme lors de l'ouverture du fichier"<<std::endl;
	}
}
