#ifndef MAIN_H
#define MAIN_H

#include <iostream>


#include "mDataClass/peer.h"
#include "mDataClass/file.h"
#include "mDataClass/configPeer.h"

//#include "mInterfaceP2P/serviceP2P.h"
#include "mGraphique/fenetre.h"

//#include "mClient/client.h"
//#include "mServeur/serveur.h"



 

#define FILECONFIG "config.json"

#if __OPSYS == linux
	#define SL "/"
#elif __OPSYS == windows
	#define SL "\\"
#endif


#endif