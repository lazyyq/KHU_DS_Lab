#include "GeniusLyricsFetcher.h"
#include <json/json.h>
#include <curl/curl.h>

int GeniusLyricsFetcher::GetLyricsFromGenius(const std::string &name,
	const std::string &artist, std::string &lyrics) {
	// Setup url for sending get request
	// Our search query is "`Artist` `Title`". ex) "Anne Marie 2002"
	const std::string searchApi = "https://api.genius.com/search?q=";
	std::ifstream ifs(GENIUS_TOKEN_FILENAME);
	if (!ifs || ifs.peek() == EOF) {
		return 0;
	}
	std::string token;
	getline(ifs, token);
	ifs.close();
	std::string url = searchApi + artist + " " + name + "&access_token=" + token;

	// Convert spaces to %20
	for (auto pos = url.find(' '); pos != std::string::npos;
		pos = url.find(' ', pos + 1)) {
		url.replace(pos, 1, "%20");
	}

	std::string result;
	int resultCode;
	SendGetRequest(url, result, resultCode);
	if (resultCode != 200) {
		return 0;
	}

	std::string lyricsUrl;
	if (!GetLyricsUrl(result, lyricsUrl)) {
		return 0;
	}
	if (!GetHTMLFromGenius(lyricsUrl, GENIUS_HTML_TEMPFILENAME)) {
		return 0;
	}
	if (!ParseLyricsFromHTML(GENIUS_HTML_TEMPFILENAME, lyrics)) {
		return 0;
	}

	return 1;
}

bool GeniusLyricsFetcher::SendGetRequest(const std::string &url,
	const FILE *fp, int &resultCode) {
	CURL *curl;
	curl = curl_easy_init();
	if (!curl) {
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // Timeout
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirections
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback); // Writefunc
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // Writedata

	curl_easy_perform(curl); // Perform cURL
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // Get response info
	curl_easy_cleanup(curl); // Cleanup

	return true;
}

bool GeniusLyricsFetcher::SendGetRequest(const std::string &url,
	std::string &result, int &resultCode) {
	CURL *curl;
	curl = curl_easy_init();
	if (!curl) {
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // Timeout
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirections
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WiteStringCallback); // Callback
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result); // Writedata

	curl_easy_perform(curl); // Perform cURL
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // Get response info
	curl_easy_cleanup(curl); // Cleanup

	return true;
}

size_t GeniusLyricsFetcher::WiteStringCallback(const char *in,
	size_t size, size_t num, std::string *out) {
	const size_t total = size * num;
	out->append(in, total);
	return total;
}

size_t GeniusLyricsFetcher::WriteFileCallback(void *ptr, size_t size,
	size_t nmemb, void *stream) {
	const size_t total = fwrite(ptr, size, nmemb, (FILE *)stream);
	return total;
}

bool GeniusLyricsFetcher::GetLyricsUrl(const std::string &jsonString,
	std::string &result) {
	Json::Value value;
	JSONCPP_STRING err;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	if (!reader->parse(jsonString.c_str(),
		jsonString.c_str() + jsonString.length(), &value, &err)) {
		// TODO: Error!
		std::cout << "error\n";
		return false;
	}

	result = value["response"]["hits"][0]["result"]["url"].asString(); // "" if null
	return result != "";
}

bool GeniusLyricsFetcher::GetHTMLFromGenius(const std::string &geniusUrl,
	const std::string &fileName) {
	int resultCode;
	std::string htmlSrc;
	FILE *fp;
	fopen_s(&fp, fileName.c_str(), "wb");
	if (!fp) {
		return false;
	}

	SendGetRequest(geniusUrl, fp, resultCode);

	if (fp) {
		fclose(fp);
	}

	return resultCode == 200;
}

bool GeniusLyricsFetcher::ParseLyricsFromHTML(const std::string &fileName,
	std::string &lyrics) {
	std::ifstream ifs(fileName);
	if (!ifs || ifs.peek() == EOF) {
		return false;
	}

	bool insideTag = false;
	bool lyricsDiv = false;
	std::string strInTag;
	const std::string startOfLyrics = "<div class=\"lyrics\">";
	const std::string lineBreak = "<br>";
	std::istreambuf_iterator<char> iter(ifs), end;

	// First we look for '<div class="lyrics">'
	for (; iter != end; ++iter) {
		if (*iter == '\n') {
			continue; // Skip line breaks
		}

		if (!insideTag) {
			if (*iter == '<') {
				insideTag = true; // Beginning of a tag
				strInTag += *iter;
			}
		} else {
			strInTag += *iter;
			if (strInTag.length() > startOfLyrics.length()) {
				// Tag is longer than startOfLyrics, definitely not what we're looking for
				// Just drop the search here
				insideTag = false;
				strInTag = "";
				continue;
			}
			if (strInTag.compare(startOfLyrics) == 0) { // Found
				++iter; break;
			}
			if (*iter == '>') {
				insideTag = false;
				strInTag = "";
			}
		}
	}

	// Next we look for '<p>', after which the lyrics actually starts
	const std::string startOfP = "<p>";
	// Reset variables for the next FOR loop
	insideTag = false;
	strInTag = "";
	for (; iter != end; ++iter) {
		if (*iter == '\n') {
			continue; // Skip line breaks
		}

		if (!insideTag) {
			if (*iter == '<') {
				insideTag = true; // Beginning of a tag
				strInTag += *iter;
			}
		} else {
			strInTag += *iter;
			if (strInTag.length() > startOfP.length()) {
				// Tag is longer than startOfP, definitely not what we're looking for
				// Just drop the search here
				insideTag = false;
				strInTag = "";
				continue;
			}
			if (strInTag.compare(startOfP) == 0) { // Found
				++iter; break;
			}
			if (*iter == '>') {
				insideTag = false;
				strInTag = "";
			}
		}
	}

	// Let's finally get the real lyrics.
	// We treat every character outside tags a part of lyrics.
	// Loop until the end of lyrics, which is '</p>'.
	const std::string endOfP = "</p>";
	// Reset variables for the next FOR loop
	insideTag = false;
	strInTag = "";
	for (; iter != end; ++iter) {
		if (*iter == '\n') {
			// Skip line breaks
			continue;
		}

		if (!insideTag) {
			if (*iter == '<') {
				// Start of tag
				insideTag = true;
			} else {
				// Normal text
				lyrics += *iter;
			}
		}

		if (insideTag) {
			strInTag += *iter;
			// We've reached the end of tag
			if (strInTag.compare(lineBreak) == 0) {
				// Was a line break
				lyrics += '\n';
			} else if (strInTag.compare(endOfP) == 0) {
				// End of lyrics
				break;
			}
			if (*iter == '>') {
				// Reset tag status
				insideTag = false;
				strInTag = "";
			}
		}
	}

	if (ifs.is_open()) {
		ifs.close();
	}
	std::filesystem::remove(fileName);

	return true;
}
