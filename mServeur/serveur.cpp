#include"serveur.h"

SerServerP2P Serveur::serviceP2P;
ConfigPeer Serveur::configuration;

Serveur::Serveur(ConfigPeer &config, SerServerP2P &service)
{
	std::cout<<"DEBUT SERVER"<<std::endl;
	Serveur::serviceP2P = service;
	Serveur::configuration = config;

	Peer myPeer;
	myPeer.url = configuration.myUrl;
	
	myPeer.fileList = GetFileListFromFile(METAF);

	configuration.listeFichier = myPeer.fileList;
	configuration.listePair.push_back(myPeer);

	maj_fichier();
	supprimer_fichier();
	ajouter_fichier();

	enregistrer_fichier();
	ajouter_liste_fichier();
	
	ajouter_liste_pair();
	ajouter_pair();
	supprimer_pair();

	Serveur::serviceP2P.OpenListener();

	std::cout << "Le serveur écoute sur : " << config.myUrl << std::endl;
	
}

Serveur::Serveur() { }
Serveur::~Serveur() 
{	
	json::value sval = json::value::object();

	sval["size"] = configuration.listeFichier.size();

	int cpt ;
	std::vector<File>::iterator it;
	json::value jfileList = json::value::array();
	
	for(it = configuration.listeFichier.begin(), cpt = 0 ; it != configuration.listeFichier.end(); ++it, ++cpt )
	{
		jfileList[cpt] = it->ToJson(1);
	}
	sval["list"] = jfileList;

	std::ofstream metafile(METAF,std::ios::out);
	metafile << sval.serialize() << std::endl;
	metafile.close();

	Serveur::serviceP2P.CloseListener();
}

int Serveur::obtenir_liste_fichier(std::string param, json::value entree, json::value& sortie)
{
	json::value sval = json::value::object();
	std::vector<File>::iterator it;
	json::value jfileList = json::value::array();
	int cpt;

	for(it = Serveur::configuration.listeFichier.begin(), cpt = 0 ; it != Serveur::configuration.listeFichier.end(); ++it, ++cpt )
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

	for(it = Serveur::configuration.listePair.begin(), cpt = 0 ; it != Serveur::configuration.listePair.end(); ++it, ++cpt )
	{
		jPeerList[cpt] = it->ToJson();
	}
	sval["list"] = jPeerList;
	sortie = sval;

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
	Peer nouvPaire = Peer::FromJson(entree);
	Serveur::configuration.listePair.push_back(nouvPaire);
	
	return 0;
}

int Serveur::desenregistrement(std::string urlPair, json::value entree, json::value& sortie)
{
	// On supprime un pair de notre liste de pair
	Peer pair = Peer::FromJson(entree);
	for(unsigned int i = 0; i < Serveur::configuration.listePair.size(); i++)
	{
		if(Serveur::configuration.listePair[i].url == pair.url)
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
	for(i = 0; i < Serveur::configuration.listeFichier.size(); i++)
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
		//sortie["size"] = json::value::string(std::to_string(length));
		//sortie["name"] = json::value::string(Serveur::configuration.listeFichier[i].name);
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

	File fichier = File::FromJson(entree);
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
	unsigned int i;
	for(i = 0; i < Serveur::configuration.listeFichier.size(); i++)
	{
		if(Serveur::configuration.listeFichier[i].id == idFichier)
		{
			break;
		}
	}

	if(i >= Serveur::configuration.listeFichier.size())
		return -1;
	
	std::string chemin = Serveur::configuration.repServer + SL + Serveur::configuration.listeFichier[i].body;

	std::ofstream of(chemin,std::ios::out);
	of << GetJsonString(entree,"body");
	of.close();

	return 0;
}

std::vector<File> Serveur::GetFileListFromFile(std::string file)
{
	std::ifstream sfile(file,std::ios::in);
	if(!sfile)
		return std::vector<File>();

    // get length of file:
    sfile.seekg (0, sfile.end);
    int length = sfile.tellg();
    sfile.seekg (0, sfile.beg);

    char* buffer = new char [length+1];

    // read data as a block:
    sfile.read (buffer,length);
    buffer[length] = '\0';

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

    sfile.close();

    std::vector<File> lfret;	
	json::value jlist = jret["list"];
	for(int i = 0; jlist[i] != json::value::null() ; ++i)
		lfret.push_back(File::FromJson(jlist[i]));

	return lfret;
}