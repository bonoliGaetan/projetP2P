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
		configuration.listePair.push_back(liste[i]);
	}
}

void Client::obtenir_liste_fichier_client(std::string dest)
{
	std::vector<File> liste = serviceP2P.GetFileList(dest);
	
	for(unsigned int i = 0; i < configuration.listePair.size(); i++)
	{
		if(configuration.listePair[i].url == dest)
		{
			configuration.listePair[i].fileList = liste;
		}
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
	
	std::string chemin = configuration.repClient +SL +fichier.id +"_" +fichier.name;
	std::ofstream nouvFichier(chemin,std::ios::out);
	nouvFichier << std::string(buffer);
	nouvFichier.close();

	remove(fichier.body.c_str());

	delete [] buffer;
}

void Client::supprimer_fichier_client(std::string dest,std::string id)
{
	serviceP2P.DeleteFile(dest,id);
	
	std::vector<File> nouvListe = serviceP2P.GetFileList(dest);
	
	std::string nomFichier;
	int j =0;
	
	for(int i = 0; configuration.listePair.size(); i++)
	{
		if(configuration.listePair[i].url == id)
		{
			configuration.listePair[i].fileList = nouvListe;
			j = i;
			break;
		}
	}
	
	for(unsigned int i = 0; i < configuration.listePair[j].fileList.size(); i++)
	{
		if(configuration.listePair[j].fileList[i].id == id)
		{
			nomFichier = configuration.listePair[j].fileList[i].name;
			configuration.listePair[j].fileList.erase(configuration.listePair[j].fileList.begin()+i);
		}
	}	
}

void Client::sauvegarder_fichier_client(std::string dest, File file)
{
	serviceP2P.SaveFile(dest,file);
}

void Client::maj_fichier_client(std::string dest, File file)
{
	serviceP2P.UpdateFile(dest,file);
}

void Client::enregistrer_pair_client(std::string dest, std::string url)
{
	serviceP2P.RegisterPeer(dest, url);
}

void Client::desenregistrer_pair_client(std::string dest, std::string url)
{
	serviceP2P.UnregisterPeer(dest, url);
}

std::vector<File> Client::obtenir_liste_fichier_d_un_pair(std::string url)
{
	for(unsigned int i = 0; i < configuration.listePair.size(); i++)
	{
		if(configuration.listePair[i].url == url)
		{
			return configuration.listePair[i].fileList;
		}
	}
	return std::vector<File>();
}


