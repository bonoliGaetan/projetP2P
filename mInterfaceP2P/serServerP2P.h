#ifndef SERSERVERP2P_H
#define SERSERVERP2P_H

	#if __OPSYS == linux
		#define HTTPLOGS	"logs/httplogs.txt"
		#define INTERLOGS	"logs/serviceserver.txt"
		#define REPTMP		"tmpP2P/"
	#elif __OPSYS == windows
		#define HTTPLOGS	"logs\\httplogs.txt"
		#define INTERLOGS	"logs/serviceserver.txt"
		#define REPTMP		"tmpP2P\\"
	#endif
	
	#include <iostream>
	#include <string>
	#include <vector>
	#include <cstdlib>

	#include <cpprest/http_listener.h>              // HTTP server
	#include <cpprest/json.h>                       // JSON library
	
	using namespace utility;                    	// Common utilities like string conversions
	using namespace web;                        	// Common features like URIs.
	using namespace web::http;                  	// Common HTTP functionality
	using namespace web::http::experimental::listener;          // HTTP server
	using namespace web::json;                                  // JSON library

	#include "../mDataClass/file.h"
	#include "../mDataClass/peer.h"
	#include "../mDataClass/configPeer.h"

	typedef int (*TFctWait)(std::string,json::value,json::value&);

	class SerServerP2P 
	{
	public:

		SerServerP2P(ConfigPeer &pcf);
		SerServerP2P();
		~SerServerP2P();

		ConfigPeer cf;

		void WaitRegister(int fctTraitement(std::string, json::value, json::value&));
		void WaitUnregister(int fctTraitement(std::string, json::value, json::value&));
		void WaitGetPeerList(int fctTraitement(std::string, json::value, json::value&));
		void WaitGetFileList(int fctTraitement(std::string, json::value, json::value&));
		void WaitGetFile(int fctTraitement(std::string, json::value, json::value&));
		void WaitDeleteFile(int fctTraitement(std::string, json::value, json::value&));
		void WaitSaveFile(int fctTraitement(std::string, json::value, json::value&));
		void WaitUpdateFile(int fctTraitement(std::string, json::value, json::value&));

		void addRequestTree(std::string url,std::string method, int fctTrait(std::string, json::value, json::value&));

		void OpenListener();
		void CloseListener();

	protected:

		string_t myIpAddr_t;
		string_t myPort_t;

		http_listener* serverListener;

		json::value requestTree;
		std::vector<TFctWait> vFctTrait;
		
		void traiterRequete(http_request req);
		int getRequestTree(std::string url, std::string method, std::string &paramUrl);

	};

#endif