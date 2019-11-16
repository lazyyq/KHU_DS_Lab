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
	*	@brief	����Ʈ�� ����� ������ ǥ����.
	*	@pre	����Ʈ�� �ʱ�ȭ������.
	*	@post	�� �������� ǥ�õ�.
	*/
	void ListPlaylist();

	/**
	*	@brief	����Ʈ���� �� ���� ��� �ű⼭���� �����.
	*/
	void ChooseAndPlay();

	/**
	*	@brief	����Ʈ�� Ư���� �����Ǻ��� ����� ������.
	*	@param	position	���� ������. �� ù��°�� 1��. �ε����� �ٸ�.
	*/
	void PlayFromPosition(int position);

	/**
	*	@brief	���� ����ϰ� ��� Ƚ���� �ø�. ���� ��� ����� �̱����̰�
	*			�� ������ ǥ���ϴ� ���� ��ħ.
	*	@param	item	����ϰ� ���� ������ ����
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
	*			��� ���� ���Լ����� ���ĵ��־� ��ǻ� ó������ �����.
	*	@pre	Music exists in playlist.
	*	@post	Music in playlist is displayed in inserted order.
	*/
	void PlayInInsertOrder();

	/**
	*	@brief	����Ʈ�� ������ ���� �� ����Ʈ�� ����� �ش� ����Ʈ�� �����.
	*			���� �÷��̸���Ʈ���� �տ������� �������� �ϳ��� ������
	*			primary key�� ���Խð��� �����ϰ� �����ϰ� �� ����Ʈ�� �߰������ν�
	*			������ �� ����Ʈ�� ��� �ش� ����Ʈ�� �����.
	*	@pre	����Ʈ�� �ʱ�ȭ������. ���� ������.
	*	@post	���� ����Ʈ�� ������ �ٲ��� ����.
	*/
	void Shuffle();

	/**
	*	@brief	Search music from list with id and delete from playlist.
	*	@pre	Music exists in music list and playlist.
	*	@post	Music retrieved from list is deleted from playlist.
	*/
	void DeleteFromPlaylist();

	/**
	*	@brief	�÷��̸���Ʈ�� �������� ���Ϸ� ������.
	*	@pre	������ ������� �ƴ�.
	*	@post	�����۵��� ���Ͽ� �����.
	*	@return	���� �� 1, ���� �� 0.
	*/
	int SavePlaylistToFile();

	/**
	*	@brief	������ �о� �������� �÷��̸���Ʈ�� ����.
	*	@pre	������ ������� �ƴ�.
	*	@post	������ ������ �����ۿ� �����.
	*	@return	���� �� 1, ���� �� 0.
	*/
	int ReadPlaylistFromFile();

	/**
	*	@brief	����Ʈ ���� �ʱ�ȭ.
	*	@pre	����Ʈ�� �ʱ�ȭ������.
	*	@post	����Ʈ�� ������ �ʱ�ȭ��.
	*/
	void MakeEmpty();

private:
	int mInsertOrder;					// Insert order of music in playlist
	SortedList<MusicItem> &mMusicList;	// ���� �����͸���Ʈ
	SortedDoublyLinkedList<PlaylistItem> mPlaylist;	// music playlist
	LyricsManager mLyricsManager;		// Manages lyrics & lyrics files
};
