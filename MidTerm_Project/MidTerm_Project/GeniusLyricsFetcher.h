#pragma once

#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <fstream>
#include <filesystem>

#define GENIUS_TOKEN_FILENAME	"genius_access_token.txt"
#define GENIUS_HTML_TEMPFILENAME "genius_html_temp.txt"

using namespace std;

class GeniusLyricsFetcher {
public:
	static int GetLyricsFromGenius(const string &name,
		const string &artist, string &lyrics);

private:
	static bool SendGetRequest(const string &url,
		const FILE *fp, int &resultCode);

	static bool SendGetRequest(const string &url,
		string &result, int &resultCode);

	static size_t WiteStringCallback(const char *in, size_t size,
		size_t num, string *out);

	static size_t WriteFileCallback(void *ptr, size_t size,
		size_t nmemb, void *stream);

	static bool GetLyricsUrl(const string &jsonString, string &result);

	static bool GetHTMLFromGenius(const string &geniusUrl,
		const string &fileName);

	static bool ParseLyricsFromHTML(const string &fileName, string &lyrics);
};
