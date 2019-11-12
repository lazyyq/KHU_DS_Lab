#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "Utils.h"

#include "SortedList.h"
#include "SortedDoublyLinkedList.h"

#include "MusicItem.h"
#include "SimpleItem.h"
#include "PlaylistItem.h"
#include "Singer.h"
#include "Genre.h"
#include "Player.h"

#define CONSOLE_COLOR	"70"
#define MUSIC_LIST_FILENAME	"files/list_music.txt"
#define ARTIST_LIST_FILENAME	"files/list_artist.txt"
#define GENRE_LIST_FILENAME	"files/list_genre.txt"

using namespace std;
using namespace utils;

/**
*	Class for running main program
*/
class Application {
public:
	/**
	*	default constructor.
	*/
	Application();

	/**
	*	destructor.
	*/
	~Application();

	/**
	*	@brief	���α׷� ������ �ʿ��� ���丮 ����.
	*/
	void InitDirectories();

	/**
	*	@brief	���� CMDâ�� color scheme�� ������
	*/
	void SetConsoleColor();

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	���Ǹ���Ʈ, ��������Ʈ, �÷��̸���Ʈ ���� ���Ϸ� ������.
	*	@pre	`files` �� `lyrics` ���丮�� ������.
	*	@post	����Ʈ���� �� ������ ������ ���Ͽ� �����.
	*/
	void Save();

	/**
	*	@brief	Show main menu.
	*/
	void MenuMain();

	/**
	*	@brief	Show menu for managing music list.
	*/
	void MenuManage();

	/**
	*	@brief	Show menu for searching music.
	*/
	void MenuSearch();

	/**
	*	@brief	Show menu for playing music and managing playlist.
	*/
	void MenuPlaylists();

	// Not used.
	//void MenuMisc();

	/**
	*	@brief	Add new record into master list and the song lists of
	*			its singer (artist) and genre.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddMusicManually();

	int AddMusic();

	/**
	*	@brief	Delete selected music information from list and the song lists of
	*			its singer (artist) and genre.
	*/
	void DeleteMusic();

	/**
	*	@brief	Replace selected music information from list.
	*/
	void ReplaceMusic();

	/**
	*	@brief	Search and display music info with input id from list.
	*/
	void SearchById();

	/**
	*	@brief	Search and display music whose name contains input name from list.
	*/
	void SearchByName();

	/**
	*	@brief	���� ��Ͽ��� ������ ã�� �ش� ������ �θ� ��� ���� ������ ǥ����.
	*/
	void SearchByArtist();

	/**
	*	@brief	�帣 ��Ͽ��� �帣�� ã�� �ش� �帣�� ��� ���� ������ ǥ����.
	*/
	void SearchByGenre();

	/**
	*	@brief	��� ���� ������ ȭ�鿡 ǥ����.
	*/
	void DisplayAllMusic();

	/**
	*	@brief	��� ����Ʈ �ʱ�ȭ.
	*	@post	�����͸���Ʈ, ��������Ʈ, �帣����Ʈ, �÷��̸���Ʈ�� ���� �ʱ�ȭ��.
	*/
	void MakeEmpty();

	/**
	*	@brief	Open a file by file descriptor as an input file.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	fileName	a filename to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenInFile(string fileName);

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName	a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenOutFile(string fileName);

	/**
	*	@brief	������ �б� ���� ���� ��� ������ ����Ʈ�� ������.
	*	@pre	������ ��� ���� �ƴ�.
	*	@post	��� ������ ����Ʈ�� �����.
	*	@return	���� �� 1, �ƴϸ� 0.
	*/
	int ReadMusicListFromFile();

	/**
	*	@brief	������ ���� ���� ���� ����Ʈ�� ��� ������ ������.
	*	@pre	������ ��� ���� �ƴ�.
	*	@post	����Ʈ�� ��� ������ ���Ͽ� �����.
	*	@return	���� �� 1, �ƴϸ� 0.
	*/
	int SaveMusicListToFile();

	/**
	*	@brief	������ �б� ���� ���� ��� ������ ����Ʈ�� ������.
	*	@pre	������ ��� ���� �ƴ�.
	*	@post	��� ������ ����Ʈ�� �����.
	*	@return	���� �� 1, �ƴϸ� 0.
	*/
	int ReadArtistListFromFile();

	/**
	*	@brief	������ ���� ���� ���� ����Ʈ�� ��� ������ ������.
	*	@pre	������ ��� ���� �ƴ�.
	*	@post	����Ʈ�� ��� ������ ���Ͽ� �����.
	*	@return	���� �� 1, �ƴϸ� 0.
	*/
	int SaveArtistListToFile();

	/**
	*	@brief	������ �б� ���� ���� ��� ������ ����Ʈ�� ������.
	*	@pre	������ ��� ���� �ƴ�.
	*	@post	��� ������ ����Ʈ�� �����.
	*	@return	���� �� 1, �ƴϸ� 0.
	*/
	int ReadGenreListFromFile();

	/**
	*	@brief	������ ���� ���� ���� ����Ʈ�� ��� ������ ������.
	*	@pre	������ ��� ���� �ƴ�.
	*	@post	����Ʈ�� ��� ������ ���Ͽ� �����.
	*	@return	���� �� 1, �ƴϸ� 0.
	*/
	int SaveGenreListToFile();


private:
	ifstream mInFile;					// input file descriptor
	ofstream mOutFile;					// output file descriptor
	SortedList<MusicItem> mMasterList;	// music item list
	SortedDoublyLinkedList<Singer> mSingerList;	// Singer list
	SortedDoublyLinkedList<Genre> mGenreList;	// Genre list
	Player mPlayer;						// Playlist manager
};

#endif	// _APPLICATION_H
