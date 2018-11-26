#include"serveur.h"

ServiceP2P Serveur::serviceP2P;
ConfigPeer Serveur::configuration;

Serveur::Serveur(ConfigPeer &config, ServiceP2P &service)
{
	std::cout<<"DEBUT SERVER"<<std::endl;
	Serveur::serviceP2P = service;
	Serveur::configuration = config;

	Peer myPeer;
	myPeer.url = configuration.myUrl;
	myPeer.name = "myPeer";
	
	myPeer.fileList = GetFileListFromFile(METAF);

	configuration.listeFichier = myPeer.fileList;
	configuration.listePair.push_back(myPeer);

	ajouter_liste_fichier();
	ajouter_liste_pair();
	ajouter_pair();
	supprimer_pair();
	ajouter_fichier();
	supprimer_fichier();
	enregistrer_fichier();
	maj_fichier();

	std::cout << "Le serveur écoute sur : " << config.myUrl << std::endl;
	
}

Serveur::Serveur() { }
Serveur::~Serveur() 
{	
	json::value sval;

	sval["size"] = configuration.listeFichier.size();

	int cpt ;
	std::vector<File>::iterator it;
	json::value jfileList = json::value::array();
	for(it = configuration.listeFichier.begin(), cpt = 0 ; it != configuration.listeFichier.end(); ++it, ++cpt )
	{
		jfileList[cpt] = serviceP2P.FileToJson(*it);
		jfileList[cpt]["body"] = json::value::string(it->body);
	}
	sval["fileList"] = jfileList;

	std::ofstream metafile(METAF,std::ios::out);
	metafile << sval.serialize();
	metafile.close();

	serviceP2P.CloseAllWaitServer();
}

int Serveur::obtenir_liste_fichier(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des meta donnees
	sortie = Serveur::serviceP2P.ListFileToJson(Serveur::configuration.listeFichier);
	return 0;
}

int Serveur::obtenir_liste_pair(std::string param, json::value entree, json::value& sortie)
{
	// On envoit la liste des pair
	sortie = Serveur::serviceP2P.ListPeerToJson(Serveur::configuration.listePair);
	return 0;
}

void Serveur::ajouter_liste_fichier()
{

	Serveur::serviceP2P.WaitGetFileList(&(Serveur::obtenir_liste_fichier));

}

void Serveur::ajouter_liste_pair()
{
	Serveur::serviceP2P.WaitGetPeerList(&(Serveur::obtenir_liste_pair));
}

void Serveur::ajouter_pair()
{
	Serveur::serviceP2P.WaitRegister(&(Serveur::enregistrement));
}

void Serveur::supprimer_pair()
{
	Serveur::serviceP2P.WaitUnregister(&(Serveur::desenregistrement));
}

int Serveur::enregistrement(std::string param, json::value entree, json::value& sortie)
{
	// On ajoute un pair a notre liste de pair
	Peer nouvPaire = Serveur::serviceP2P.JsonToPeer(entree);
	Serveur::configuration.listePair.push_back(nouvPaire);
	return 0;
}

int Serveur::desenregistrement(std::string urlPair, json::value entree, json::value& sortie)
{
	// On supprime un pair de notre liste de pair
	
	for(unsigned int i = 0; i < Serveur::configuration.listePair.size(); i++)
	{
		if(Serveur::configuration.listePair[i].url == urlPair)
		{
			Serveur::configuration.listePair.erase(Serveur::configuration.listePair.begin()+i);
			break;
		}
	}
	return 0;
}

void Serveur::ajouter_fichier()
{
	Serveur::serviceP2P.WaitGetFile(&(Serveur::donner_fichier));
}

int Serveur::donner_fichier(std::string id, json::value entree, json::value& sortie)
{
	
	unsigned int i;
	for( i = 0; i < Serveur::configuration.listeFichier.size(); i++)
	{
		if(Serveur::configuration.listeFichier[i].id == id)
		{
			break;
		}
	}
	
	try
	{	
		std::string chemin = Serveur::configuration.repServer +SL +Serveur::configuration.listeFichier[i].body;
		
		std::ifstream fichier(chemin,std::ifstream::in);

		fichier.seekg (0, fichier.end);
	    int length = fichier.tellg();
	    fichier.seekg (0, fichier.beg);

	    char* buffer = new char[length];

		fichier.read(buffer,length);
		std::string contenu(buffer);

		Serveur::configuration.listeFichier[i].size = length;
		sortie["size"] = json::value::string(std::to_string(length));
		sortie["name"] = json::value::string(Serveur::configuration.listeFichier[i].name);
		sortie["body"] = json::value::string(contenu);
		

		delete [] buffer;
		fichier.close();
	}
	catch(std::exception e)
	{
		std::cout<<"Fichier trop gros // pas trouvé"<<std::endl;
		return 0;
	}	

	return 0;
}

void Serveur::supprimer_fichier()
{
	Serveur::serviceP2P.WaitDeleteFile(&(Serveur::supression_fichier));
}

int Serveur::supression_fichier(std::string idFichier, json::value entree, json::value& sortie)
{
	std::string nomFichier;
	
	for(unsigned int i = 0; i < Serveur::configuration.listeFichier.size(); i++)
	{
		if(Serveur::configuration.listeFichier[i].id == idFichier)
		{
			nomFichier = Serveur::configuration.listeFichier[i].name;
			break;
		}
	}
	
	std::string chemin = Serveur::configuration.repServer + SL + nomFichier;
	
	remove(chemin.c_str());
	return 0;
}

void Serveur::enregistrer_fichier()
{
	Serveur::serviceP2P.WaitSaveFile(&(Serveur::sauvegarder_fichier));
}

int Serveur::sauvegarder_fichier(std::string param, json::value entree, json::value& sortie)
{
	std::ofstream logFile(SERVEURLOGS,std::ios::app);
	logFile << "Save File Meta" << std::endl;
	logFile.close();

	File fichier = serviceP2P.JsonToFile(entree);

	int max = -1;
	int actu;

	unsigned int i;
	for(i = 0; i < Serveur::configuration.listeFichier.size(); i++)
	{
		actu = std::stoi(Serveur::configuration.listeFichier[i].id,nullptr,10);
	
		if(actu > max)
		{
			max = actu;
		}
	}
		
	std::string nouvId = std::to_string(max + 1);
	
	fichier.id = nouvId;
	fichier.name = GetJsonString(entree,"name");
	fichier.body = fichier.name +"_" +fichier.id;

	std::cout << "Fichier ajouter : ID = " << fichier.id << std::endl;
	sortie["id"] = json::value::string(fichier.id);
	Serveur::configuration.listeFichier.push_back(fichier);
	return 0;
}

void Serveur::maj_fichier()
{
	Serveur::serviceP2P.WaitUpdateFile(&(Serveur::rafraichir_fichier));
}

int Serveur::rafraichir_fichier(std::string idFichier, json::value entree, json::value& sortie)
{
	std::ofstream logFile(SERVEURLOGS,std::ios::app);
	logFile << "Save File Body" << std::endl;
	logFile.close();

	unsigned int i;
	for(i = 0; i < Serveur::configuration.listeFichier.size(); i++)
	{
		if(Serveur::configuration.listeFichier[i].id == idFichier)
		{
			break;
		}
	}
	
	std::string chemin = Serveur::configuration.repServer + SL + Serveur::configuration.listeFichier[i].body;

	std::ofstream of(chemin,std::ios::out);
	of << GetJsonString(entree,"body");
	of.close();

	return 0;
}

std::vector<File> Serveur::GetFileListFromFile(std::string file)
{
	try {

		std::ifstream sfile(file,std::ios::in);
		if(!sfile)
			return std::vector<File>();

	    // get length of file:
	    sfile.seekg (0, sfile.end);
	    int length = sfile.tellg();
	    sfile.seekg (0, sfile.beg);

	    char * buffer = new char [length];

	    // read data as a block:
	    sfile.read (buffer,length);
	    sfile.close();

	    std::ofstream logFile(SERVEURLOGS,std::ios::app);
	    logFile << buffer << std::endl;
		logFile.close();

	    string_t str(buffer);
	    // ...buffer contains the entire file...
	    json::value jret = json::value::parse(str);

	    logFile = std::ofstream(SERVEURLOGS,std::ios::app);
	    logFile << jret.serialize() << std::endl;
		logFile.close();

	    delete[] buffer;

	    return Serveur::serviceP2P.JsonToListFile(jret);
	}catch(json::json_exception je)
	{
		std::cout << "Erreur de lecture du fichier de fichiers" << std::endl;
		exit(0);
	}
}