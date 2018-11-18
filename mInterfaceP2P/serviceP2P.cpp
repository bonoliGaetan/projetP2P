#include <iostream>

#include "serviceP2P.h"

StError new_StError()
{
	StError ret;
	ret.code = 0;
	ret.codeString = std::string();
	ret.message = std::string();

	return ret;
}

ServiceP2P::ServiceP2P()
{
	this->lastError = new_StError();

	this->addrIP = std::string();
	this->outPort = 0;
	this->inPort = 0;
}

ServiceP2P::~ServiceP2P() {}


void ServiceP2P::Test()
{
	auto fileStream = std::make_shared<ostream>();
	// Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U(HTTPLOGS))
    .then([=](ostream outFile)
    {
       	*fileStream = outFile;

        // Create http_client to send the request.
        http_client client(U("www.google.fr"));

        // Build request URI and start the request.
        uri_builder builder(U("/search"));
        builder.append_query(U("q"), U("google"));
        return client.request(methods::GET, builder.to_string());
    })
    .then([=](http_response response)
    {
        printf("Received response status code:%u\n", response.status_code());
    });
}