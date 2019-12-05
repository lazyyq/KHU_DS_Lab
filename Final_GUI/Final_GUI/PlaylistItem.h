#pragma once

#include <json/json.h>

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
	PlaylistItem(std::string inId);

	PlaylistItem(std::string inId, int inPlayedTimes,
		std::string inInsertedTime);

	/**
	*	Default destructor
	*/
	~PlaylistItem();

	// Get id
	std::string GetId() const;

	// Get played count
	int GetPlayedTimes() const;

	// Get inserted time
	std::string GetInsertedTime() const;

	// Set id
	void SetId(std::string inId);

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
	friend Json::Value &operator<<(Json::Value &value, const PlaylistItem &item);

private:
	std::string mId;			// Primary key of music
	int mPlayedTimes;		// How many times it has been played
	std::string mInsertedTime;		// Primary key. When it was inserted to the playlist.

	const static int attrIndentSize = 25; // ȭ�鿡 ǥ���� �� �鿩����

	/**
	*	Get current date & time for mInsertedTime
	*/
	static std::string GetCurrentTime();

	static std::string mLastInsertTime; // Last playlistitem inserted time.
	static int mLastInsertBit; // Extra bit that was appended to inserted time before.
};
