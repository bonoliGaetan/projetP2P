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

void Client::obtenir_liste_pair_client(std::string dest)
{
	std::vector<Peer> liste = GetPeerList(dest);
	
	for(int i = 0; i < liste.size(); i++)
	{
		listePair.push_back(liste[i]);
	}
}

void Client::obtenir_liste_fichier_client(std::string dest)
{
	std::vector<File> liste = GetFileList(dest);
	int idDepart;
	int max = 0;
	int actu;
	
	if(listeFichier.empty())
	{
		idDepart = 0;
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
		
		idDepart = max + 1;
	}
	
	for(int i = 0; i < liste.size(); i++)
	{
		liste[i].id = std::to_string(max++);
		listePair.push_back(liste[i]);
	}
}

void Client::obtenir_fichier_client(std::string dest, std::string id)
{
	File fichier = GetFile(dest,id);
	
	std::ifstream fic(fichier.body,std::ios::in);
	    
	fic.seekg (0, fic.end);
	int length = fic.tellg();
	fic.seekg (0, fic.beg);

	char * buffer = new char [length];

	fic.read (buffer,length);
	fic.close();
	
	std::ofstream fichier(fichier.body,std::ios::out);
	fichier << std::string(buffer);
	fichier.close();
}

void Client::supprimer_fichier_client(std::string dest,std::string id)
{
	DeleteFile(std::string dest, std::string id);
	
	std::vector<File> nouvListe = GetFileList(dest);
	
	std::string nomFichier;
	int j;
	
	for(int i = 0; listePair.size(); i++)
	{
		if(listePair[i].url == id)
		{
			listePair[j].fileList = nouvListe;
			break;
		}
	}
	
	for(int i = 0; i < listePair[j].listeFichier.size(); i++)
	{
		if(listePair[j].listeFichier[i].id == id)
		{
			nomFichier = listePair[j].listeFichier[i].name;
			listePair[j].listeFichier.erase(i);
		}
	}
	
	
}

void Client::sauvegarder_fichier_client(std::string dest, File file)
{
	SaveFile(std::string dest, File file);
}

void Client::maj_fichier_client(std::string dest, File file)
{
	UpdateFile(std::string dest, File file);
}





