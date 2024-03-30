#include "HttpClient.h"

HttpClient::HttpClient(std::string url, int port)
{
	cli = new httplib::Client(url, port);
}

HttpClient::~HttpClient()
{
	delete cli;
}

std::string HttpClient::get_req(std::string url, std::vector<std::string> keys, std::vector<std::string> values)
{
	url += "?" + keys[0] + "=" + values[0];
	for (size_t i = 1; i < keys.size(); i++)
	{
		url += "&" + keys[i] + "=" + values[i];
	}
	auto res = cli->Get(url);
	if (res && res->status == 200) {
		std::string ress = res->body;
		return res->body;
	}

	return "error";
}

std::string HttpClient::post_req(std::string url, std::vector<std::string> keys, std::vector<std::string> values)
{
	httplib::MultipartFormDataItems items;
	for (size_t i = 0; i < keys.size(); i++)
	{
		httplib::MultipartFormData newItem{ keys[i], values[i] };
		items.push_back(newItem);
	}

	auto res = cli->Post(url, items);

	if (res && res->status == 200) {
		return res->body;
	}

	return "error";
}
