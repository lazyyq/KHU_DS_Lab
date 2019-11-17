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

	/**
	*	@brief	From the list, fetch and display lyrics for the given music
	*			based on its title and name.
	*	@param	music	���縦 ǥ���� ��
	*/
	void ShowLyrics(const MusicItem &music);

	/**
	*	@brief	�ش� ��� ��Ƽ��Ʈ�� �̸��� �Բ� ���� ����.
	*	@param	name	�� �̸�
	*			artist	��Ƽ��Ʈ �̸�
	*			lyrics	���簡 �����
	*	@return	���� �������� �� ���� �� 1, ���� �� 0
	*/
	int SaveLyrics(const std::string &name, const std::string &artist,
		const std::string &lyrics);

private:
	SortedDoublyLinkedList<LyricsItem> mLyricsList; // ���� ����Ʈ

	void ReadLyricsListFromFile(); // ���Ϸκ��� ���縦 �о��
};
