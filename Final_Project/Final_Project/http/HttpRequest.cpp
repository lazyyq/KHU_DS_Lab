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

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL ����
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); // Ÿ�Ӿƿ� ����
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirection �� ���󰡱� ����
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback); // �ݹ� ����
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // ����� ����� ���� ������ ����

	curl_easy_perform(curl); // ��û ����
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // ���� �ޱ�
	curl_easy_cleanup(curl);

	return true;
}

bool HttpRequest::SendGetRequest(string &result, int &resultCode) {
	CURL *curl = curl_easy_init();
	if (!curl) {
		cout << "curl init failed.\n";
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL ����
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); // Ÿ�Ӿƿ� ����
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirection �� ���󰡱� ����
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteStringCallback); // �ݹ� ����
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result); // ����� ����� string ����

	curl_easy_perform(curl); // ��û ����
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resultCode); // ���� �ޱ�
	curl_easy_cleanup(curl);

	return true;
}

size_t HttpRequest::WriteStringCallback(const char *in,
	size_t size, size_t num, string *out) {
	const size_t total = size * num; // ��Ż ������ ���
	out->append(in, total); // out�� ���� ���ڿ���ŭ �߰�
	return total;
}

size_t HttpRequest::WriteFileCallback(void *ptr, size_t size,
	size_t nmemb, void *stream) {
	// ���� ���ڿ� ��Ʈ���� ���� �� ��Ż ������ ���
	const size_t total = fwrite(ptr, size, nmemb, (FILE *)stream);
	return total;
}
