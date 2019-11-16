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

// 곡 이름과 가수명으로 가사를 받아옴
int GeniusLyricsFetcher::GetLyricsFromGenius(const string &name,
	const string &artist, string &lyrics) {
	// Setup url for sending get request
	// Our search query is "`Artist` `Title`". ex) "Anne Marie 2002"
	const string searchApi = "https://api.genius.com/search?q=";
	// 리퀘스트를 보낼 URL
	string url = searchApi + artist + " " + name + "&access_token=" + GENIUS_ACCESS_TOKEN;

	// URL의 공백을 %20으로 바꿈
	for (auto pos = url.find(' '); pos != string::npos;
		pos = url.find(' ', pos + 1)) {
		url.replace(pos, 1, "%20");
	}

	// 리퀘스트 전송
	string result;
	int resultCode;
	SendGetRequest(url, result, resultCode);
	if (resultCode != 200) {
		// 200 이 아니면 실패로 간주하고 바로 함수 종료
		return 0;
	}

	// JSON 형태의 응답에서 가사 URL 가져오기
	string lyricsUrl;
	if (!GetLyricsUrl(result, lyricsUrl)) {
		return 0;
	}
	// 가사 URL을 따라가 HTML 소스 받아오기
	if (!GetHTMLFromGenius(lyricsUrl, GENIUS_HTML_TEMPFILENAME)) {
		return 0;
	}
	// HTML 소스에서 가사만 추출, lyrics에 저장
	if (!ParseLyricsFromHTML(GENIUS_HTML_TEMPFILENAME, lyrics)) {
		return 0;
	}

	return 1;
}

// Get 리퀘스트 전송, cURL 이용
bool GeniusLyricsFetcher::SendGetRequest(const string &url,
	const FILE *fp, int &resultCode) {
	// REST 요청을 보낼 cURL 초기화
	CURL *curl;
	curl = curl_easy_init();
	if (!curl) {
		cout << "curl init failed\n";
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL 설정
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // 타임아웃 설정
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirection 시 따라가기 설정
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback); // 도착한 응답에 대해 콜백 설정
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // 결과가 저장될 파일 포인터 설정

	curl_easy_perform(curl); // 요청 전송
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // 응답 받기
	curl_easy_cleanup(curl); // Cleanup

	return true;
}

// Get 리퀘스트 전송, cURL 이용
bool GeniusLyricsFetcher::SendGetRequest(const string &url,
	string &result, int &resultCode) {
	// REST 요청을 보낼 cURL 초기화
	CURL *curl;
	curl = curl_easy_init();
	if (!curl) {
		cout << "curl init failed\n";
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL 설정
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // 타임아웃 설정
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirection 시 따라가기 설정
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WiteStringCallback); // 도착한 응답에 대해 콜백 설정
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result); // 결과가 저장될 string 설정

	curl_easy_perform(curl); // 요청 전송
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // 응답 받기
	curl_easy_cleanup(curl); // Cleanup

	return true;
}

// 리퀘스트 콜백, 결과물 string에 저장
size_t GeniusLyricsFetcher::WiteStringCallback(const char *in,
	size_t size, size_t num, string *out) {
	const size_t total = size * num; // 토탈 사이즈 계산
	out->append(in, total); // out에 받은 문자열만큼 추가
	return total;
}
// 리퀘스트 콜백, 결과물 스트림에 저장
size_t GeniusLyricsFetcher::WriteFileCallback(void *ptr, size_t size,
	size_t nmemb, void *stream) {
	// 받은 문자열 스트림에 저장 및 토탈 사이즈 계산
	const size_t total = fwrite(ptr, size, nmemb, (FILE *)stream);
	return total;
}

// 리퀘스트 응답을 JSON 파싱하여 URL만 추출
bool GeniusLyricsFetcher::GetLyricsUrl(const string &jsonString,
	string &result) {
	// 파서 이용에 필요한 변수 초기화
	Json::Value value; // 파싱된 내용이 담길 변수
	JSONCPP_STRING err;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();

	// string에 담긴 JSON 문서를 파싱하여 value에 배열의 형태로 저장
	if (!reader->parse(jsonString.c_str(),
		jsonString.c_str() + jsonString.length(), &value, &err)) {
		// TODO: Error!
		cout << "error\n";
		return false;
	}

	// URL이 담긴 부분을 찾아 result 에 저장
	result = value["response"]["hits"][0]["result"]["url"].asString(); // "" if null
	return result != ""; // 결과가 ""이면 실패로 간주
}

// URL의 HTML 소스 받아서 파일에 저장
bool GeniusLyricsFetcher::GetHTMLFromGenius(const string &geniusUrl,
	const string &fileName) {
	int resultCode;

	FILE *fp;
	fopen_s(&fp, fileName.c_str(), "wb"); // 파일 열기
	if (!fp) {
		return false;
	}

	// 요청 전송하고 그 결과를 파일에 저장
	SendGetRequest(geniusUrl, fp, resultCode);

	if (fp) {
		fclose(fp); // 파일 닫기
	}

	return resultCode == 200; // resultCode가 200이면 성공으로 간주
}

// HTML 소스에서 가사만 뽑아내는, 굉장이 무식한 파서 역할
bool GeniusLyricsFetcher::ParseLyricsFromHTML(const string &fileName,
	string &lyrics) {
	// HTML 소스가 담긴 파일 열기
	ifstream ifs(fileName);
	if (!ifs || ifs.peek() == EOF) {
		return false;
	}

	bool insideTag = false; // 현재 태그 안의 내용을 읽고 있는지 여부
	bool lyricsDiv = false; // 가사의 시작을 알리는 div 태그를 찾았는지 여부
	string strInTag; // 태그 내용을 저장할 스트링, 우리가 찾는 스트링이 맞는지 대조하는 데 사용
	const string startOfLyrics = "<div class=\"lyrics\">"; // 가사의 시작을 알리는 태그
	const string lineBreak = "<br>"; // 줄바꿈 문자
	istreambuf_iterator<char> iter(ifs), end; // iterator

	// First we look for '<div class="lyrics">'
	for (; iter != end; ++iter) {
		if (*iter == '\n') {
			continue; // Skip line breaks
		}

		if (!insideTag) { // 현재 태그를 읽고 있는게 아니면
			if (*iter == '<') { // 태그의 시작을 만났을 때
				insideTag = true; // 태그임을 표시
				strInTag += *iter; // 태그의 내용 저장 시작
			}
		} else {
			strInTag += *iter; // 태그 내용 저장
			if (strInTag.length() > startOfLyrics.length()) {
				// 여태 저장한 태그의 길이가 우리가 찾고 있는 태그보다 긴 걸 보니
				// 우리가 찾는 태그가 아닌 게 확실함. 태그 내용의 저장이 무의미하니 여기서 중지
				insideTag = false;
				strInTag = "";
				continue;
			}
			if (strInTag.compare(startOfLyrics) == 0) {
				// 우리가 찾고 있던, 가사의 시작을 알리는 div 태그 발견. 중단.
				++iter; break;
			}
			if (*iter == '>') { // 태그의 끝
				insideTag = false;
				strInTag = "";
			}
		}
	}

	// Next we look for '<p>', after which the lyrics actually starts
	// 전체적인 흐름은 위와 동일
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
				lyrics += *iter; // 태그 안에 있지 않은 일반 텍스트. 즉 가사의 일부분이므로 저장.
			}
		}

		if (insideTag) {
			strInTag += *iter;
			if (strInTag.compare(lineBreak) == 0) {
				// 태그의 내용이 line break 이었으므로 가사에도 줄바꿈 추가
				lyrics += '\n';
			} else if (strInTag.compare(endOfP) == 0) { // 가사 끝				
				break;
			}
			if (*iter == '>') { // 태그 종료
				// Reset tag status
				insideTag = false;
				strInTag = "";
			}
		}
	}

	if (ifs.is_open()) {
		ifs.close(); // HTML 소스 파일 닫기
	}
	filesystem::remove(fileName); // HTML 소스 파일은 임시파일이었으므로 삭제

	return true;
}
