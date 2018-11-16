#include <iostream>
#include <string>
#include <list>

#include "../dataClass/file.h"
#include "../dataClass/peer.h"


class ServiceP2P 
{
public:

	std::list<Peer> GetPeerList(std::string url);
	std::list<File> GetFileList(std::string url);
	char* GetFile(std::string url, std::string id);
	
	void UpdateFile(std::string url, File file);

	void DeleteFile(std::string id);
	
	void registerPeer(std::string url);
	void unregisterPeer(std::string url);


private:




};
