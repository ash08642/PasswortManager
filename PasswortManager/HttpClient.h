#pragma once
#include <httplib.h>
#include <string>
#include <vector>

class HttpClient
{
public:
	enum StatusStrigs
	{
		USERNAME_IS_TAKEN,
		SERVER_ERROR
	};

	HttpClient(std::string url, int port);
	~HttpClient();

	std::string get_req(std::string url, std::vector<std::string> keys, std::vector<std::string> values);
	std::string post_req(std::string url, std::vector<std::string> keys, std::vector<std::string> values);

private:
	httplib::Client* cli;
};

