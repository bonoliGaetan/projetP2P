#include "peer.h"


Peer::Peer(std::string url)
{
	this->url = url;
	this->fileList = std::vector<File>();
}


json::value Peer::ToJson()
{
	return json::value::string(this->url);
}


Peer Peer::FromJson(json::value jpar)
{
	return Peer(GetJsonString(jpar,"url"));
}