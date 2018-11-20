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

// ****************

#include "../mDataClass/file.h"
#include "../mDataClass/peer.h"

#define LOCALHOST 	"localhost"
#define HTTPLOGS	"httplogs.txt"

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

	ServiceP2P(std::string port);
	~ServiceP2P();

	StError lastError;
	std::string myIpAddr;
	std::string localhost;
	std::string myPort;

	// CLIENT
	std::vector<Peer> GetPeerList(std::string dest);
	std::vector<File> GetFileList(std::string dest);
	File GetFile(std::string dest, std::string id);
	
	void DeleteFile(std::string dest, std::string id);

	std::string SaveFile(std::string dest, File file);

	void UpdateFile(std::string dest, File file);

	// foncTraitement : int <nomfct>(std::string paramUrl, json::value dataIn, json::value &dataOut);
	void WaitRegister(int fctTraitement(std::string, json::value, json::value&));
	void WaitUnregister(int fctTraitement(std::string, json::value, json::value&));

	void CloseAllWaitClient();
	
	// SERVEUR
	void RegisterPeer(std::string dest, std::string url);
	void UnregisterPeer(std::string dest, std::string url);

	void WaitPeerList(int fctTraitement(std::string, json::value, json::value&));
	void WaitFileList(int fctTraitement(std::string, json::value, json::value&));
	void WaitGetFile(int fctTraitement(std::string, json::value, json::value&));

	void WaitDeleteFile(int fctTraitement(std::string, json::value, json::value&));

	void WaitSaveFile(int fctTraitement(std::string, json::value, json::value&));
	void WaitUpdateFile(int fctTraitement(std::string, json::value, json::value&));

	void CloseAllWaitServer();

protected:

	string_t myIpAddr_t;
	string_t localhost_t;
	string_t myPort_t;
	std::string getIPAddress();

	std::vector<http_listener*> clientListeners;
	std::vector<http_listener*> serverListeners;

	json::value RequestHttp(std::string pdest,std::string pmethod, std::string ppath, json::value pbody);
	
	void SetListenerMethod(http_listener &plistener, string_t pmethod, int fctTraitement(std::string, json::value,json::value&));

	// TODO traitement erreurs
};


#endif