#include "main.h"

/*
int testhandler(std::string paramUrl, json::value dataIn, json::value &dataOut)
{
	std::cout << paramUrl << std::endl;
	dataOut = dataIn;
	dataOut["request"] = json::value(paramUrl);

	try {
		std::ifstream sfile(paramUrl,std::ios::in);
	    
	    sfile.seekg (0, sfile.end);
	    int length = sfile.tellg();
	    sfile.seekg (0, sfile.beg);

	    char * buffer = new char [length];

	    sfile.read (buffer,length);
	    sfile.close();
 
 		dataOut["size"] = length;
	    dataOut["body"] = json::value::string(buffer);

	    delete[] buffer;

	}catch(std::ifstream::failure ioe)
	{
		std::cerr << "Erreur de lecture du fichier : " << paramUrl << std::endl;
	}

	std::cout << dataOut.serialize() << std::endl;
}
*/

int main(int nbarg, char* argv[])
{	

	ConfigPeer cf(FILECONFIG);
	ServiceP2P spp(cf);
	Client client(cf,spp);
	

	File f;
	f.id = "3";
	f.name = "sss";
	cf.listeFichier.push_back(f);

	Peer p;
	p.url = "55";
	p.name = "aaa";
	cf.listePair.push_back(p);


	Gtk::Main app(nbarg,argv);
	
	Fenetre fen(client,"Salut");
	Gtk::Main::run(fen);

	/*
	

	cf.affData();
	// TODO : S'ajouter dans la liste des pairs

	//Client(cf,spp); TODO
	//Server(cf,spp); TODO

	// A SUPPR
	
	spp.WaitGetFile(&testhandler);

	File f;
	f.id = "-1";
	f.name = "truc";
	f.size = 0;
	f.body = "config.json";
	spp.GetFile(cf.firstRegister,"config.json");

	sleep(15);
	*/

	return 0;
}

/*
std::map<std::string,std::string> init_liste_option(std::string sfichier)
{
	// Ouverture du fichier contenant la liste des pairs.
	
	std::map<std::string,std::string> ret;
	std::ifstream fichier(sfichier,std::ifstream::in);
	
	if(fichier)
	{
		std::cout<<"Le fichier " << sfichier << " s'est ouvert"<<std::endl;
		
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
				ret[clef] = valeurFinal;
			}
			else
			{
				fichier >> valeur;
				ret[clef] = valeur;
			}
		}
		
		fichier.close();
	}
	else
	{
		std::cout<<"Erreur lors de l'ouverture du fichier"<<std::endl;
	}

	return ret;
}
*/