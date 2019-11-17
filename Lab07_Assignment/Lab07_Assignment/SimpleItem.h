#pragma once

#include <json/json.h>

/**
*	가수의 곡 리스트나 장르의 곡 리스트에 저장하기 위한,
*	마스터리스트 검색용 아이디를 담을 목적으로 최소한의 정보만 담고있는 곡 간이정보 클래스.
*/
class SimpleItem {
public:
	/**
	*	Constructor
	*/
	SimpleItem();

	SimpleItem(const std::string &inId, const std::string &inName,
		const std::string &inArtist);

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
	std::string GetId() const;

	/**
	*	@brief	Get name of song.
	*	@pre	Item is initialized. Name is set.
	*	@post	None.
	*	@return	Name of song.
	*/
	std::string GetName() const;

	/**
	*	@brief	Get artist of song.
	*	@pre	Item is initialized. Artist is set.
	*	@post	None.
	*	@return	Artist of song.
	*/
	std::string GetArtist() const;

	/**
	*	@brief	Set id of song.
	*	@pre	Item is initialized.
	*	@post	Id is set.
	*	@param	inId	Id to set.
	*/
	void SetId(std::string &inId);

	/**
	*	@brief	Set name of song.
	*	@pre	Item is initialized.
	*	@post	Name is set.
	*	@param	inName	Name to set.
	*/
	void SetName(std::string &inName);

	/**
	*	@brief	Set artist of song.
	*	@pre	Item is initialized.
	*	@post	Artist is set.
	*	@param	inArtist	Artist to set.
	*/
	void SetArtist(std::string &inArtist);

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
	std::string mId; // Music id
	std::string mName; // Music name
	std::string mArtist; // Artist name

	static const int attrIndentSize = 25; // 정보 표시할때 들여쓰기 칸 수
};
