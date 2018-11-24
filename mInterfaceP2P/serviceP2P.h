#ifndef SERVICEP2P_H
#define SERVICEP2P_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

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

// ****************

#include "../mDataClass/file.h"
#include "../mDataClass/peer.h"
#include "../mDataClass/configPeer.h"

#define LOCALHOST 	"localhost"

#if __OPSYS == linux
	#define HTTPLOGS	"logs/httplogs.txt"
	#define REPTMP		"tmpP2P/"
#elif __OPSYS == windows
	#define HTTPLOGS	"logs\\httplogs.txt"
	#define REPTMP		"tmpP2P\\"
#endif
typedef struct
{
	int code;
	std::string codeString;
	std::string message;
}StError;

StError new_StError(int,std::string);

class ServiceP2P 
{
public:

	ServiceP2P(ConfigPeer &pcf);
	ServiceP2P();
	~ServiceP2P();

	StError lastResponse;
	ConfigPeer cf;

	// JSON

	json::value FileToJson(File file);
	json::value ListFileToJson(std::vector<File> &filelist);
	json::value PeerToJson(Peer peer);
	json::value ListPeerToJson(std::vector<Peer> &peerList);

	File JsonToFile(json::value file);
	std::vector<File> JsonToListFile(json::value fileList);
	Peer JsonToPeer(json::value peer);
	std::vector<Peer> JsonToListPeer(json::value peerList);

	// CLIENT
	std::vector<Peer> GetPeerList(std::string dest);
	std::vector<File> GetFileList(std::string dest);
	File GetFile(std::string dest, std::string id);
	
	void DeleteFile(std::string dest, std::string id);

	void SaveFile(std::string dest, File file);

	void UpdateFile(std::string dest, File file);

	void RegisterPeer(std::string dest, std::string url);
	void UnregisterPeer(std::string dest, std::string url);
	
	// SERVEUR
	
	// foncTraitement : int <nomfct>(std::string paramUrl, json::value dataIn, json::value &dataOut);
	void WaitRegister(int fctTraitement(std::string, json::value, json::value&));
	void WaitUnregister(int fctTraitement(std::string, json::value, json::value&));

	void WaitGetPeerList(int fctTraitement(std::string, json::value, json::value&));
	void WaitGetFileList(int fctTraitement(std::string, json::value, json::value&));
	void WaitGetFile(int fctTraitement(std::string, json::value, json::value&));

	void WaitDeleteFile(int fctTraitement(std::string, json::value, json::value&));

	void WaitSaveFile(int fctTraitement(std::string, json::value, json::value&));
	void WaitUpdateFile(int fctTraitement(std::string, json::value, json::value&));

	void CloseAllWaitServer();

protected:

	string_t myIpAddr_t;
	string_t myPort_t;

	std::string getIPAddress();

	std::vector<http_listener*> serverListeners;

	json::value RequestHttp(std::string pdest,std::string pmethod, std::string ppath, json::value &pbody);
	
	void SetListenerMethod(http_listener &plistener, string_t pmethod, int fctTraitement(std::string, json::value,json::value&));

	// TODO traitement erreurs
};


#endif