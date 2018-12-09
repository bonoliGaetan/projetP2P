#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include "mGraphique/fenetre.h"

#include "mClient/client.h"
#include "mServeur/serveur.h"

#include "mDataClass/configPeer.h"



 

#define FILECONFIG "config.json"

#if __OPSYS == linux
	#define SL "/"
#elif __OPSYS == windows
	#define SL "\\"
#endif


#endif