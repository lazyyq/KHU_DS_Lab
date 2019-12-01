#pragma once

#include <iostream>

struct HttpResult {
	int resultCode;
	std::string result;
};

class HttpRequest {
public:
	HttpRequest();

	void SetUrl(const std::string &_url);

	void AddParam(const std::string &key, const std::string &value);

	void SetTimeout(const int _timeout);

	bool SendGetRequest(const FILE *fp, int &resultCode);

	bool SendGetRequest(std::string &result, int &resultCode);

private:
	std::string url;
	int timeout = 10;
	bool hasParams = false;

	static size_t WriteStringCallback(const char *in, size_t size,
		size_t num, std::string *out);

	static size_t WriteFileCallback(void *ptr, size_t size,
		size_t nmemb, void *stream);
};
