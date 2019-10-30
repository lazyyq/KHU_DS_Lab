#pragma once

#include <iostream>
#include <string>
#include <filesystem>

#include "GeniusLyricsFetcher.h"
#include "LyricsItem.h"
#include "SortedDoublyLinkedList.h"
#include "MusicItem.h"

using namespace std;

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

	/**
	*	@brief	Get number from keyboard input.
	*	@return	1 on success, 0 otherwise
	*/
	int GetNum(int &n);

	/**
	*	@brief	From the list, fetch and display lyrics for the given music
	*			based on its title and name.
	*	@param	music	가사를 표시할 곡
	*/
	void ShowLyrics(const MusicItem &music);

	/**
	*	@brief	해당 곡과 아티스트의 이름과 함께 가사 저장.
	*	@param	name	곡 이름
	*			artist	아티스트 이름
	*			lyrics	가사가 저장됨
	*	@return	가사 가져오는 데 성공 시 1, 실패 시 0
	*/
	int SaveLyrics(const string &name, const string &artist,
		const string &lyrics);

private:
	SortedDoublyLinkedList<LyricsItem> mLyricsList; // 가사 리스트

	void ReadLyricsListFromFile(); // 파일로부터 가사를 읽어옴
};