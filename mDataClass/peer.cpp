#include "peer.h"

json::value Peer::ToJson()
{
	json::value jret = json::value::object();

	jret["url"] = json::value::string(this->url);

	return jret;
}


Peer Peer::FromJson(json::value jpar)
{
	Peer fret;

	fret.url = GetJsonString(jpar,"url");

	return fret;
}