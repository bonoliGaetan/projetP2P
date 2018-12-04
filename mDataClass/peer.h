#ifndef PEER_H
#define PEER_H

#include<iostream>
#include<string>
#include<vector>
#include"file.h"
#include "jsonUtility.h"

using namespace web;
using namespace web::json;

class Peer
{
	public:
	std::string url;
	std::string name;
	std::vector<File> fileList;

	json::value ToJson();
	static Peer FromJson(json::value jpar);
};

#endif