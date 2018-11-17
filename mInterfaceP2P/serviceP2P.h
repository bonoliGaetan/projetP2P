#include <iostream>
#include <string>
#include <list>

#include "../mDataClass/file.h"
#include "../mDataClass/peer.h"


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
