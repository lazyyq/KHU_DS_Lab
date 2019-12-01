#include "HttpRequest.h"

#include <curl/curl.h>

#include "../utils/StringUtils.h"

using namespace std;
using namespace stringutils;

HttpRequest::HttpRequest() {}

void HttpRequest::SetUrl(const string &_url) {
	url = _url;
}

void HttpRequest::AddParam(const string &key, const string &value) {
	if (!hasParams) {
		url += string("?");
		hasParams = true;
	}
	CURL *curl = curl_easy_init();

	char *encoded_key = curl_easy_escape(curl, AnsiToUtf8(key).c_str(), 0);
	char *encoded_value = curl_easy_escape(curl, AnsiToUtf8(value).c_str(), 0);
	url += string("&") + encoded_key + string("=") + encoded_value;

	curl_free(encoded_key);
	curl_free(encoded_value);
	curl_easy_cleanup(curl);
}

void HttpRequest::SetTimeout(const int _timeout) {
	timeout = _timeout;
}

bool HttpRequest::SendGetRequest(const FILE *fp, int &resultCode) {
	CURL *curl = curl_easy_init();
	if (!curl) {
		cout << "curl init failed.\n";
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL 설정
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); // 타임아웃 설정
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirection 시 따라가기 설정
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback); // 콜백 설정
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // 결과가 저장될 파일 포인터 설정

	curl_easy_perform(curl); // 요청 전송
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // 응답 받기
	curl_easy_cleanup(curl);

	return true;
}

bool HttpRequest::SendGetRequest(string &result, int &resultCode) {
	CURL *curl = curl_easy_init();
	if (!curl) {
		cout << "curl init failed.\n";
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL 설정
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); // 타임아웃 설정
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirection 시 따라가기 설정
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteStringCallback); // 콜백 설정
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result); // 결과가 저장될 string 설정

	curl_easy_perform(curl); // 요청 전송
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // 응답 받기
	curl_easy_cleanup(curl);

	return true;
}

size_t HttpRequest::WriteStringCallback(const char *in,
	size_t size, size_t num, string *out) {
	const size_t total = size * num; // 토탈 사이즈 계산
	out->append(in, total); // out에 받은 문자열만큼 추가
	return total;
}

size_t HttpRequest::WriteFileCallback(void *ptr, size_t size,
	size_t nmemb, void *stream) {
	// 받은 문자열 스트림에 저장 및 토탈 사이즈 계산
	const size_t total = fwrite(ptr, size, nmemb, (FILE *)stream);
	return total;
}
