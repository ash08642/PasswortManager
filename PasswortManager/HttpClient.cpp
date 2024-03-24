#include "HttpClient.h"

HttpClient::HttpClient(std::string url, int port)
{
	cli = new httplib::Client(url, port);
}

HttpClient::~HttpClient()
{
	delete cli;
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

	/*httplib::MultipartFormDataItems items = {
	  { "name", "abeer", "moeez", "rameez" },
	  { "age", "22", "23", "24" },
	  { "file1", "h\ne\n\nl\nl\no\n", "hello.txt", "text/plain" },
	  { "file2", "{\n  \"world\", true\n}\n", "world.json", "application/json" },
	  { "file3", "", "", "application/octet-stream" },
	};

	auto res = cli->Post("/multipart", items);*/

	if (res && res->status == 200) {
		return res->body;
	}

	return "error";
}
