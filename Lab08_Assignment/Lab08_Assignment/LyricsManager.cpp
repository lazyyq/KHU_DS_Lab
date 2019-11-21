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

// ������
LyricsManager::LyricsManager() {
	ReadLyricsListFromFile(); // ���Ͽ��� ���� �б�
}

// �ı���
LyricsManager::~LyricsManager() {
	mLyricsList.MakeEmpty(); // ���� ����Ʈ �ʱ�ȭ
}

// ���� �����ֱ�
void LyricsManager::ShowLyrics(const MusicItem &music) {
	LyricsItem item(music.GetName(), music.GetArtist());
	// ���� ����Ʈ�� �����ϴ��� �˻�
	if (mLyricsList.Get(item)) { // ���� �߰�
		string lyrics;
		item.GetLyrics(lyrics);
		// We have lyrics for that music, show on console
		cout << "\n\t-------- Lyrics ------------------\n\n";
		cout << lyrics << endl;
	} else { // ���簡 ����
		// We don't have lyrics for that music, get from genius.com
		// ���縦 ������ �������� ����
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

		// ������ ���� ��������
		string lyrics;
		if (GeniusLyricsFetcher::GetLyricsFromGenius(
			music.GetName(), music.GetArtist(), lyrics)) {
			// ���� ���� ���� ���� ���ٸ��� �տ� �� ����
			string indentedLyrics = lyrics;
			for (auto pos = indentedLyrics.find('\n'); pos != string::npos;
				pos = indentedLyrics.find('\n', pos + 1)) {
				// �� �ٹٲ� ���ڸ� �ٹٲ޹���+�ǹ��ڷ� ����
				indentedLyrics.replace(pos, 1, "\n\t");
			}
			// ���� ǥ��
			cout << "\n\n\t------------------ Lyrics ------------------\n\n";
			cout << '\t' << indentedLyrics;
			cout << "\n\n\t--------------------------------------------\n\n";

			// ���縦 ���Ϸ� �������� ����
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
				SaveLyrics(music.GetName(), music.GetArtist(), lyrics); // ����
			}
		}
	}
}

// ���� ����
int LyricsManager::SaveLyrics(const string &name,
	const string &artist, const string &lyrics) {
	// ���ϸ� ���ϱ�
	string path =
		LYRICS_FOLDERNAME + string("/") + artist + " - " + name + ".txt";
	while (filesystem::exists(path)) {
		// �ߺ��� ������ �����ϸ� .txt �տ� _2 �ٿ��� _2.txt �����
		path.insert(path.length() - 4, "_2");
	}

	ofstream ofs(path); // ���Ͻ�Ʈ�� ����
	if (!ofs) {
		return 0;
	}
	// ù°�ٰ� ��°�ٿ� ���� ���̸��� ��Ƽ��Ʈ, �״����ٺ��� ����
	ofs << name << endl << artist << endl << lyrics;
	ofs.close();

	// ���� ����Ʈ���� �߰�
	LyricsItem item(name, artist, path);
	mLyricsList.Add(item);

	return 1;
}

// ���Ͽ��� ���� �о����
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
