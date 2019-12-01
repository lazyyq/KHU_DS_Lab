#pragma once

#include <string>

class LyricsItem {
public:
	/**
	*	Constructor
	*/
	LyricsItem();

	LyricsItem(std::string inName, std::string inArtist);

	LyricsItem(std::string inName, std::string inArtist,
		std::string inFileName);

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
	int GetLyrics(std::string &lyrics);

	/**
	*	Comparator. Primary key 는 곡명과 아티스트명.
	*/
	bool operator==(const LyricsItem &that) const;
	bool operator<(const LyricsItem &that) const;
	bool operator<=(const LyricsItem &that) const;
	bool operator>(const LyricsItem &that) const;
	bool operator>=(const LyricsItem &that) const;

private:
	std::string mName; // Music name
	std::string mArtist; // Artist name
	std::string mFileName; // Lyrics filename
};
