#pragma once

#include <iostream>
#include <string>
#include <filesystem>

#include "GeniusLyricsFetcher.h"
#include "LyricsItem.h"
#include "SortedDoublyLinkedList.h"
#include "LinkedList.h"

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
	*	From the list, look for lyrics for the given artist and title.
	*
	*	@return	1 on success, 0 on failure.
	*/
	int GetLyrics(const string &name, const string &artist,
		string &lyrics);

	int SaveLyrics(const string &name, const string &artist,
		const string &lyrics);

private:
	SortedDoublyLinkedList<LyricsItem> mLyricsList;

	void InitLyricsList();
};