#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "SortedList.h"
#include "UnsortedLinkedList.h"
#include "LinkedList.h"
#include "SortedDoublyLinkedList.h"

#include "MusicItem.h"
#include "PlaylistItem.h"
#include "Singer.h"
#include "Player.h"

#define CONSOLE_COLOR	"70"
#define MUSIC_LIST_FILENAME	"files/list_music.txt"
#define FILENAMESIZE 1024

using namespace std;

/**
*	application class for item management simply.
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
	*	@brief	Clear console.
	*/
	void Clear();

	/**
	*	@brief	Pause console.
	*/
	void Pause();

	/**
	*	@brief	Display message and pause console.
	*/
	void Pause(const string &message);

	/**
	*	@brief	Get number from keyboard input.
	*	@pre
	*	@post
	*	@return	1 on success, 0 otherwise
	*/
	int GetNum(int &n);

	/**
	*	Initialize required directories
	*/
	void InitDirectories();

	void SetConsoleColor();

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	Save music list, playlist, etc.
	*/
	void Save();

	void MenuMain();
	void MenuManage();
	void MenuSearch();
	void MenuPlaylists();
	void MenuMisc();

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddMusic();

	/**
	*	@brief	Delete selected music information from list.
	*	@pre	None.
	*	@post	None.
	*/
	void DeleteMusic();

	/**
	*	@brief	Replace selected music information from list.
	*	@pre	None.
	*	@post	None.
	*/
	void ReplaceMusic();

	/**
	*	@brief	Search and display music info with input id from list.
	*	@pre	None.
	*	@post	None.
	*/
	void SearchById();

	/**
	*	@brief	Search and display music whose name contains input name from list.
	*	@pre	None.
	*	@post	None.
	*/
	void SearchByName();

	/**
	*	@brief	Search and display music whose artist contains input artist from list.
	*	@pre	None.
	*	@post	None.
	*/
	void SearchByArtist();

	/**
	*	@brief	Search and display music info with input genre from list.
	*	@pre	None.
	*	@post	None.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	void SearchByGenre();

	/**
	*	@brief	Display all records in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllMusic();

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
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
	*	@brief	Open a file as a read mode, read all data on the file, and set list by the data.
	*	@pre	The file is not opened.
	*	@post	list holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadMusicListFromFile();

	/**
	*	@brief	Open a file as a write mode, and write all data into the file,
	*	@pre	The file is not opened.
	*	@post	the list is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int SaveMusicListToFile();

	/**
	*	@brief	Add a new singer.
	*	@pre	Singer list is initalized.
	*	@post	New singer is added to singer list.
	*/
	void AddSinger();

	/**
	*	@brief	Add a new song to a singer's song list. Will require user
	*			to add a new singer first if not exists.
	*	@pre	Singer list is initialized and song exists in music master list.
	*	@post	New song is added to the singer's song list. If the singer
	*			does not exist, he is added as well.
	*/
	void AddSong();

	/**
	*	@brief	Search and display all songs by specific singer whose name
	*			exactly matches the user's input.
	*	@pre	Music master list and singer list is initialized.
	*	@post	Music info from the singer is displayed.
	*/
	void SearchBySinger();


private:
	ifstream mInFile;					// input file descriptor
	ofstream mOutFile;					// output file descriptor
	SortedList<MusicItem> mMasterList;	// music item list
	LinkedList<Singer> mSingerList;	// Singer list
	Player mPlayer;						// Playlist manager
};

#endif	// _APPLICATION_H

