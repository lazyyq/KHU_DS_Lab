#pragma once

#include <fstream>

#include "Genre.h"
#include "MusicItem.h"
#include "Player.h"
#include "Singer.h"
#include "SortedDoublyLinkedList.h"
#include "SortedList.h"

/**
*	Class for running main program
*/
class Application {
	friend class QtMainWindow;
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
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*	@param	_id			User ID
	*			_isAdmin	Is this user an admin?
	*/
	void Run(const std::string &_id, const bool _isAdmin);

	/**
	*	@brief	���Ǹ���Ʈ, ��������Ʈ, �÷��̸���Ʈ ���� ���Ϸ� ������.
	*	@pre	`files` �� `lyrics` ���丮�� ������.
	*	@post	����Ʈ���� �� ������ ������ ���Ͽ� �����.
	*/
	void Save();

	/**
	*	@brief	Add new record into master list and the song lists of
	*			its singer (artist) and genre.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@param	data	Record to add to list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddMusic(const MusicItem &data);

	/**
	*	@brief	Get record of music from keyboard and add to list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddMusicManually();

	/**
	*	@brief	Read record from an mp3 file and add to song list.
	*	@return	1 on success, 0 on failure.
	*/
	int AddMusicFromFile();

	/**
	*	@brief	Scan a folder recursively, read record from mp3 files inside
				and add to song list.
	*	@return	1 on success, 0 on failure.
	*/
	int AddMusicFromFolder();

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
	std::string mId; // User id
	bool mIsAdmin = false; // Is this user an admin?
	ifstream mInFile;					// input file descriptor
	ofstream mOutFile;					// output file descriptor
	SortedList<MusicItem> mMasterList;	// music item list
	SortedDoublyLinkedList<Singer> mSingerList;	// Singer list
	SortedDoublyLinkedList<Genre> mGenreList;	// Genre list
	Player *mPlayer;						// Playlist manager
	std::string mFilenameMasterList; // Masterlist filename
	std::string mFilenameArtistList; // Singer list filename
	std::string mFilenameGenreList; // Genre list filename
};
