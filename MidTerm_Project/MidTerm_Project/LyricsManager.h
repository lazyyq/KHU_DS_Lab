#pragma once

#include <iostream>
#include <string>
#include <filesystem>

#include "GeniusLyricsFetcher.h"
#include "LyricsItem.h"
#include "SortedDoublyLinkedList.h"
#include "LinkedList.h"
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
	*	@pre
	*	@post
	*	@return	1 on success, 0 otherwise
	*/
	int GetNum(int &n);

	/**
	*	From the list, fetch and display lyrics for the given music
	*	based on its title and name.
	*/
	void ShowLyrics(const MusicItem &music);

	int SaveLyrics(const string &name, const string &artist,
		const string &lyrics);

private:
	SortedDoublyLinkedList<LyricsItem> mLyricsList;

	void ReadLyricsListFromFile();
};