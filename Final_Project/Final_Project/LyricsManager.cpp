#include "LyricsManager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "GeniusLyricsFetcher.h"
#include "utils/Utils.h"

#define LYRICS_FOLDERNAME	"lyrics"

using namespace std;
using namespace utils;

// 생성자
LyricsManager::LyricsManager() {
	ReadLyricsListFromFile(); // 파일에서 가사 읽기
}

// 파괴자
LyricsManager::~LyricsManager() {
	mLyricsList.MakeEmpty(); // 가사 리스트 초기화
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
		if (GeniusLyricsFetcher::GetLyricsFromGenius(
			music.GetName(), music.GetArtist(), lyrics)) {
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
				SaveLyrics(music.GetName(), music.GetArtist(), lyrics); // 저장
			}
		}
	}
}

// 가사 저장
int LyricsManager::SaveLyrics(const string &name,
	const string &artist, const string &lyrics) {
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
		}
	}
}
