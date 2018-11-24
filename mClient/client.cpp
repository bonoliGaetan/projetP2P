#include "client.h"


Client::Client(ConfigPeer &config, ServiceP2P &service)
{
	std::cout<<"DEBUT CLIENT"<<std::endl;
	serviceP2P = service;
	configuration = config;
}

Client::Client() { };
Client::~Client()
{
	std::cout<<"FIN"<<std::endl;
}

void Client::obtenir_liste_pair_client(std::string dest)
{
	std::vector<Peer> liste = serviceP2P.GetPeerList(dest);
	
	for(unsigned int i = 0; i < liste.size(); i++)
	{
		listePair.push_back(liste[i]);
	}
}

void Client::obtenir_liste_fichier_client(std::string dest)
{
	std::vector<File> liste = serviceP2P.GetFileList(dest);
	int idDepart;
	int max = 0;
	int actu;
	
	if(listeFichier.empty())
	{
		idDepart = 0;
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
		
		idDepart = max + 1;
	}
	
	for(unsigned int i = 0; i < liste.size(); i++)
	{
		liste[i].id = std::to_string(max++);
		listePair.push_back(liste[i]);
	}
}

void Client::obtenir_fichier_client(std::string dest, std::string id)
{
	File fichier = serviceP2P.GetFile(dest,id);
	
	std::ifstream fic(fichier.body,std::ios::in);
	    
	fic.seekg (0, fic.end);
	int length = fic.tellg();
	fic.seekg (0, fic.beg);

	char * buffer = new char [length];

	fic.read (buffer,length);
	fic.close();
	
	std::ofstream fichier(configuration.repClient,std::ios::out);
	fichier << std::string(buffer);
	fichier.close();
}

void Client::supprimer_fichier_client(std::string dest,std::string id)
{
	serviceP2P.DeleteFile(std::string dest, std::string id);
	
	std::vector<File> nouvListe = serviceP2P.GetFileList(dest);
	
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
	serviceP2P.SaveFile(std::string dest, File file);
}

void Client::maj_fichier_client(std::string dest, File file)
{
	serviceP2P.UpdateFile(std::string dest, File file);
}

void Client::enregistrer_pair_client(std::string dest, std::string url)
{
	serviceP2P.RegisterPeer(std::string dest, std::string url);
}

void Client::desenregistrer_pair_client(std::string dest, std::string url)
{
	serviceP2P.UnregisterPeer(std::string dest, std::string url);
}

