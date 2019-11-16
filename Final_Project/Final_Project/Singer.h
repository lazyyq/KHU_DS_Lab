#ifndef _SINGER_H_
#define _SINGER_H_

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <json/json.h>

#include "SortedDoublyLinkedList.h"
#include "SimpleItem.h"

using namespace std;

class Singer {
public:
	/**
	*	Constructors
	*/
	Singer();
	Singer(const string &inName, const int inAge,
		const char &inChar);

	/**
	*	Destructor
	*/
	~Singer();

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
	int AddSong(const SimpleItem &song);

	/**
	*	@brief	Remove song from list.
	*	@pre	Item is initialized. Song list is initialized.
	*	@post	Song is removed from song list.
	*	@return	1 on success, 0 on failure.
	*/
	int RemoveSong(const SimpleItem &song);

	/**
	*	@brief	곡 리스트 반환
	*	@pre	곡 리스트가 초기화돼있음.
	*	@return	곡 리스트
	*/
	const SortedDoublyLinkedList<SimpleItem> &GetSongList();

	/**
	*	@brief	Compare two items.
	*	@pre	Both items are initialized.
	*	@post	None.
	*	@return	Compare results of items.
	*/
	bool operator==(const Singer &that) const;
	bool operator!=(const Singer &that) const;
	bool operator<(const Singer &that) const;
	bool operator<=(const Singer &that) const;
	bool operator>(const Singer &that) const;
	bool operator>=(const Singer &that) const;

	/**
	*	@brief	Read record from JSON.
	*/
	friend Json::Value &operator>>(Json::Value &value, Singer &item);

	/**
	*	@brief	Write record to JSON.
	*/
	friend Json::Value &operator<<(Json::Value &root, const Singer &item);

private:
	string mName; // Singer name
	int mAge; // Singer age
	char mSex; // Singer sex
	SortedDoublyLinkedList<SimpleItem> mSongList; // Song list

	static const int attrIndentSize = 25; // 정보 표시할 때 들여쓰기 칸 수
};

#endif // _SINGER_H_