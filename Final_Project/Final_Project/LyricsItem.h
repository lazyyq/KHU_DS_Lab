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
	*	@brief	해당 곡의 가사를 가져옴.
	*	@post	가사가 설정돼있음.
	*	@pre	가사가 lyrics에 담김.
	*	@param	lyrics	가사가 저장됨.
	*	@return	가사 저장 성공 시 1, 아니면 0.
	*/
	int GetLyrics(string &lyrics);

	/**
	*	Comparator. Primary key 는 곡명과 아티스트명.
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
