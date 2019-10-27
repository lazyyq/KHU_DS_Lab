#include "LyricsManager.h"

#define LYRICS_FOLDERNAME	"lyrics"

LyricsManager::LyricsManager() {
	InitLyricsList();
}

LyricsManager::~LyricsManager() {
	mLyricsList.MakeEmpty();
}

int LyricsManager::GetLyrics(const string &name,
	const string &artist, string &lyrics) {
	LyricsItem item(name, artist);
	int exists = mLyricsList.Get(item);
	if (exists) {
		item.GetLyrics(lyrics);
		return 1;
	} else {
		return 0;
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

void LyricsManager::InitLyricsList() {
	// Create 'lyrics' folder
	filesystem::create_directory(LYRICS_FOLDERNAME);

	// Add lyrics items
	string name, artist;
	ifstream ifs;
	// Iterate through lyrics directory
	for (const auto &file : filesystem::directory_iterator(LYRICS_FOLDERNAME)) {
		ifs.open(file.path());
		if (ifs) {
			getline(ifs, name); // First line : music title
			getline(ifs, artist); // Second line : artist
			// Rest of the file is the actual lyrics

			LyricsItem item(name, artist, file.path().string());
			mLyricsList.Add(item); // Add to list
			ifs.close();
		}
	}
}
