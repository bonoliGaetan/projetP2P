#include "client.h"


Client::Client(ConfigPeer* config)
{
	std::cout<<"DEBUT CLIENT"<<std::endl;
	this->serviceP2P = SerClientP2P(config);
	this->configuration = config;

	printf("CLIENT LANCER\n");
}

Client::Client() { };
Client::~Client()
{
	std::cout<<"FIN"<<std::endl;
}

void Client::obtenir_liste_pair_client(std::string dest)
{

	std::vector<Peer> liste = serviceP2P.GetPeerList(dest);

	if(suppr_peer_if_notfound(dest))
		return;

	std::vector<Peer>::iterator it;
	std::vector<Peer>::iterator it2;
	for(it = liste.begin(); it != liste.end(); ++it)
	{
		for(it2 = configuration->listePair.begin(); it2 != configuration->listePair.end(); ++it2)
			if(it->url == it2->url)
				break;
		if(it2 == configuration->listePair.end())
		{
			configuration->listePair.push_back(*it);
		}
	}
}

void Client::obtenir_liste_fichier_client(std::string dest)
{
	std::vector<File> liste = serviceP2P.GetFileList(dest);
	if(suppr_peer_if_notfound(dest))
		return;
	
	std::vector<Peer>::iterator it;

	for(it = configuration->listePair.begin(); it != configuration->listePair.end(); ++it)
	{
		if(it->url == dest)
		{
			it->fileList = liste;
		}
	}
}

void Client::obtenir_fichier_client(std::string dest, std::string id)
{
	File fichier = serviceP2P.GetFile(dest,id);

	if(suppr_peer_if_notfound(dest))
		return;
	
	//sauvegarder_fichier_client(configuration->myUrl,fichier);

	std::ifstream fic(fichier.body,std::ios::in);
	    
	fic.seekg (0, fic.end);
	int length = fic.tellg();
	fic.seekg (0, fic.beg);

	char * buffer = new char [length];

	fic.read (buffer,length);
	fic.close();
	
	std::string chemin = configuration->repClient +SL +fichier.id +"_" +fichier.name;
	std::ofstream nouvFichier(chemin,std::ios::out);
	nouvFichier << std::string(buffer);
	nouvFichier.close();

	remove(fichier.body.c_str());

	delete [] buffer;
}

void Client::supprimer_fichier_client(std::string dest,std::string id)
{
	serviceP2P.DeleteFile(dest,id);

	if(suppr_peer_if_notfound(dest))
		return;
	
	obtenir_liste_fichier_d_un_pair(dest);

}

void Client::sauvegarder_fichier_client(std::string dest, File file)
{
	std::ifstream fic(file.body,std::ios::in);

	fic.seekg (0, fic.end);
	file.size = fic.tellg();
	fic.seekg (0, fic.beg);

	fic.close();

	file.id = affecter_id(configuration->id,file.name,file.size,10);
	serviceP2P.SaveFile(dest,file);

	suppr_peer_if_notfound(dest);
}

void Client::maj_fichier_client(std::string dest, File file)
{
	serviceP2P.UpdateFile(dest,file);

	suppr_peer_if_notfound(dest);
}

void Client::enregistrer_pair_client(std::string dest, std::string url)
{
	serviceP2P.RegisterPeer(dest, url);

	suppr_peer_if_notfound(dest);
}

void Client::desenregistrer_pair_client(std::string dest, std::string url)
{
	serviceP2P.UnregisterPeer(dest, url);

	suppr_peer_if_notfound(dest);
}

std::vector<File> Client::obtenir_liste_fichier_d_un_pair(std::string url)
{
	for(unsigned int i = 0; i < configuration->listePair.size(); i++)
	{
		if(configuration->listePair[i].url == url)
		{
			return configuration->listePair[i].fileList;
		}
	}
	return std::vector<File>();
}

int Client::suppr_peer_if_notfound(std::string url)
{
	if(serviceP2P.lastResponse.code == -1)
	{
		std::vector<Peer>::iterator it;
		for( it = configuration->listePair.begin(); it != configuration->listePair.end(); ++it)
		{
			if(it->url == url)
			{
				configuration->listePair.erase(it);
				return 1;
			}
		}
	}
	return 0;
}


std::string Client::affecter_id(int pairId, std::string nomFic, int tailleFic, int taille)
{
	char carac[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const char* nom = nomFic.c_str();
	int graine = 0;
	unsigned int i ;
	
	for(i = 0; i < nomFic.size(); i++)
	{
		graine += nom[i] * (1000 + i * 100);
	}
	
	graine += 1000000 * pairId;
	
	graine += tailleFic;
	
	srand(graine);
	
	int alea;
	char chaine[taille+1];
	
	for(int j = 0; j < taille ; j++)
	{
		alea = rand()%62;
		chaine[j] = carac[alea];
	}
	chaine[taille] = '\0';
	std::string resultat = chaine;
	
	return resultat;
}




