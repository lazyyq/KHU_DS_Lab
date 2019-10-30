#include "LyricsManager.h"

#define LYRICS_FOLDERNAME	"lyrics"

LyricsManager::LyricsManager() {
	ReadLyricsListFromFile();
}

LyricsManager::~LyricsManager() {
	mLyricsList.MakeEmpty();
}

int LyricsManager::GetNum(int &n) {
	int result = 1, input;

	cin >> input;
	if (cin.fail() == 1) { // Error, input is probably not int
		cin.clear(); // Clear fail flags
		result = 0; // We return 0 on failure
	} else {
		// We should not cin directly to n because
		// bad input such as char is recognized as 0,
		// which might be considered a valid number
		// by the function that called GetNum(n).
		n = input;
	}
	cin.ignore(100, '\n');

	return result;
}

void LyricsManager::ShowLyrics(const MusicItem &music) {
	LyricsItem item(music.GetName(), music.GetArtist());

	if (mLyricsList.Get(item)) {
		string lyrics;
		item.GetLyrics(lyrics);
		// We have lyrics for that music, show on console
		cout << "\n\t-------- Lyrics ------------------\n\n";
		cout << lyrics << endl;
	} else {
		// We don't have lyrics for that music, get from genius.com
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

		string lyrics;
		if (GeniusLyricsFetcher::GetLyricsFromGenius(
			music.GetName(), music.GetArtist(), lyrics)) {
			string indentedLyrics = lyrics;
			for (auto pos = indentedLyrics.find('\n'); pos != string::npos;
				pos = indentedLyrics.find('\n', pos + 1)) {
				indentedLyrics.replace(pos, 1, "\n\t");
			}
			cout << "\n\n\t------------------ Lyrics ------------------\n\n";
			cout << '\t' << indentedLyrics;
			cout << "\n\n\t--------------------------------------------\n\n";


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
				SaveLyrics(music.GetName(), music.GetArtist(), lyrics);
			}
		}
	}
}

int LyricsManager::SaveLyrics(const string &name,
	const string &artist, const string &lyrics) {
	string path =
		LYRICS_FOLDERNAME + string("/") + artist + " - " + name + ".txt";
	while (filesystem::exists(path)) {
		path.insert(path.length() - 4, "_2");
	}

	ofstream ofs(path);
	if (!ofs) {
		return 0;
	}
	ofs << name << endl << artist << endl << lyrics;
	ofs.close();

	LyricsItem item(name, artist, path);
	mLyricsList.Add(item);

	return 1;
}

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
