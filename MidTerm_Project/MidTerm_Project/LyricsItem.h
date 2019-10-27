#pragma once

#include <string>
#include <fstream>

using namespace std;

class LyricsItem {
public:
	/**
	*	Constructor
	*/
	LyricsItem();

	LyricsItem(string inName, string inArtist);

	LyricsItem(string inName, string inArtist,
		string inFileName);

	/**
	*	Destructor
	*/
	~LyricsItem();

	/**
	*	Get lyrics
	*/
	int GetLyrics(string &lyrics);

	/**
	*	Comparator
	*/
	bool operator==(const LyricsItem &that) const;
	bool operator<(const LyricsItem &that) const;
	bool operator<=(const LyricsItem &that) const;
	bool operator>(const LyricsItem &that) const;
	bool operator>=(const LyricsItem &that) const;

private:
	string mName; // Music name
	string mArtist; // Artist name
	string mFileName; // Lyrics filename
};
