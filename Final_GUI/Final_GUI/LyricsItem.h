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
	*	@brief	�ش� ���� ���縦 ������.
	*	@post	���簡 ����������.
	*	@pre	���簡 lyrics�� ���.
	*	@param	lyrics	���簡 �����.
	*	@return	���� ���� ���� �� 1, �ƴϸ� 0.
	*/
	int GetLyrics(std::string &lyrics);

	/**
	*	Comparator. Primary key �� ���� ��Ƽ��Ʈ��.
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
