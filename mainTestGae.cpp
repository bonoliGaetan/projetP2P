#include"./mClient/client.h"

int main()
{
	Client* a = new Client();
	
	printf("1\n");
	
	std::ifstream fic("test.json");
		printf("1\n");
	json::value file;
		printf("1\n");
	fic >> file;
		printf("1\n");
	a->json_vers_fichier(file);
	
	return 0;
}
