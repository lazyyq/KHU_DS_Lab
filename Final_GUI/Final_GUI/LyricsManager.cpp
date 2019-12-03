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

// ������
LyricsManager::LyricsManager() {
	ReadLyricsListFromFile(); // ���Ͽ��� ���� �б�
}

// �ı���
LyricsManager::~LyricsManager() {
	mLyricsList.MakeEmpty(); // ���� ����Ʈ �ʱ�ȭ
}

// ���� ��ȯ
bool LyricsManager::GetLyrics(const MusicItem &music, std::string &lyrics) {
	LyricsItem item(music.GetName(), music.GetArtist());
	// ���� ����Ʈ�� �����ϴ��� �˻�
	if (mLyricsList.Get(item)) { // ���� �߰�
		item.GetLyrics(lyrics);
		return true;
	} else {
		return false;
	}
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
		if (GetLyricsFromGenius(music, lyrics)) {
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
				SaveLyrics(music, lyrics); // ����
			}
		}
	}
}

// ���� ����
int LyricsManager::SaveLyrics(const MusicItem &music, const string &lyrics) {
	const string name = music.GetName(), artist = music.GetArtist();
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

	// ������Ʈ ����
	string result;
	int resultCode;
	req.SendGetRequest(result, resultCode);
	if (resultCode != 200) {
		// 200 �� �ƴϸ� ���з� �����ϰ� �ٷ� �Լ� ����
		return 0;
	}

	// JSON ������ ���信�� ���� URL ��������
	string lyricsUrl;
	{
		Json::Value value; // �Ľ̵� ������ ��� ����
		JSONCPP_STRING err;
		Json::CharReaderBuilder builder;
		Json::CharReader *reader = builder.newCharReader();

		// string�� ��� JSON ������ �Ľ��Ͽ� value�� �迭�� ���·� ����
		if (!reader->parse(result.c_str(),
			result.c_str() + result.length(), &value, &err)) {
			// TODO: Error!
			cout << "error\n";
			return false;
		}

		// URL�� ��� �κ��� ã�� ����
		lyricsUrl = value["response"]["hits"][0]["result"]["url"].asString(); // "" if null
		if (lyricsUrl == "") {
			return false;
		}
	}
	// ���� URL�� ���� HTML �ҽ� �޾ƿ���
	{
		int resultCode;

		FILE *fp;
		fopen_s(&fp, GENIUS_HTML_TEMPFILENAME, "wb"); // ���� ����
		if (!fp) {
			return false;
		}

		// ��û �����ϰ� �� ����� ���Ͽ� ����
		HttpRequest tmpReq;
		tmpReq.SetUrl(lyricsUrl);
		tmpReq.SendGetRequest(fp, resultCode);

		if (fp) {
			fclose(fp);
		}
		if (resultCode != 200) {
			return false; // resultCode�� 200�̸� �������� ����
		}
	}
	// HTML �ҽ����� ���縸 ����, lyrics�� ����
	{
		// HTML �ҽ��� ��� ���� ����
		ifstream ifs(GENIUS_HTML_TEMPFILENAME);
		if (!ifs || ifs.peek() == EOF) {
			if (ifs.is_open()) {
				ifs.close();
			}
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
		filesystem::remove(GENIUS_HTML_TEMPFILENAME); // HTML �ҽ� ������ �ӽ������̾����Ƿ� ����
	}

	return 1;
}
