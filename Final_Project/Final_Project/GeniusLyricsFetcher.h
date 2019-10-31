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
*	genius.com 에 REST 요청을 보내 노래의 가사가 포함된 사이트의 URL을 알아낸 뒤,
*	해당 URL의 HTML 소스를 긁어와 가사만 뽑아내어 출력하기 위한 클래스.
*	static 함수들로만 이루어져 있어 따로 인스턴스화가 필요하지 않으며
*	genius.com 의 API 액세스 토큰이 genius_access_token.txt 에 저장돼있어야 함.
*/
class GeniusLyricsFetcher {
public:
	/**
	*	@brief	genius.com에서 노래 제목과 가수 이름을 이용하여 가사를 검색해서 가져옴.
	*	@post	genius_access_token.txt 에 genius.com API 액세스 토큰이 저장돼있음.
	*	@pre	lyrics 에 노래의 가사가 저장됨.
	*	@param	name	노래의 제목
	*			artist	가수 이름
	*			lyrics	받아온 가사가 저장될 string
	*	@return	성공 시 1, 실패 시 0.
	*/
	static int GetLyricsFromGenius(const std::string &name,
		const std::string &artist, std::string &lyrics);

private:
	/**
	*	@brief	cURL을 이용해 Get 리퀘스트를 보내고 그 결과를 파일에 저장함.
	*	@post	URL에 Get 리퀘스트를 보낸 결과와 결과 코드가 반환됨.
	*	@param	url			리퀘스트를 보낼 URL
	*			fp			결과가 저장될 파일
	*			resultCode	결과코드가 저장됨
	*	@return	성공 시 true, 아니면 false.
	*/
	static bool SendGetRequest(const std::string &url,
		const FILE *fp, int &resultCode);

	/**
	*	@brief	cURL을 이용해 Get 리퀘스트를 보내고 그 결과를 string에 저장함.
	*	@post	URL에 Get 리퀘스트를 보낸 결과와 결과 코드가 반환됨.
	*	@param	url			리퀘스트를 보낼 URL
	*			result		결과가 저장될 string
	*			resultCode	결과코드가 저장됨
	*	@return	성공 시 true, 아니면 false.
	*/
	static bool SendGetRequest(const std::string &url,
		std::string &result, int &resultCode);

	/**
	*	@brief	Get 리퀘스트의 결과가 여러 개로 쪼개져서 반환될 때
	*			그걸 처리하기 위해 호출되는 콜백 코드.
	*	@pre	SendGetRequest()를 이용해 Get 리퀘스트를 보냄.
	*	@post	리퀘스트의 응답을 string에 계속 더함.
	*	@return	여태까지 온 응답의 총 크기
	*/
	static size_t WiteStringCallback(const char *in, size_t size,
		size_t num, std::string *out);

	/**
	*	@brief	Get 리퀘스트의 결과가 여러 개로 쪼개져서 반환될 때
	*			그걸 처리하기 위해 호출되는 콜백 코드.
	*	@pre	SendGetRequest()를 이용해 Get 리퀘스트를 보냄.
	*	@post	리퀘스트의 응답을 stream에 계속 더함.
	*	@return	여태까지 온 응답의 총 크기
	*/
	static size_t WriteFileCallback(void *ptr, size_t size,
		size_t nmemb, void *stream);

	/**
	*	@brief	서버에서 온 JSON 형태의 응답을 파싱하여 가사 URL을 추출함.
	*	@pre	Get 리퀘스트를 보내서 도착한 응답이 string에 저장됨.
	*	@post	result에 가사의 URL이 담김.
	*	@param	jsonString	서버의 응답으로 온 JSON
	*			result		추출한 가사 URL이 담김
	*	@result	성공 시 true, 실패 시 false
	*/
	static bool GetLyricsUrl(const std::string &jsonString, std::string &result);

	/**
	*	@brief	가사 URL의 HTML 소스를 가져와서 파일로 저장함. 소스의 크기가 커서
	*			string에 담기에는 부적합하기 때문.
	*	@pre	가사의 URL을 찾아냄.
	*	@post	파일에 HTML 소스가 저장됨.
	*	@param	geniusUrl	소스를 가져올 URL
	*			fileName	소스가 저장될 파일의 이름
	*	@return	성공 시 true, 실패 시 false
	*/
	static bool GetHTMLFromGenius(const std::string &geniusUrl,
		const std::string &fileName);

	/**
	*	@brief	HTML 소스에서 가사만 골라서 뽑아냄. 파서를 쓰기 귀찮아서 대충 짠 코드.
	*	@pre	HTML 소스가 파일에 저장돼있음.
	*	@post	HTML 소스에서 가사만 뽑아내서 lyrics에 저장함.
	*	@param	fileName	HTML 소스가 담긴 파일명
	*			lyrics		추출한 가사가 담김
	*	@return	성공 시 true, 실패 시 false
	*/
	static bool ParseLyricsFromHTML(const std::string &fileName, std::string &lyrics);
};
