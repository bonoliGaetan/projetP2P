#include <iostream>
#include <string>
#include <list>

#include "../mDataClass/file.h"
#include "../mDataClass/peer.h"


class ServiceP2P 
{
public:
	// CLIENT
	std::list<Peer> GetPeerList(std::string url);
	std::list<File> GetFileList(std::string url);
	void GetFile(std::string url, File &file);
	
	void DeleteFile(std::string url, std::string id);

	void UpdateDataFile(std::string url, File file);
	void UpdateMetaFile(std::string url, File file);

	Peer WaitRegister(int* typeReg);
	
	// SERVEUR
	void registerPeer(std::string url);
	void unregisterPeer(std::string url);

	void SendPeerList(std::string url, std::list<Peer>);
	void SendFileList(std::string url, std::list<File>);

	void SendMetaFile(std::string url, File file);
	void SendDataFile(std::string url, File file);

protected:

	// Variables
	// attibuts peut être nécessaire pour les requêtes http
	// Si oui, fait un contructeur
	// Si non, mettre en static


	// Fonction d'écriture de requêtes
	std::string WRGetPeerList(std::string url);
	std::string WRGetFileList(std::string url);
	std::string WRGetFile(std::string url, std::string id);
	std::string WRDeleteFile(std::string url, std::string id);
	std::string WRUpdateDataFile(std::string url, File file);
	std::string WRUpdateMetaFile(std::string url, File file);

	std::string WRRegisterPeer(std::string url);
	std::string WRUnregisterPeer(std::string url);
	std::string WRSendPeerList(std::string url, std::list<Peer>);
	std::string WRSendFileList(std::string url, std::list<File>);
	std::string WRSendDataFile(std::string url, File file);
	std::string WRSendMetaFile(std::string url, File file);

	void SendRequestHTTP(std::string request);

	// et les retours de requêtes

};
