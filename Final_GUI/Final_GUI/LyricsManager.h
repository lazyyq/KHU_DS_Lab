#pragma once

#include "LyricsItem.h"
#include "MusicItem.h"
#include "SortedDoublyLinkedList.h"

class LyricsManager {
public:
	/**
	*	Constructor
	*/
	LyricsManager();

	/**
	*	Destructor
	*/
	~LyricsManager();

	// Get lyrics
	bool GetLyrics(const MusicItem &music, std::string &lyrics);

	/**
	*	@brief	From the list, fetch and display lyrics for the given music
	*			based on its title and name.
	*	@param	music	가사를 표시할 곡
	*/
	void ShowLyrics(const MusicItem &music);

	/**
	*	@brief	해당 곡과 아티스트의 이름과 함께 가사 저장.
	*	@param	music	가사 정보가 담긴 음악
	*	@return	가사 가져오는 데 성공 시 1, 실패 시 0
	*/
	int SaveLyrics(const MusicItem &music,
		const std::string &lyrics);

	// 웹에서 가사 가져오기
	static int GetLyricsFromGenius(const MusicItem &music, std::string &lyrics);

private:
	SortedDoublyLinkedList<LyricsItem> mLyricsList; // 가사 리스트

	void ReadLyricsListFromFile(); // 파일로부터 가사를 읽어옴
};
