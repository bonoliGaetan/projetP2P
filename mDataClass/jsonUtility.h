#ifndef JSONUTILITY_H
#define JSONUTILITY_H

#include <cpprest/json.h>
#include<string>

using namespace web;
using namespace web::json;
using namespace utility;

std::string GetJsonString(json::value &jval, string_t key);
int GetJsonInt(json::value &jval, string_t key);

#endif