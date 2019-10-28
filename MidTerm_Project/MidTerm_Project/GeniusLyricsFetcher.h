#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#define GENIUS_TOKEN_FILENAME	"genius_access_token.txt"
#define GENIUS_HTML_TEMPFILENAME "genius_html_temp.txt"

// using namespace std;
// is not allowed here since std::byte and
// 'typedef unsigned char byte' in curl.h cause a conflict.

class GeniusLyricsFetcher {
public:
	static int GetLyricsFromGenius(const std::string &name,
		const std::string &artist, std::string &lyrics);

private:
	static bool SendGetRequest(const std::string &url,
		const FILE *fp, int &resultCode);

	static bool SendGetRequest(const std::string &url,
		std::string &result, int &resultCode);

	static size_t WiteStringCallback(const char *in, size_t size,
		size_t num, std::string *out);

	static size_t WriteFileCallback(void *ptr, size_t size,
		size_t nmemb, void *stream);

	static bool GetLyricsUrl(const std::string &jsonString, std::string &result);

	static bool GetHTMLFromGenius(const std::string &geniusUrl,
		const std::string &fileName);

	static bool ParseLyricsFromHTML(const std::string &fileName, std::string &lyrics);
};
