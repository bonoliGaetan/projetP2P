#ifndef SERVICEP2P_H
#define SERVICEP2P_H

#include <iostream>
#include <string>
#include <vector>

// Include REST API

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                       // JSON library

using namespace utility;                    	// Common utilities like string conversions
using namespace web;                        	// Common features like URIs.
using namespace web::http;                  	// Common HTTP functionality
using namespace web::http::client;          	// HTTP client features
using namespace web::http::experimental::listener;          // HTTP server
using namespace web::json;                                  // JSON library
using namespace concurrency::streams;       	// Asynchronous streams

// ***************

#include "../mDataClass/file.h"
#include "../mDataClass/peer.h"

#define LOCALHOST 	"127.0.0.1"
#define HTTPLOGS	"httplog.txt"



typedef struct
{
	int code;
	std::string codeString;
	std::string message;
}StError;

StError new_StError();

class ServiceP2P 
{
public:

	ServiceP2P();
	~ServiceP2P();

	StError lastError;

	void Test();

	// CLIENT
	std::vector<Peer> GetPeerList(std::string dest);
	std::vector<File> GetFileList(std::string dest);
	void GetFile(std::string dest, File &file);
	
	void DeleteFile(std::string dest, std::string id);

	void UpdateDataFile(std::string dest, File file);
	void UpdateMetaFile(std::string dest, File file);

	void WaitRequestClient(int* typeReq, void* data);
	
	// SERVEUR
	void registerPeer(std::string dest, std::string url);
	void unregisterPeer(std::string dest, std::string url);

	void SendPeerList(std::string dest, std::vector<Peer>);
	void SendFileList(std::string dest, std::vector<File>);

	void SendMetaFile(std::string dest, File file);
	void SendDataFile(std::string dest, File file);

	void WaitRequestServer(int* typeReq, void* data);

protected:

	// Variables
	std::string addrIP;
	int outPort;
	int inPort;


	// Fonction d'écriture de requêtes
	std::string WRGetPeerList(std::string url);
	std::string WRGetFileList(std::string url);
	std::string WRGetFile(std::string url, std::string id);
	std::string WRDeleteFile(std::string url, std::string id);
	std::string WRUpdateDataFile(std::string url, File file);
	std::string WRUpdateMetaFile(std::string url, File file);

	std::string WRRegisterPeer(std::string url);
	std::string WRUnregisterPeer(std::string url);
	std::string WRSendPeerList(std::string url, std::vector<Peer>);
	std::string WRSendFileList(std::string url, std::vector<File>);
	std::string WRSendDataFile(std::string url, File file);
	std::string WRSendMetaFile(std::string url, File file);

	void SendRequestHTTP(std::string request);

	// et les retours de requêtes

};


#endif