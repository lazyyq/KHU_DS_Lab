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
	*	@param	music	���縦 ǥ���� ��
	*/
	void ShowLyrics(const MusicItem &music);

	/**
	*	@brief	�ش� ��� ��Ƽ��Ʈ�� �̸��� �Բ� ���� ����.
	*	@param	music	���� ������ ��� ����
	*	@return	���� �������� �� ���� �� 1, ���� �� 0
	*/
	int SaveLyrics(const MusicItem &music,
		const std::string &lyrics);

	// ������ ���� ��������
	static int GetLyricsFromGenius(const MusicItem &music, std::string &lyrics);

private:
	SortedDoublyLinkedList<LyricsItem> mLyricsList; // ���� ����Ʈ

	void ReadLyricsListFromFile(); // ���Ϸκ��� ���縦 �о��
};
