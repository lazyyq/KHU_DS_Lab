#include "LyricsManager.h"

LyricsManager::LyricsManager() {
	InitLyricsList();
}

LyricsManager::~LyricsManager() {
	mLyricsList.MakeEmpty();
}

int LyricsManager::GetLyrics(const string name,
	const string artist, string &lyrics) {
	LyricsItem item(name, artist);
	int exists = mLyricsList.Get(item);
	if (exists) {
		item.GetLyrics(lyrics);
		return 1;
	} else {
		return 0;
	}
}

void LyricsManager::InitLyricsList() {
	// Create 'lyrics' folder
	filesystem::create_directory("lyrics");

	// Add lyrics items
	string name, artist;
	ifstream ifs;
	// Iterate through lyrics directory
	for (const auto &file : filesystem::directory_iterator("lyrics")) {
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
