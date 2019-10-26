#ifndef _PLAYITEM_H
#define _PLAYITEM_H

#include <iostream>
#include <string>
#include <iomanip>

#define PLAYITEM_ATTR_INDENT_SIZE	25

using namespace std;

class PlayItem {
public:
	/**
	*	Default constructor
	*/
	PlayItem();

	/**
	*	Constructor
	*/
	PlayItem(string inId, int inNumPlay, int inInTime);

	/**
	*	Default destructor
	*/
	~PlayItem();

	// Get id
	string GetId();

	// Get played count
	int GetNumPlay();

	// Get inserted time
	int GetInTime();

	// Set id
	void SetId(string inId);

	// Set played count
	void SetNumPlay(int inNumPlay);

	// Set inserted time
	void SetInTime(int inInTime);

	/**
	*	@brief	Set music id from keyboard.
	*	@pre	Item is initialized.
	*	@post	Music id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Increase music played count.
	*	@pre	Item is initialized.
	*	@post	mNumPlay increases by 1.
	*/
	void IncreaseNumPlay();

	/**
	*	@brief	Compare two item by id.
	*	@pre	The two items should be initialized.
	*	@post	None.
	*	@param	that	target item for comparing.
	*	@return	True if ids are same, false otherwise.
	*/
	bool operator==(const PlayItem &that) const;

private:
	string mId;			// Primary key of music
	int mNumPlay;		// How many times it has been played
	int mInTime;		// When it was inserted to the playlist.
						// For this assignment only, just an index.

	const static int attrIndentSize = 25;
};

#endif // _PLAYITEM_H
