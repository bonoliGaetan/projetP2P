#ifndef FILE_H
#define FILE_H

#include<iostream>
#include<string>
#include<cpprest/json.h>
#include "jsonUtility.h"

using namespace web;
using namespace web::json;

class File
{
	public:
		std::string id;
		int size;
		std::string name;
		std::string body;

		json::value ToJson(int);
		static File FromJson(json::value);
};

#endif