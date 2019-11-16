#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <json/json.h>

#include "SortedDoublyLinkedList.h"
#include "SimpleItem.h"

using namespace std;

class Genre {
public:
	/**
	*	Constructors
	*/
	Genre();
	Genre(const string &inName);

	/**
	*	Destructor
	*/
	~Genre();

	/**
	*	@brief	Get name of genre.
	*	@pre	Item is initialized. Name is set.
	*	@post	None.
	*	@return	Name of genre.
	*/
	string GetName();

	/**
	*	@brief	Set name of genre.
	*	@pre	Item is initialized.
	*	@post	Name is set.
	*	@param	inName	Name to set.
	*/
	void SetName(string &inName);

	/**
	*	@brief	Set name of genre from keyboard input.
	*	@pre	Item is initialized.
	*	@post	Name is set.
	*/
	void SetNameFromKB();

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
	bool operator==(const Genre &that) const;
	bool operator!=(const Genre &that) const;
	bool operator<(const Genre &that) const;
	bool operator<=(const Genre &that) const;
	bool operator>(const Genre &that) const;
	bool operator>=(const Genre &that) const;

	/**
	*	@brief	Read record from JSON.
	*/
	friend Json::Value &operator>>(Json::Value &value, Genre &item);

	/**
	*	@brief	Write record to JSON.
	*/
	friend Json::Value &operator<<(Json::Value &root, const Genre &item);

private:
	string mName; // Genre name
	SortedDoublyLinkedList<SimpleItem> mSongList; // Song list

	static const int attrIndentSize = 25; // 정보 표시할 때 들여쓰기 칸 수
};
