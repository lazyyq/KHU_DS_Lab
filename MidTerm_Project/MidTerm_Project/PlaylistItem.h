#ifndef _PLAYITEM_H
#define _PLAYITEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#define PLAYITEM_ATTR_INDENT_SIZE	25

using namespace std;

class PlaylistItem {
public:
	/**
	*	Default constructor
	*/
	PlaylistItem();

	/**
	*	Constructor
	*/
	PlaylistItem(string inId);

	/**
	*	Default destructor
	*/
	~PlaylistItem();

	// Get id
	string GetId();

	// Get played count
	int GetPlayedTimes();

	// Get inserted time
	string GetInsertedTime();

	// Set id
	void SetId(string inId);

	// Set played count
	void SetPlayedTimes(int inPlayedTimes);

	/**
	*	@brief	Set music id from keyboard.
	*	@pre	Item is initialized.
	*	@post	Music id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Increase music played count.
	*	@pre	Item is initialized.
	*	@post	mPlayedTimes increases by 1.
	*/
	void IncreasePlayedTimes();

	/**
	*	@brief	Compare two item by id.
	*	@pre	The two items should be initialized.
	*	@post	None.
	*	@param	that	target item for comparing.
	*	@return	True if ids are same, false otherwise.
	*/
	bool operator==(const PlaylistItem &that) const;
	bool operator<(const PlaylistItem &that) const;
	bool operator<=(const PlaylistItem &that) const;
	bool operator>(const PlaylistItem &that) const;
	bool operator>=(const PlaylistItem &that) const;

	/**
	*	@brief	Read a record from file.
	*/
	friend ifstream &operator>>(ifstream &ifs, PlaylistItem &item);

	/**
	*	@brief	Write a record into file.
	*/
	friend ofstream &operator<<(ofstream &ofs, const PlaylistItem &item);

private:
	string mId;			// Primary key of music
	int mPlayedTimes;		// How many times it has been played
	string mInsertedTime;		// When it was inserted to the playlist.

	const static int attrIndentSize = 25;

	/**
	*	Get current date & time for mInsertedTime
	*/
	static string GetCurrentTime();
};

#endif // _PLAYITEM_H
