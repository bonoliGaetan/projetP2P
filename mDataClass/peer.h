#ifndef PEER_H
#define PEER_H

#include<iostream>
#include<string>
#include<list>
#include"file.h"

class Peer
{
	public:
	std::string url;
	std::string nom;
	std::list<File> fichiers;
};

#endif