#ifndef SERCLIENTP2P_H
#define SERCLIENTP2P_H

	#include <iostream>
	#include <string>
	#include <vector>
	#include <cstdlib>

	// Include REST API

	#include <cpprest/http_client.h>
	#include <cpprest/json.h>                       // JSON library

	using namespace utility;                    	// Common utilities like string conversions
	using namespace web;                        	// Common features like URIs.
	using namespace web::http;                  	// Common HTTP functionality
	using namespace web::http::client;          	// HTTP client features
	using namespace web::json;                                  // JSON library

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

	class SerClientP2P 
	{
	public:

		SerClientP2P(ConfigPeer &pcf);
		SerClientP2P();
		~SerClientP2P();

		StError lastResponse;
		ConfigPeer cf;

		std::vector<Peer> GetPeerList(std::string dest);
		std::vector<File> GetFileList(std::string dest);
		File GetFile(std::string dest, std::string id);
		void DeleteFile(std::string dest, std::string id);
		void SaveFile(std::string dest, File file);
		void UpdateFile(std::string dest, File file);
		void RegisterPeer(std::string dest, std::string url);
		void UnregisterPeer(std::string dest, std::string url);

		json::value RequestHttp(std::string pdest,std::string pmethod, std::string ppath, json::value &pbody);

	protected:

		string_t myIpAddr_t;
		string_t myPort_t;
	};





#endif