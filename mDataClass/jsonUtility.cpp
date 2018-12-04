#include "jsonUtility.h"

int GetJsonInt(json::value &jval, string_t key)
{
	int ret;
	try {
		ret = jval.at(key).as_integer();
	}catch(json::json_exception je) {
		ret = 0;
	} 
	return ret;
}

std::string GetJsonString(json::value &jval, string_t key)
{
	string_t ret_t;
	std::string ret;
	try {
		ret_t = jval.at(key).as_string();
		ret = utility::conversions::to_utf8string(ret_t);
	}catch(json::json_exception je) {
		ret = "";
	} 
	return ret;
}