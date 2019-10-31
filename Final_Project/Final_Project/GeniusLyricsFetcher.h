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

/**
*	genius.com �� REST ��û�� ���� �뷡�� ���簡 ���Ե� ����Ʈ�� URL�� �˾Ƴ� ��,
*	�ش� URL�� HTML �ҽ��� �ܾ�� ���縸 �̾Ƴ��� ����ϱ� ���� Ŭ����.
*	static �Լ���θ� �̷���� �־� ���� �ν��Ͻ�ȭ�� �ʿ����� ������
*	genius.com �� API �׼��� ��ū�� genius_access_token.txt �� ������־�� ��.
*/
class GeniusLyricsFetcher {
public:
	/**
	*	@brief	genius.com���� �뷡 ����� ���� �̸��� �̿��Ͽ� ���縦 �˻��ؼ� ������.
	*	@post	genius_access_token.txt �� genius.com API �׼��� ��ū�� ���������.
	*	@pre	lyrics �� �뷡�� ���簡 �����.
	*	@param	name	�뷡�� ����
	*			artist	���� �̸�
	*			lyrics	�޾ƿ� ���簡 ����� string
	*	@return	���� �� 1, ���� �� 0.
	*/
	static int GetLyricsFromGenius(const std::string &name,
		const std::string &artist, std::string &lyrics);

private:
	/**
	*	@brief	cURL�� �̿��� Get ������Ʈ�� ������ �� ����� ���Ͽ� ������.
	*	@post	URL�� Get ������Ʈ�� ���� ����� ��� �ڵ尡 ��ȯ��.
	*	@param	url			������Ʈ�� ���� URL
	*			fp			����� ����� ����
	*			resultCode	����ڵ尡 �����
	*	@return	���� �� true, �ƴϸ� false.
	*/
	static bool SendGetRequest(const std::string &url,
		const FILE *fp, int &resultCode);

	/**
	*	@brief	cURL�� �̿��� Get ������Ʈ�� ������ �� ����� string�� ������.
	*	@post	URL�� Get ������Ʈ�� ���� ����� ��� �ڵ尡 ��ȯ��.
	*	@param	url			������Ʈ�� ���� URL
	*			result		����� ����� string
	*			resultCode	����ڵ尡 �����
	*	@return	���� �� true, �ƴϸ� false.
	*/
	static bool SendGetRequest(const std::string &url,
		std::string &result, int &resultCode);

	/**
	*	@brief	Get ������Ʈ�� ����� ���� ���� �ɰ����� ��ȯ�� ��
	*			�װ� ó���ϱ� ���� ȣ��Ǵ� �ݹ� �ڵ�.
	*	@pre	SendGetRequest()�� �̿��� Get ������Ʈ�� ����.
	*	@post	������Ʈ�� ������ string�� ��� ����.
	*	@return	���±��� �� ������ �� ũ��
	*/
	static size_t WiteStringCallback(const char *in, size_t size,
		size_t num, std::string *out);

	/**
	*	@brief	Get ������Ʈ�� ����� ���� ���� �ɰ����� ��ȯ�� ��
	*			�װ� ó���ϱ� ���� ȣ��Ǵ� �ݹ� �ڵ�.
	*	@pre	SendGetRequest()�� �̿��� Get ������Ʈ�� ����.
	*	@post	������Ʈ�� ������ stream�� ��� ����.
	*	@return	���±��� �� ������ �� ũ��
	*/
	static size_t WriteFileCallback(void *ptr, size_t size,
		size_t nmemb, void *stream);

	/**
	*	@brief	�������� �� JSON ������ ������ �Ľ��Ͽ� ���� URL�� ������.
	*	@pre	Get ������Ʈ�� ������ ������ ������ string�� �����.
	*	@post	result�� ������ URL�� ���.
	*	@param	jsonString	������ �������� �� JSON
	*			result		������ ���� URL�� ���
	*	@result	���� �� true, ���� �� false
	*/
	static bool GetLyricsUrl(const std::string &jsonString, std::string &result);

	/**
	*	@brief	���� URL�� HTML �ҽ��� �����ͼ� ���Ϸ� ������. �ҽ��� ũ�Ⱑ Ŀ��
	*			string�� ��⿡�� �������ϱ� ����.
	*	@pre	������ URL�� ã�Ƴ�.
	*	@post	���Ͽ� HTML �ҽ��� �����.
	*	@param	geniusUrl	�ҽ��� ������ URL
	*			fileName	�ҽ��� ����� ������ �̸�
	*	@return	���� �� true, ���� �� false
	*/
	static bool GetHTMLFromGenius(const std::string &geniusUrl,
		const std::string &fileName);

	/**
	*	@brief	HTML �ҽ����� ���縸 ��� �̾Ƴ�. �ļ��� ���� �����Ƽ� ���� § �ڵ�.
	*	@pre	HTML �ҽ��� ���Ͽ� ���������.
	*	@post	HTML �ҽ����� ���縸 �̾Ƴ��� lyrics�� ������.
	*	@param	fileName	HTML �ҽ��� ��� ���ϸ�
	*			lyrics		������ ���簡 ���
	*	@return	���� �� true, ���� �� false
	*/
	static bool ParseLyricsFromHTML(const std::string &fileName, std::string &lyrics);
};
