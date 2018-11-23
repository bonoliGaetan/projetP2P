#include <iostream>
#include "mInterfaceP2P/serviceP2P.h"
#include "mClient/client.h"
//#include "mServer/server.h"

#if __OPSYS == linux
	#define SL "/"
#elif __OPSYS == windows
	#define SL "\\"
#endif

using namespace web::json;  

int main(void)
{	
	std::cout << SL << std::endl;

	//ServiceP2P s("8080");
	
	return 0;
}