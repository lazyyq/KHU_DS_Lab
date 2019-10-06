#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "SortedList.h"
#include "ItemType.h"

#define FILENAMESIZE 1024

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
	~Application() {}

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	Display command on screen and get a input from keyboard.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	int GetCommand();

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddMusic();

	/**
	*	@brief	Display all records in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllMusic();

	/**
	*	@brief	Open a file by file descriptor as an input file.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	fileName	a filename to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenInFile(char* fileName);

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName	a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenOutFile(char* fileName);

	/**
	*	@brief	Open a file as a read mode, read all data on the file, and set list by the data.
	*	@pre	The file is not opened.
	*	@post	list holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile();

	/**
	*	@brief	Open a file as a write mode, and write all data into the file,
	*	@pre	The file is not opened.
	*	@post	the list is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile();

	/**
	*	@brief	Search and display music info with input id from list.
	*	@pre	None.
	*	@post	None.
	*	@return	None.
	*/
	void SearchById();

	/**
	*	@brief	Search and display music whose name contains input name from list.
	*	@pre	None.
	*	@post	None.
	*	@return	None.
	*/
	void SearchByName();

	/**
	*	@brief	Search and display music whose artist contains input artist from list.
	*	@pre	None.
	*	@post	None.
	*	@return	None.
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
	*	@brief	Delete selected music information from list.
	*	@pre	None.
	*	@post	None.
	*	@return	None.
	*/
	void DeleteMusic();

	/**
	*	@brief	Replace selected music information from list.
	*	@pre	None.
	*	@post	None.
	*	@return	None.
	*/
	void ReplaceMusic();

private:
	ifstream mInFile;		///< input file descriptor.
	ofstream mOutFile;		///< output file descriptor.
	SortedList<ItemType> mList;		///< item list.
	int mCommand;			///< current command number.
};

#endif	// _APPLICATION_H

