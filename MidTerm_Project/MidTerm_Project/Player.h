#pragma once

#include <iostream>

#include "SortedList.h"
#include "SortedDoublyLinkedList.h"
#include "MusicItem.h"
#include "PlaylistItem.h"
#include "LyricsManager.h"

#define PLAYLIST_FILENAME	"files/list_playlist.txt"

using namespace std;

class Player {
public:
	/**
	*	Constructor
	*/
	Player(SortedList<MusicItem> &inList);

	/**
	*	Destructor
	*/
	~Player();

	/**
	*	@brief	Get number from keyboard input.
	*	@pre
	*	@post
	*	@return	1 on success, 0 otherwise
	*/
	int GetNum(int &n);

	/**
	*	@brief	Search music from list with id and add to playlist.
	*	@pre	Music list and playlist is initialized.
	*	@post	Music retrieved from list is added to playlist.
	*/
	void AddToPlaylist();

	/**
	*	@brief	Play music from playlist in inserted order.
	*	@pre	Music exists in playlist.
	*	@post	Music in playlist is displayed in inserted order.
	*/
	void PlayInInsertOrder();

	/**
	*	@brief	Search music from list with id and delete from playlist.
	*	@pre	Music exists in music list and playlist.
	*	@post	Music retrieved from list is deleted from playlist.
	*/
	void DeleteFromPlaylist();

	int SavePlaylistToFile();

	int ReadPlaylistFromFile();

private:
	int mInsertOrder;					// Insert order of music in playlist
	SortedList<MusicItem> &mMusicList;
	SortedDoublyLinkedList<PlaylistItem> mPlaylist;	// music playlist
	LyricsManager mLyricsManager;		// Manages lyrics & lyrics files
};
