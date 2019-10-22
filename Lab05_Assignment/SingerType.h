#ifndef _SINGERTYPE_H_
#define _SINGERTYPE_H_

#include <iostream>
#include <string>
#include <iomanip>
#include "UnsortedLinkedList.h"
#include "LinkedList.h"

#define SINGERTYPE_ATTR_INDENT_SIZE	25
using namespace std;

class SongItem {
public:
	/**
	*	Constructor
	*/
	SongItem();
	SongItem(const string &inId, const string &inName);

	/**
	*	Destructor
	*/
	~SongItem();

	/**
	*	@brief	Get id of song.
	*	@pre	Item is initialized. Id is set.
	*	@post	None.
	*	@return	Id of song.
	*/
	string GetId();

	/**
	*	@brief	Get name of song.
	*	@pre	Item is initialized. Name is set.
	*	@post	None.
	*	@return	Name of song.
	*/
	string GetName();

	/**
	*	@brief	Set id of song.
	*	@pre	Item is initialized.
	*	@post	Id is set.
	*	@param	inId	Id to set.
	*/
	void SetId(string &inId);

	/**
	*	@brief	Set name of song.
	*	@pre	Item is initialized.
	*	@post	Name is set.
	*	@param	inName	Name to set.
	*/
	void SetName(string &inName);

	/**
	*	@brief	Set attributes of song from keyboard input.
	*	@pre	Item is initialized.
	*	@post	Atributes are set.
	*/
	void SetInfoFromKB();

	/**
	*	@brief	Set Id of song from keyboard input.
	*	@pre	Item is initialized.
	*	@post	Id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Set name of song from keyboard input.
	*	@pre	Item is initialized.
	*	@post	Name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Compare two items.
	*	@pre	Both items are initialized.
	*	@post	None.
	*	@return	Compare results of items.
	*/
	bool operator==(const SongItem &that) const;
	bool operator!=(const SongItem &that) const;
	bool operator<(const SongItem &that) const;
	bool operator<=(const SongItem &that) const;
	bool operator>(const SongItem &that) const;
	bool operator>=(const SongItem &that) const;

private:
	string mId; // Song id
	string mName; // Song name
};

class SingerType {
public:
	/**
	*	Constructors
	*/
	SingerType();
	SingerType(const string &inName, const int inAge,
		const char &inChar);

	/**
	*	Destructor
	*/
	~SingerType();

	/**
	*	@brief	Get name of singer.
	*	@pre	Item is initialized. Name is set.
	*	@post	None.
	*	@return	Name of singer.
	*/
	string GetName();

	/**
	*	@brief	Get age of singer.
	*	@pre	Item is initialized. Age is set.
	*	@post	None.
	*	@return	Age of singer.
	*/
	int GetAge();

	/**
	*	@brief	Get sex of singer.
	*	@pre	Item is initialized. Sex is set.
	*	@post	None.
	*	@return	Sex of singer.
	*/
	char GetSex();

	/**
	*	@brief	Get song list of singer.
	*	@pre	Item is initialized. Song list is set.
	*	@post	None.
	*	@return	Song list of singer.
	*/
	UnsortedLinkedList<SongItem> GetSongList();

	/**
	*	@brief	Set name of singer.
	*	@pre	Item is initialized.
	*	@post	Name is set.
	*	@param	inName	Name to set.
	*/
	void SetName(string &inName);

	/**
	*	@brief	Set age of singer.
	*	@pre	Item is initialized.
	*	@post	Age is set.
	*	@param	inAge	Age to set.
	*/
	void SetAge(int inAge);

	/**
	*	@brief	Set sex of singer.
	*	@pre	Item is initialized.
	*	@post	Sex is set.
	*	@param	inSex	Sex to set.
	*/
	void SetSex(char inSex);

	/**
	*	@brief	Set attributes of singer from keyboard input.
	*	@pre	Item is initialized.
	*	@post	Atributes are set.
	*/
	void SetInfoFromKB();

	/**
	*	@brief	Set name of singer from keyboard input.
	*	@pre	Item is initialized.
	*	@post	Name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Set age of singer from keyboard input.
	*	@pre	Item is initialized.
	*	@post	Age is set.
	*/
	void SetAgeFromKB();

	/**
	*	@brief	Set sex of singer from keyboard input.
	*	@pre	Item is initialized.
	*	@post	Sex is set.
	*/
	void SetSexFromKB();

	/**
	*	@brief	Add song to song list.
	*	@pre	Item is initialized. Song list is initialized.
	*	@post	Song is added to song list.
	*	@return	1 on success, 0 on failure.
	*/
	int AddSong(const SongItem &song);

	/**
	*	@brief	Remove song from list.
	*	@pre	Item is initialized. Song list is initialized.
	*	@post	Song is removed from song list.
	*	@return	1 on success, 0 on failure.
	*/
	int RemoveSong(const SongItem &song);

	/**
	*	@brief	Compare two items.
	*	@pre	Both items are initialized.
	*	@post	None.
	*	@return	Compare results of items.
	*/
	bool operator==(const SingerType &that) const;
	bool operator!=(const SingerType &that) const;
	bool operator<(const SingerType &that) const;
	bool operator<=(const SingerType &that) const;
	bool operator>(const SingerType &that) const;
	bool operator>=(const SingerType &that) const;

private:
	string mName; // Singer name
	int mAge; // Singer age
	char mSex; // Singer sex
	UnsortedLinkedList<SongItem> mSongList; // Song list
};

#endif // _SINGERTYPE_H_