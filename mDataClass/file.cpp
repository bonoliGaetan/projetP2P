#include "file.h"

json::value File::ToJson(int body)
{
	json::value jret = json::value::object();

	jret["name"] = json::value::string(this->name);
	jret["fileId"] = json::value::string(this->id);
	jret["size"] = json::value::number(this->size);

	if(body == 1)
		jret["body"] = json::value::string(this->body);

	return jret;
}


File File::FromJson(json::value jpar)
{
	File fret;

	fret.id = GetJsonString(jpar,"fileId");
	fret.name = GetJsonString(jpar,"name");
	fret.size = GetJsonInt(jpar,"size");
	fret.body = GetJsonString(jpar,"body");

	return fret;
}