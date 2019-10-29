#ifndef _PLAYITEM_H
#define _PLAYITEM_H

#include <iostream>
#include <string>
#include <iomanip>

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
	PlaylistItem(string inId, int inPlayedTimes, int inInsertedTime);

	/**
	*	Default destructor
	*/
	~PlaylistItem();

	// Get id
	string GetId();

	// Get played count
	int GetPlayedTimes();

	// Get inserted time
	int GetInsertedTime();

	// Set id
	void SetId(string inId);

	// Set played count
	void SetPlayedTimes(int inPlayedTimes);

	// Set inserted time
	void SetInsertedTime(int inInsertedTime);

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

private:
	string mId;			// Primary key of music
	int mPlayedTimes;		// How many times it has been played
	int mInsertedTime;		// When it was inserted to the playlist.
						// For this assignment only, just an index.

	const static int attrIndentSize = 25;
};

#endif // _PLAYITEM_H
