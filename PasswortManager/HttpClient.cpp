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
	//
	//
	//httplib::Headers headers;// { { keys[0], values[0] }, { keys[1], values[2] } };
	//for (size_t i = 0; i < keys.size(); i++)
	//{
	//	headers.insert({ keys[i], values[i] });
	//}
	/*httplib::Params params;
	for (size_t i = 0; i < keys.size(); i++)
	{
		params.emplace(keys[i], values[i]);
	}*/
	/*httplib::Headers headers = {
  { "Accept-Encoding", "gzip, deflate" }
	};
	auto res = cli.Get("/hi", headers);*/
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
