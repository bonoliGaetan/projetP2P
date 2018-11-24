#ifndef MAIN_H
#define MAIN_H

#include <iostream>


#include "mInterfaceP2P/serviceP2P.h"
//#include "mClient/client.h"
#include "mDataClass/configPeer.h"
#include "mServeur/serveur.h"
//#include "mGraphique/fenetre.h"


#define FILECONFIG "config.json"

#if __OPSYS == linux
	#define SL "/"
#elif __OPSYS == windows
	#define SL "\\"
#endif

using namespace web::json;  

std::vector<Peer> listePair;
std::vector<File> listeFichier;

#endif