#include "LyricsManager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "GeniusAccessToken.h"
#include "http/HttpRequest.h"
#include "utils/StringUtils.h"
#include "utils/Utils.h"

#define LYRICS_FOLDERNAME			"data/lyrics"
#define GENIUS_HTML_TEMPFILENAME	"genius_html_temp.txt"

using namespace std;
using namespace utils;
using namespace stringutils;

// 생성자
LyricsManager::LyricsManager() {
	ReadLyricsListFromFile(); // 파일에서 가사 읽기
}

// 파괴자
LyricsManager::~LyricsManager() {
	mLyricsList.MakeEmpty(); // 가사 리스트 초기화
}

// 가사 반환
bool LyricsManager::GetLyrics(const MusicItem &music, std::string &lyrics) {
	LyricsItem item(music.GetName(), music.GetArtist());
	// 가사 리스트에 존재하는지 검색
	if (mLyricsList.Get(item)) { // 가사 발견
		item.GetLyrics(lyrics);
		return true;
	} else {
		return false;
	}
}

// 가사 보여주기
void LyricsManager::ShowLyrics(const MusicItem &music) {
	LyricsItem item(music.GetName(), music.GetArtist());
	// 가사 리스트에 존재하는지 검색
	if (mLyricsList.Get(item)) { // 가사 발견
		string lyrics;
		item.GetLyrics(lyrics);
		// We have lyrics for that music, show on console
		cout << "\n\t-------- Lyrics ------------------\n\n";
		cout << lyrics << endl;
	} else { // 가사가 없다
		// We don't have lyrics for that music, get from genius.com
		// 가사를 웹에서 가져올지 묻기
		int fetchFromWeb = -1;
		while (!((fetchFromWeb == 0) || (fetchFromWeb == 1))) {
			cout << "\n\tWe don't have lyrics for \"" << music.GetName()
				<< "\", shall we look for it on the web? (1: yes / 0: no): ";
			if (!GetNum(fetchFromWeb)) {
				continue;
			}
		}
		if (fetchFromWeb == 0) {
			return;
		}

		// 웹에서 가사 가져오기
		string lyrics;
		if (GetLyricsFromGenius(music, lyrics)) {
			// 보기 좋게 가사 한줄 한줄마다 앞에 탭 삽입
			string indentedLyrics = lyrics;
			for (auto pos = indentedLyrics.find('\n'); pos != string::npos;
				pos = indentedLyrics.find('\n', pos + 1)) {
				// 각 줄바꿈 문자를 줄바꿈문자+탭문자로 변경
				indentedLyrics.replace(pos, 1, "\n\t");
			}
			// 가사 표시
			cout << "\n\n\t------------------ Lyrics ------------------\n\n";
			cout << '\t' << indentedLyrics;
			cout << "\n\n\t--------------------------------------------\n\n";

			// 가사를 파일로 저장할지 묻기
			int save = -1;
			while (!((save == 0) || (save == 1))) {
				cout << "\n\n\tIs this the right lyrics for your song?\n"
					<< "\tIf yes, we'll save it for you so we can load it faster next time."
					<< " (1: yes / 0: no): ";
				if (!GetNum(save)) {
					continue;
				}
			}
			if (save == 1) {
				SaveLyrics(music, lyrics); // 저장
			}
		}
	}
}

// 가사 저장
int LyricsManager::SaveLyrics(const MusicItem &music, const string &lyrics) {
	const string name = music.GetName(), artist = music.GetArtist();
	// 파일명 정하기
	string path =
		LYRICS_FOLDERNAME + string("/") + artist + " - " + name + ".txt";
	while (filesystem::exists(path)) {
		// 중복된 파일이 존재하면 .txt 앞에 _2 붙여서 _2.txt 만들기
		path.insert(path.length() - 4, "_2");
	}

	ofstream ofs(path); // 파일스트림 열기
	if (!ofs) {
		return 0;
	}
	// 첫째줄과 둘째줄엔 각각 곡이름과 아티스트, 그다음줄부터 가사
	ofs << name << endl << artist << endl << lyrics;
	ofs.close();

	// 가사 리스트에도 추가
	LyricsItem item(name, artist, path);
	mLyricsList.Add(item);

	return 1;
}

// 파일에서 가사 읽어오기
void LyricsManager::ReadLyricsListFromFile() {
	// Create 'lyrics' folder
	filesystem::create_directory(LYRICS_FOLDERNAME);

	// Add lyrics items
	string name, artist;
	ifstream ifs;
	// Iterate through lyrics directory
	for (const auto &file : filesystem::directory_iterator(LYRICS_FOLDERNAME)) {
		ifs.open(file.path());
		if (ifs && ifs.peek() != EOF) {
			getline(ifs, name); // First line : music title
			getline(ifs, artist); // Second line : artist
			// Rest of the file is the actual lyrics

			LyricsItem item(name, artist, file.path().string());
			mLyricsList.Add(item); // Add to list
			ifs.close();
		} else {
			if (ifs.is_open()) {
				ifs.close();
			}
		}
	}
}

int LyricsManager::GetLyricsFromGenius(const MusicItem &music, string &lyrics) {
	HttpRequest req;

	// Setup url for sending get request
	// Our search query is "`Artist` `Title`". ex) "Anne Marie 2002"
	const string searchApi = "https://api.genius.com/search";
	req.SetUrl(searchApi);
	req.AddParam("q", music.GetArtist() + " " + music.GetName());
	req.AddParam("access_token", GENIUS_ACCESS_TOKEN);

	// 리퀘스트 전송
	string result;
	int resultCode;
	req.SendGetRequest(result, resultCode);
	if (resultCode != 200) {
		// 200 이 아니면 실패로 간주하고 바로 함수 종료
		return 0;
	}

	// JSON 형태의 응답에서 가사 URL 가져오기
	string lyricsUrl;
	{
		Json::Value value; // 파싱된 내용이 담길 변수
		JSONCPP_STRING err;
		Json::CharReaderBuilder builder;
		Json::CharReader *reader = builder.newCharReader();

		// string에 담긴 JSON 문서를 파싱하여 value에 배열의 형태로 저장
		if (!reader->parse(result.c_str(),
			result.c_str() + result.length(), &value, &err)) {
			// TODO: Error!
			cout << "error\n";
			return false;
		}

		// URL이 담긴 부분을 찾아 저장
		lyricsUrl = value["response"]["hits"][0]["result"]["url"].asString(); // "" if null
		if (lyricsUrl == "") {
			return false;
		}
	}
	// 가사 URL을 따라가 HTML 소스 받아오기
	{
		int resultCode;

		FILE *fp;
		fopen_s(&fp, GENIUS_HTML_TEMPFILENAME, "wb"); // 파일 열기
		if (!fp) {
			return false;
		}

		// 요청 전송하고 그 결과를 파일에 저장
		HttpRequest tmpReq;
		tmpReq.SetUrl(lyricsUrl);
		tmpReq.SendGetRequest(fp, resultCode);

		if (fp) {
			fclose(fp);
		}
		if (resultCode != 200) {
			return false; // resultCode가 200이면 성공으로 간주
		}
	}
	// HTML 소스에서 가사만 추출, lyrics에 저장
	{
		// HTML 소스가 담긴 파일 열기
		ifstream ifs(GENIUS_HTML_TEMPFILENAME);
		if (!ifs || ifs.peek() == EOF) {
			if (ifs.is_open()) {
				ifs.close();
			}
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
		filesystem::remove(GENIUS_HTML_TEMPFILENAME); // HTML 소스 파일은 임시파일이었으므로 삭제
	}

	return 1;
}
