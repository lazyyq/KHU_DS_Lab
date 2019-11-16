#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <json/json.h>

using namespace std;

/**
*	������ �� ����Ʈ�� �帣�� �� ����Ʈ�� �����ϱ� ����,
*	�����͸���Ʈ �˻��� ���̵� ���� �������� �ּ����� ������ ����ִ� �� �������� Ŭ����.
*/
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

	/**
	*	@brief	Get artist of song.
	*	@pre	Item is initialized. Artist is set.
	*	@post	None.
	*	@return	Artist of song.
	*/
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

	/**
	*	@brief	Set artist of song.
	*	@pre	Item is initialized.
	*	@post	Artist is set.
	*	@param	inArtist	Artist to set.
	*/
	void SetArtist(string &inArtist);

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

	/**
	*	@brief	Read record from JSON.
	*/
	friend Json::Value &operator>>(Json::Value &value, SimpleItem &item);

	/**
	*	@brief	Write record to JSON.
	*/
	friend Json::Value &operator<<(Json::Value &root, const SimpleItem &item);

private:
	string mId; // Music id
	string mName; // Music name
	string mArtist; // Artist name

	static const int attrIndentSize = 25; // ���� ǥ���Ҷ� �鿩���� ĭ ��
};
