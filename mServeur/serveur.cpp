#include"serveur.h"

SerServerP2P* Serveur::serviceP2P;
ConfigPeer* Serveur::configuration;
std::vector<File> Serveur::listeFichier = std::vector<File>();
std::vector<Peer> Serveur::listePair = std::vector<Peer>();
int Serveur::spaceUsed = 0;

Serveur::Serveur(ConfigPeer* config)
{
	Serveur::serviceP2P = new SerServerP2P(config);
	Serveur::configuration = config;
	
	Peer myPeer(configuration->myUrl);
	
	Serveur::GetMetaData(METAF);

	myPeer.fileList = Serveur::listeFichier;
	Serveur::listePair.push_back(myPeer);

	SetWaitUpdateFile();
	SetWaitSaveFile();
	SetWaitDeleteFile();
	SetWaitGetFile();
	SetWaitUnregister();
	SetWaitRegister();
	SetWaitGetPeerList();
	SetWaitGetFileList();	
}

Serveur::Serveur()
{
	std::cout << "END SERVEUR" << std::endl;
}
Serveur::~Serveur() 
{	
	Serveur::SaveMetaData(METAF);
	Serveur::serviceP2P->CloseListener();
}

void Serveur::SaveMetaData(std::string fileName)
{
	json::value sval = json::value::object();

	sval["space"] = json::value::number(Serveur::spaceUsed);

	int cpt ;
	std::vector<File>::iterator it;
	json::value jfileList = json::value::array();
	
	for(it = Serveur::listeFichier.begin(), cpt = 0 ; it != Serveur::listeFichier.end(); ++it, ++cpt )
	{
		jfileList[cpt] = it->ToJson(1);
	}
	sval["list"] = jfileList;

	std::ofstream metafile(fileName,std::ios::out);
	metafile << sval.serialize() << std::endl;
	metafile.close();
}

void Serveur::GetMetaData(std::string fileName)
{
	std::ifstream sfile(fileName,std::ios::in);
	if(!sfile)
		return;

    sfile.seekg (0, sfile.end);
    int length = sfile.tellg();
    sfile.seekg (0, sfile.beg);

    char* buffer = new char [length+1];

    sfile.read (buffer,length);
    buffer[length] = '\0';

    std::ofstream logFile(SERVEURLOGS,std::ios::app);
    logFile << buffer << std::endl;
	logFile.close();

    string_t str(buffer);
    json::value jret = json::value::parse(str);

    logFile = std::ofstream(SERVEURLOGS,std::ios::app);
    logFile << jret.serialize() << std::endl;
	logFile.close();

    delete[] buffer;
    sfile.close();
	
    Serveur::spaceUsed = GetJsonInt(jret,"space");
	json::value jlist = jret["list"];
	Serveur::listeFichier.empty();
	for(int i = 0; jlist[i] != json::value::null() ; ++i)
		Serveur::listeFichier.push_back(File::FromJson(jlist[i]));

}



void Serveur::SetWaitGetFileList()
{
	Serveur::serviceP2P->WaitGetFileList(&(Serveur::obtenir_liste_fichier));
}

void Serveur::SetWaitGetPeerList()
{
	Serveur::serviceP2P->WaitGetPeerList(&(Serveur::obtenir_liste_pair));
}

void Serveur::SetWaitRegister()
{
	Serveur::serviceP2P->WaitRegister(&(Serveur::enregistrement));
}

void Serveur::SetWaitUnregister()
{
	Serveur::serviceP2P->WaitUnregister(&(Serveur::desenregistrement));
}

void Serveur::SetWaitGetFile()
{
	Serveur::serviceP2P->WaitGetFile(&(Serveur::donner_fichier));
}

void Serveur::SetWaitDeleteFile()
{
	Serveur::serviceP2P->WaitDeleteFile(&(Serveur::supression_fichier));
}

void Serveur::SetWaitSaveFile()
{
	Serveur::serviceP2P->WaitSaveFile(&(Serveur::sauvegarder_fichier));
}

void Serveur::SetWaitUpdateFile()
{
	Serveur::serviceP2P->WaitUpdateFile(&(Serveur::rafraichir_fichier));
}

int Serveur::enregistrement(std::string param, json::value entree, json::value& sortie)
{
	// On ajoute un pair a notre liste de pair
	Peer nouvPair(GetJsonString(entree,"url"));
	
	std::vector<Peer>::iterator it;
	for(it = Serveur::listePair.begin(); it != Serveur::listePair.end(); ++it)
		if(it->url == nouvPair.url)
			break;
	if(it == Serveur::listePair.end())
	{
		Serveur::listePair.push_back(nouvPair);
		return 0;
	}

	return -1;
}

int Serveur::desenregistrement(std::string urlPair, json::value entree, json::value& sortie)
{
	// On supprime un pair de notre liste de pair
	Peer pair(GetJsonString(entree,"url"));
	std::vector<Peer>::iterator it;
	for( it = Serveur::listePair.begin(); it != Serveur::listePair.end(); ++it)
	{
		if(it->url == pair.url)
		{
			Serveur::listePair.erase(it);
			return 0;
			break;
		}
	}
	return -1;
}

int Serveur::donner_fichier(std::string id, json::value entree, json::value& sortie)
{
	std::vector<File>::iterator it;
	for( it = Serveur::listeFichier.begin(); it != Serveur::listeFichier.end(); ++it)
	{
		if(it->id == id)
		{
			break;
		}
	}
	if(it == Serveur::listeFichier.end())
		return -1;
	
	try
	{	
		std::string chemin = Serveur::configuration->repServer +SL +it->body;
		
		std::ifstream fichier(chemin,std::ifstream::in);

		fichier.seekg (0, fichier.end);
	    int length = fichier.tellg();
	    fichier.seekg (0, fichier.beg);

	    char* buffer = new char[length];

		fichier.read(buffer,length);
		std::string contenu(buffer);

		it->size = length;
		//sortie["size"] = json::value::string(std::to_string(length));
		//sortie["name"] = json::value::string(Serveur::configuration->listeFichier[i].name);
		sortie["content"] = json::value::string(contenu);
		
		delete [] buffer;
		fichier.close();
	}
	catch(std::exception e)
	{
		std::ofstream logFile = std::ofstream(SERVEURLOGS,std::ios::app);
	    logFile << e.what() << std::endl;
		logFile.close();
		return -1;
	}	

	return 0;
}



int Serveur::supression_fichier(std::string idFichier, json::value entree, json::value& sortie)
{
	std::vector<File>::iterator it;
	std::string nomFichier;

	for(it = Serveur::listeFichier.begin(); it != Serveur::listeFichier.end(); ++it)
	{
		if(it->id == idFichier)
		{
			nomFichier = it->name;
			break;
		}
	}
	if(it == Serveur::listeFichier.end())
		return -1;

	std::string chemin = Serveur::configuration->repServer + SL + it->body;
	remove(chemin.c_str());
	Serveur::listeFichier.erase(it);

	Serveur::SaveMetaData(METAF);

	return 0;
}


int Serveur::sauvegarder_fichier(std::string param, json::value entree, json::value& sortie)
{
	File fichier = File::FromJson(entree);
	
	std::vector<File>::iterator it;
	for(it = Serveur::listeFichier.begin(); it != Serveur::listeFichier.end(); ++it)
	{
		if(it->id == fichier.id)
		{
			return -1;
		}
	}

	fichier.body = fichier.id + "-" + fichier.name;	
	Serveur::listeFichier.push_back(fichier);

	Serveur::SaveMetaData(METAF);

	return 0;
}



int Serveur::rafraichir_fichier(std::string idFichier, json::value entree, json::value& sortie)
{
	std::vector<File>::iterator it;
	for(it = Serveur::listeFichier.begin(); it != Serveur::listeFichier.end(); ++it)
	{
		if(it->id == idFichier)
		{
			break;
		}
	}
	if(it == Serveur::listeFichier.end())
		return -1;

	std::string chemin = Serveur::configuration->repServer + SL + it->body;
	if(Serveur::spaceUsed + (int) GetJsonString(entree,"content").size() > Serveur::configuration->tailleMaxRepServer)
	{
		Serveur::listeFichier.erase(it);
		return -1;
	}
	Serveur::spaceUsed += GetJsonString(entree,"content").size();

	std::ofstream of(chemin,std::ios::out);
	of << GetJsonString(entree,"content");
	of.close();

	Serveur::SaveMetaData(METAF);

	return 0;
}

int Serveur::obtenir_liste_fichier(std::string param, json::value entree, json::value& sortie)
{
	json::value sval = json::value::object();
	std::vector<File>::iterator it;
	json::value jfileList = json::value::array();
	int cpt;

	for(it = Serveur::listeFichier.begin(), cpt = 0 ; it != Serveur::listeFichier.end(); ++it, ++cpt )
	{
		jfileList[cpt] = it->ToJson(0);
	}
	sval["list"] = jfileList;
	sortie = sval;
	
	return 0;
}

int Serveur::obtenir_liste_pair(std::string param, json::value entree, json::value& sortie)
{
	json::value sval = json::value::object();
	std::vector<Peer>::iterator it;
	json::value jPeerList = json::value::array();
	int cpt;

	for(it = Serveur::listePair.begin(), cpt = 0 ; it != Serveur::listePair.end(); ++it, ++cpt )
	{
		jPeerList[cpt] = json::value::string(it->url);
	}
	sval["list"] = jPeerList;
	sortie = sval;

	return 0;
}

void Serveur::Open()
{
	Serveur::serviceP2P->OpenListener();
}

void Serveur::Close()
{
	Serveur::serviceP2P->CloseListener();
}