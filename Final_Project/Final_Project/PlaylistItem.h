#ifndef _PLAYITEM_H
#define _PLAYITEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <json/json.h>

#define PLAYITEM_ATTR_INDENT_SIZE	25

using namespace std;

/**
*	�÷��̸���Ʈ�� ����� �������� Ŭ����.
*	�� ���̵�, ��� Ƚ��, �÷��̸���Ʈ ���� �ð� ���� ������ ����.
*/
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

	PlaylistItem(string inId, int inPlayedTimes,
		string inInsertedTime);

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
	*	@brief	Read record from JSON.
	*/
	friend Json::Value &operator>>(Json::Value &value, PlaylistItem &item);

	/**
	*	@brief	Write record to JSON.
	*/
	friend Json::Value &operator<<(Json::Value &root, const PlaylistItem &item);

private:
	string mId;			// Primary key of music
	int mPlayedTimes;		// How many times it has been played
	string mInsertedTime;		// Primary key. When it was inserted to the playlist.

	const static int attrIndentSize = 25; // ȭ�鿡 ǥ���� �� �鿩����

	/**
	*	Get current date & time for mInsertedTime
	*/
	static string GetCurrentTime();
};

#endif // _PLAYITEM_H
