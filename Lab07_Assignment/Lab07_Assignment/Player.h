#pragma once

#include "LyricsManager.h"
#include "MusicItem.h"
#include "PlaylistItem.h"
#include "SortedDoublyLinkedList.h"
#include "SortedList.h"

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
	*	@brief	리스트의 곡들의 정보를 표시함.
	*	@pre	리스트가 초기화돼있음.
	*	@post	곡 정보들이 표시됨.
	*/
	void ListPlaylist();

	/**
	*	@brief	리스트에서 한 곡을 골라 거기서부터 재생함.
	*/
	void ChooseAndPlay();

	/**
	*	@brief	리스트의 특정한 포지션부터 재생을 시작함.
	*	@param	position	곡의 포지션. 맨 첫번째가 1임. 인덱스와 다름.
	*/
	void PlayFromPosition(int position);

	/**
	*	@brief	곡을 재생하고 재생 횟수를 늘림. 실제 재생 기능은 미구현이고
	*			곡 정보를 표시하는 데서 그침.
	*	@param	item	재생하고 싶은 아이템 정보
	*/
	void Play(PlaylistItem &item);

	/**
	*	@brief	Search music from list with id and add to playlist.
	*	@pre	Music list and playlist is initialized.
	*	@post	Music retrieved from list is added to playlist.
	*/
	void AddToPlaylist();

	/**
	*	@brief	Play music from playlist in inserted order.
	*			사실 곡이 삽입순으로 정렬돼있어 사실상 처음부터 재생함.
	*	@pre	Music exists in playlist.
	*	@post	Music in playlist is displayed in inserted order.
	*/
	void PlayInInsertOrder();

	/**
	*	@brief	리스트의 순서를 섞어 새 리스트를 만들고 해당 리스트를 재생함.
	*			기존 플레이리스트에서 앞에서부터 아이템을 하나씩 꺼내서
	*			primary key인 삽입시간을 랜덤하게 설정하고 새 리스트에 추가함으로써
	*			랜덤한 새 리스트를 얻고 해당 리스트를 재생함.
	*	@pre	리스트가 초기화돼있음. 곡이 존재함.
	*	@post	기존 리스트의 내용은 바뀌지 않음.
	*/
	void Shuffle();

	/**
	*	@brief	Search music from list with id and delete from playlist.
	*	@pre	Music exists in music list and playlist.
	*	@post	Music retrieved from list is deleted from playlist.
	*/
	void DeleteFromPlaylist();

	/**
	*	@brief	플레이리스트의 아이템을 파일로 저장함.
	*	@pre	파일이 사용중이 아님.
	*	@post	아이템들이 파일에 저장됨.
	*	@return	성공 시 1, 실패 시 0.
	*/
	int SavePlaylistToFile();

	/**
	*	@brief	파일을 읽어 아이템을 플레이리스트에 저장.
	*	@pre	파일이 사용중이 아님.
	*	@post	파일의 정보가 아이템에 저장됨.
	*	@return	성공 시 1, 실패 시 0.
	*/
	int ReadPlaylistFromFile();

	/**
	*	@brief	리스트 내용 초기화.
	*	@pre	리스트가 초기화돼있음.
	*	@post	리스트의 내용이 초기화됨.
	*/
	void MakeEmpty();

private:
	int mInsertOrder;					// Insert order of music in playlist
	SortedList<MusicItem> &mMusicList;	// 음악 마스터리스트
	SortedDoublyLinkedList<PlaylistItem> mPlaylist;	// music playlist
	LyricsManager mLyricsManager;		// Manages lyrics & lyrics files
};
