#ifndef PEER_H
#define PEER_H

#include<iostream>
#include<string>
#include<vector>
#include"file.h"

class Peer
{
	public:
	std::string url;
	std::string name;
	std::vector<File> fileList;
};

#endif