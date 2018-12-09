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

int main(int argc, char* argv[])
{	

	ConfigPeer cf(FILECONFIG);

	if(argc <= 1)
		return 0;

	if(argv[1][0] == 's')
	{
		Serveur serv(&cf);
		sleep(20);

	}
	else
	{

		Client client(&cf);
		
		Gtk::Main app(argc, argv);
	    Fenetre fen(&client);
	    //fen.Init(client);
	    Gtk::Main::run(fen);
	
		/*try {
			switch(argv[2][0])
			{
				case 'd':
					client.obtenir_fichier_client(argv[3],argv[4]);
					break;
				case 'u':
					File f;
					f.body = argv[4];
					f.name = argv[4];
					client.sauvegarder_fichier_client(argv[3],f);
			}
		}catch(std::exception e)
		{
			std::cout << e.what() << std::endl;
		}*/
	}
	
	
	return 0;
}
