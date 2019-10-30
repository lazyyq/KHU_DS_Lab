#pragma once

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class SimpleItem {
public:
	/**
	*	Constructor
	*/
	SimpleItem();

	SimpleItem(const string &inId, const string &inName,
		const string &inArtist);

	/**
	*	Destructor
	*/
	~SimpleItem();

	/**
	*	@brief	Get id of song.
	*	@pre	Item is initialized. Id is set.
	*	@post	None.
	*	@return	Id of song.
	*/
	string GetId() const;

	/**
	*	@brief	Get name of song.
	*	@pre	Item is initialized. Name is set.
	*	@post	None.
	*	@return	Name of song.
	*/
	string GetName() const;

	string GetArtist() const;

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

	void SetArtist(string &inArtist);

	///**
	//*	@brief	Set attributes of song from keyboard input.
	//*	@pre	Item is initialized.
	//*	@post	Atributes are set.
	//*/
	//void SetInfoFromKB();

	///**
	//*	@brief	Set Id of song from keyboard input.
	//*	@pre	Item is initialized.
	//*	@post	Id is set.
	//*/
	//void SetIdFromKB();

	///**
	//*	@brief	Set name of song from keyboard input.
	//*	@pre	Item is initialized.
	//*	@post	Name is set.
	//*/
	//void SetNameFromKB();

	/**
	*	@brief	Compare two items.
	*	@pre	Both items are initialized.
	*	@post	None.
	*	@return	Compare results of items.
	*/
	bool operator==(const SimpleItem &that) const;
	bool operator!=(const SimpleItem &that) const;
	bool operator<(const SimpleItem &that) const;
	bool operator<=(const SimpleItem &that) const;
	bool operator>(const SimpleItem &that) const;
	bool operator>=(const SimpleItem &that) const;

private:
	string mId; // Music id
	string mName; // Music name
	string mArtist; // Artist name

	static const int attrIndentSize = 25;
};
