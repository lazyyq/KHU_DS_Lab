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
	*	@brief	�ش� ���� ���縦 ������.
	*	@post	���簡 ����������.
	*	@pre	���簡 lyrics�� ���.
	*	@param	lyrics	���簡 �����.
	*	@return	���� ���� ���� �� 1, �ƴϸ� 0.
	*/
	int GetLyrics(string &lyrics);

	/**
	*	Comparator. Primary key �� ���� ��Ƽ��Ʈ��.
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
