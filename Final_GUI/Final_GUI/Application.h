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
	*	@brief	프로그램 구동에 필요한 디렉토리 생성.
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
	*	@brief	음악리스트, 가수리스트, 플레이리스트 등을 파일로 저장함.
	*	@pre	`files` 와 `lyrics` 디렉토리가 존재함.
	*	@post	리스트들이 각 폴더의 정해진 파일에 저장됨.
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
	*	@brief	가수 목록에서 가수를 찾아 해당 가수가 부른 모든 곡의 정보를 표시함.
	*/
	void SearchByArtist();

	/**
	*	@brief	장르 목록에서 장르를 찾아 해당 장르의 모든 곡의 정보를 표시함.
	*/
	void SearchByGenre();

	/**
	*	@brief	모든 곡의 정보를 화면에 표시함.
	*/
	void DisplayAllMusic();

	/**
	*	@brief	모든 리스트 초기화.
	*	@post	마스터리스트, 가수리스트, 장르리스트, 플레이리스트가 전부 초기화됨.
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
	*	@brief	파일을 읽기 모드로 열어 모든 정보를 리스트에 저장함.
	*	@pre	파일이 사용 중이 아님.
	*	@post	모든 정보가 리스트에 저장됨.
	*	@return	성공 시 1, 아니면 0.
	*/
	int ReadMusicListFromFile();

	/**
	*	@brief	파일을 쓰기 모드로 열어 리스트의 모든 정보를 저장함.
	*	@pre	파일이 사용 중이 아님.
	*	@post	리스트의 모든 정보가 파일에 저장됨.
	*	@return	성공 시 1, 아니면 0.
	*/
	int SaveMusicListToFile();

	/**
	*	@brief	파일을 읽기 모드로 열어 모든 정보를 리스트에 저장함.
	*	@pre	파일이 사용 중이 아님.
	*	@post	모든 정보가 리스트에 저장됨.
	*	@return	성공 시 1, 아니면 0.
	*/
	int ReadArtistListFromFile();

	/**
	*	@brief	파일을 쓰기 모드로 열어 리스트의 모든 정보를 저장함.
	*	@pre	파일이 사용 중이 아님.
	*	@post	리스트의 모든 정보가 파일에 저장됨.
	*	@return	성공 시 1, 아니면 0.
	*/
	int SaveArtistListToFile();

	/**
	*	@brief	파일을 읽기 모드로 열어 모든 정보를 리스트에 저장함.
	*	@pre	파일이 사용 중이 아님.
	*	@post	모든 정보가 리스트에 저장됨.
	*	@return	성공 시 1, 아니면 0.
	*/
	int ReadGenreListFromFile();

	/**
	*	@brief	파일을 쓰기 모드로 열어 리스트의 모든 정보를 저장함.
	*	@pre	파일이 사용 중이 아님.
	*	@post	리스트의 모든 정보가 파일에 저장됨.
	*	@return	성공 시 1, 아니면 0.
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
