#include "GeniusLyricsFetcher.h"

#include <string>
#include <fstream>
#include <filesystem>
#include <json/json.h>
#include <curl/curl.h>

#include "GeniusAccessToken.h"

#define GENIUS_TOKEN_FILENAME	"genius_access_token.txt"
#define GENIUS_HTML_TEMPFILENAME "genius_html_temp.txt"

using namespace std;

// �� �̸��� ���������� ���縦 �޾ƿ�
int GeniusLyricsFetcher::GetLyricsFromGenius(const string &name,
	const string &artist, string &lyrics) {
	// Setup url for sending get request
	// Our search query is "`Artist` `Title`". ex) "Anne Marie 2002"
	const string searchApi = "https://api.genius.com/search?q=";
	// ������Ʈ�� ���� URL
	string url = searchApi + artist + " " + name + "&access_token=" + GENIUS_ACCESS_TOKEN;

	// URL�� ������ %20���� �ٲ�
	for (auto pos = url.find(' '); pos != string::npos;
		pos = url.find(' ', pos + 1)) {
		url.replace(pos, 1, "%20");
	}

	// ������Ʈ ����
	string result;
	int resultCode;
	SendGetRequest(url, result, resultCode);
	if (resultCode != 200) {
		// 200 �� �ƴϸ� ���з� �����ϰ� �ٷ� �Լ� ����
		return 0;
	}

	// JSON ������ ���信�� ���� URL ��������
	string lyricsUrl;
	if (!GetLyricsUrl(result, lyricsUrl)) {
		return 0;
	}
	// ���� URL�� ���� HTML �ҽ� �޾ƿ���
	if (!GetHTMLFromGenius(lyricsUrl, GENIUS_HTML_TEMPFILENAME)) {
		return 0;
	}
	// HTML �ҽ����� ���縸 ����, lyrics�� ����
	if (!ParseLyricsFromHTML(GENIUS_HTML_TEMPFILENAME, lyrics)) {
		return 0;
	}

	return 1;
}

// Get ������Ʈ ����, cURL �̿�
bool GeniusLyricsFetcher::SendGetRequest(const string &url,
	const FILE *fp, int &resultCode) {
	// REST ��û�� ���� cURL �ʱ�ȭ
	CURL *curl;
	curl = curl_easy_init();
	if (!curl) {
		cout << "curl init failed\n";
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL ����
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // Ÿ�Ӿƿ� ����
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirection �� ���󰡱� ����
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback); // ������ ���信 ���� �ݹ� ����
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // ����� ����� ���� ������ ����

	curl_easy_perform(curl); // ��û ����
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // ���� �ޱ�
	curl_easy_cleanup(curl); // Cleanup

	return true;
}

// Get ������Ʈ ����, cURL �̿�
bool GeniusLyricsFetcher::SendGetRequest(const string &url,
	string &result, int &resultCode) {
	// REST ��û�� ���� cURL �ʱ�ȭ
	CURL *curl;
	curl = curl_easy_init();
	if (!curl) {
		cout << "curl init failed\n";
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL ����
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // Ÿ�Ӿƿ� ����
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirection �� ���󰡱� ����
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WiteStringCallback); // ������ ���信 ���� �ݹ� ����
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result); // ����� ����� string ����

	curl_easy_perform(curl); // ��û ����
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // ���� �ޱ�
	curl_easy_cleanup(curl); // Cleanup

	return true;
}

// ������Ʈ �ݹ�, ����� string�� ����
size_t GeniusLyricsFetcher::WiteStringCallback(const char *in,
	size_t size, size_t num, string *out) {
	const size_t total = size * num; // ��Ż ������ ���
	out->append(in, total); // out�� ���� ���ڿ���ŭ �߰�
	return total;
}
// ������Ʈ �ݹ�, ����� ��Ʈ���� ����
size_t GeniusLyricsFetcher::WriteFileCallback(void *ptr, size_t size,
	size_t nmemb, void *stream) {
	// ���� ���ڿ� ��Ʈ���� ���� �� ��Ż ������ ���
	const size_t total = fwrite(ptr, size, nmemb, (FILE *)stream);
	return total;
}

// ������Ʈ ������ JSON �Ľ��Ͽ� URL�� ����
bool GeniusLyricsFetcher::GetLyricsUrl(const string &jsonString,
	string &result) {
	// �ļ� �̿뿡 �ʿ��� ���� �ʱ�ȭ
	Json::Value value; // �Ľ̵� ������ ��� ����
	JSONCPP_STRING err;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();

	// string�� ��� JSON ������ �Ľ��Ͽ� value�� �迭�� ���·� ����
	if (!reader->parse(jsonString.c_str(),
		jsonString.c_str() + jsonString.length(), &value, &err)) {
		// TODO: Error!
		cout << "error\n";
		return false;
	}

	// URL�� ��� �κ��� ã�� result �� ����
	result = value["response"]["hits"][0]["result"]["url"].asString(); // "" if null
	return result != ""; // ����� ""�̸� ���з� ����
}

// URL�� HTML �ҽ� �޾Ƽ� ���Ͽ� ����
bool GeniusLyricsFetcher::GetHTMLFromGenius(const string &geniusUrl,
	const string &fileName) {
	int resultCode;

	FILE *fp;
	fopen_s(&fp, fileName.c_str(), "wb"); // ���� ����
	if (!fp) {
		return false;
	}

	// ��û �����ϰ� �� ����� ���Ͽ� ����
	SendGetRequest(geniusUrl, fp, resultCode);

	if (fp) {
		fclose(fp); // ���� �ݱ�
	}

	return resultCode == 200; // resultCode�� 200�̸� �������� ����
}

// HTML �ҽ����� ���縸 �̾Ƴ���, ������ ������ �ļ� ����
bool GeniusLyricsFetcher::ParseLyricsFromHTML(const string &fileName,
	string &lyrics) {
	// HTML �ҽ��� ��� ���� ����
	ifstream ifs(fileName);
	if (!ifs || ifs.peek() == EOF) {
		return false;
	}

	bool insideTag = false; // ���� �±� ���� ������ �а� �ִ��� ����
	bool lyricsDiv = false; // ������ ������ �˸��� div �±׸� ã�Ҵ��� ����
	string strInTag; // �±� ������ ������ ��Ʈ��, �츮�� ã�� ��Ʈ���� �´��� �����ϴ� �� ���
	const string startOfLyrics = "<div class=\"lyrics\">"; // ������ ������ �˸��� �±�
	const string lineBreak = "<br>"; // �ٹٲ� ����
	istreambuf_iterator<char> iter(ifs), end; // iterator

	// First we look for '<div class="lyrics">'
	for (; iter != end; ++iter) {
		if (*iter == '\n') {
			continue; // Skip line breaks
		}

		if (!insideTag) { // ���� �±׸� �а� �ִ°� �ƴϸ�
			if (*iter == '<') { // �±��� ������ ������ ��
				insideTag = true; // �±����� ǥ��
				strInTag += *iter; // �±��� ���� ���� ����
			}
		} else {
			strInTag += *iter; // �±� ���� ����
			if (strInTag.length() > startOfLyrics.length()) {
				// ���� ������ �±��� ���̰� �츮�� ã�� �ִ� �±׺��� �� �� ����
				// �츮�� ã�� �±װ� �ƴ� �� Ȯ����. �±� ������ ������ ���ǹ��ϴ� ���⼭ ����
				insideTag = false;
				strInTag = "";
				continue;
			}
			if (strInTag.compare(startOfLyrics) == 0) {
				// �츮�� ã�� �ִ�, ������ ������ �˸��� div �±� �߰�. �ߴ�.
				++iter; break;
			}
			if (*iter == '>') { // �±��� ��
				insideTag = false;
				strInTag = "";
			}
		}
	}

	// Next we look for '<p>', after which the lyrics actually starts
	// ��ü���� �帧�� ���� ����
	const string startOfP = "<p>";
	// Reset variables for the next FOR loop
	insideTag = false;
	strInTag = "";
	for (; iter != end; ++iter) {
		if (*iter == '\n') {
			continue; // Skip line breaks
		}

		if (!insideTag) {
			if (*iter == '<') { // Beginning of a tag
				insideTag = true;
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
	const string endOfP = "</p>";
	// Reset variables for the next FOR loop
	insideTag = false;
	strInTag = "";
	for (; iter != end; ++iter) {
		if (*iter == '\n') {
			continue; // Skip line breaks
		}

		if (!insideTag) {
			if (*iter == '<') { // Start of tag
				insideTag = true;
			} else {
				lyrics += *iter; // �±� �ȿ� ���� ���� �Ϲ� �ؽ�Ʈ. �� ������ �Ϻκ��̹Ƿ� ����.
			}
		}

		if (insideTag) {
			strInTag += *iter;
			if (strInTag.compare(lineBreak) == 0) {
				// �±��� ������ line break �̾����Ƿ� ���翡�� �ٹٲ� �߰�
				lyrics += '\n';
			} else if (strInTag.compare(endOfP) == 0) { // ���� ��				
				break;
			}
			if (*iter == '>') { // �±� ����
				// Reset tag status
				insideTag = false;
				strInTag = "";
			}
		}
	}

	if (ifs.is_open()) {
		ifs.close(); // HTML �ҽ� ���� �ݱ�
	}
	filesystem::remove(fileName); // HTML �ҽ� ������ �ӽ������̾����Ƿ� ����

	return true;
}
