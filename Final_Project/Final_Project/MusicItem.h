#pragma once

#include <json/json.h>

#include "id3/ID3Tag.h"

/**
*	곡 정보가 담긴 클래스
*/
class MusicItem {
public:
	/**
	*	default constructor.
	*/
	MusicItem();

	MusicItem(MetadataInfo::ID3::ID3Tag &tag);

	/**
	*	destructor.
	*/
	~MusicItem() {}

	/**
	*	@brief	곡을 재생하는 함수. 실제 재생기능은 구현돼있지 않고 곡 정보를 표시하는 데서 그침.
	*/
	void Play();

	/**
	*	@brief	Get music id.
	*	@pre	Music id is set.
	*	@post	None.
	*	@return	Music id.
	*/
	string GetId() const;

	/**
	*	@brief	Get music name.
	*	@pre	Music name is set.
	*	@post	None.
	*	@return	Music name.
	*/
	string GetName() const;

	/**
	*	@brief	Get music melodizer.
	*	@pre	Music melodizer is set.
	*	@post	None.
	*	@return	Music melodizer.
	*/
	string GetMelodizer() const;

	/**
	*	@brief	Get music artist.
	*	@pre	Music artist is set.
	*	@post	None.
	*	@return	Music artist.
	*/
	string GetArtist() const;

	/**
	*	@brief	Get music genre.
	*	@pre	Music genre is set.
	*	@post	None.
	*	@return	Music genre.
	*/
	string GetGenre() const;

	/**
	*	@brief	Set music id.
	*	@pre	none.
	*	@post	Music id is set.
	*	@param	inId	Music id.
	*/
	void SetId(string inId);

	/**
	*	@brief	Set music name.
	*	@pre	none.
	*	@post	Music name is set.
	*	@param	inName	Music name.
	*/
	void SetName(string inName);

	/**
	*	@brief	Set music melodizer.
	*	@pre	none.
	*	@post	Music melodizer is set.
	*	@param	inMelodizer		Music melodizer.
	*/
	void SetMelodizer(string inMelodizer);

	/**
	*	@brief	Set music artist.
	*	@pre	none.
	*	@post	Music artist is set.
	*	@param	inArtist		Music artist.
	*/
	void SetArtist(string inArtist);

	/**
	*	@brief	Set music genre.
	*	@pre	none.
	*	@post	Music genre is set.
	*	@param	inGenre		Music genre.
	*/
	void SetGenre(string inGenre);

	/**
	*	@brief	Set music record.
	*	@pre	none.
	*	@post	Music record is set.
	*	@param	inId	Music id.
	*	@param	inName	Music name.
	*	@param	inMelodizer		Music melodizer.
	*	@param	inArtist	Music artist.
	*	@param	inGenre		Music genre.
	*/
	void SetRecord(string inId, string inName,
		string inMelodizer, string inArtist, string inGenre);

	/**
	*	@brief	Display music id on screen.
	*	@pre	Music id is set.
	*	@post	Music id is on screen.
	*/
	void DisplayIdOnScreen() const;

	/**
	*	@brief	Display music name on screen.
	*	@pre	Music name is set.
	*	@post	Music name is on screen.
	*/
	void DisplayNameOnScreen() const;

	/**
	*	@brief	Display music melodizer on screen.
	*	@pre	Music melodizer is set.
	*	@post	Music melodizer is on screen.
	*/
	void DisplayMelodizerOnScreen() const;

	/**
	*	@brief	Display music artist on screen.
	*	@pre	Music artist is set.
	*	@post	Music artist is on screen.
	*/
	void DisplayArtistOnScreen() const;

	/**
	*	@brief	Display music genre on screen.
	*	@pre	Music genre is set.
	*	@post	Music genre is on screen.
	*/
	void DisplayGenreOnScreen() const;

	/**
	*	@brief	Set music id from keyboard.
	*	@pre	none.
	*	@post	music id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Set music name from keyboard.
	*	@pre	none.
	*	@post	music name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Set music melodizer from keyboard.
	*	@pre	none.
	*	@post	music melodizer is set.
	*/
	void SetMelodizerFromKB();

	/**
	*	@brief	Set music artist from keyboard.
	*	@pre	none.
	*	@post	music artist is set.
	*/
	void SetArtistFromKB();

	/**
	*	@brief	Set music genre from keyboard.
	*	@pre	none.
	*	@post	music genre is set.
	*/
	void SetGenreFromKB();

	/**
	*	@brief	Read record from MP3 tag.
	*	@param	tag	MP3 tag to read data from.
	*/
	void SetRecordFromTag(MetadataInfo::ID3::ID3Tag &tag);

	/**
	*	@brief	곡 정보로부터 아이디 생성. 아이디는 `곡명 - 아티스트명` 형식.
	*	@post	곡 아이템이 초기화돼있음.
	*	@pre	곡 아이템의 아이디가 생성됨.
	*	@param	item	아이디 생성이 필요한 곡.
	*	@return	곡 아이디.
	*/
	static string GenerateMusicId(const MusicItem &item);

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None.
	*	@param	that	target item for comparing.
	*	@return	return true if the ids are same, false otherwise.
	*/
	bool operator==(const MusicItem &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None.
	*	@param	that	target item for comparing.
	*	@return	return true if the ids differ, false otherwise.
	*/
	bool operator!=(const MusicItem &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None..
	*	@param	that	target item for comparing.
	*	@return	return true if this > that, false otherwise.
	*/
	bool operator>(const MusicItem &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None..
	*	@param	that	target item for comparing.
	*	@return	return true if this >= that, false otherwise.
	*/
	bool operator>=(const MusicItem &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None..
	*	@param	that	target item for comparing.
	*	@return	return true if this < that, false otherwise.
	*/
	bool operator<(const MusicItem &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None..
	*	@param	that	target item for comparing.
	*	@return	return true if this <= that, false otherwise.
	*/
	bool operator<=(const MusicItem &that) const;

	/**
	*	@brief	Set music record from keyboard.
	*			Id is automatically generated using music name and artist.
	*	@pre	none.
	*	@post	music record is set.
	*/
	friend istream &operator>>(istream &is, MusicItem &item);

	/**
	*	@brief	Display a music record on screen.
	*	@pre	music record is set.
	*	@post	music record is on screen.
	*/
	friend ostream &operator<<(ostream &os, const MusicItem &item);

	/**
	*	@brief	Read record from JSON.
	*/
	friend Json::Value &operator>>(Json::Value &value, MusicItem &item);

	/**
	*	@brief	Write record to JSON.
	*/
	friend Json::Value &operator<<(Json::Value &value, const MusicItem &item);

protected:
	string mId;			///< Music ID.
	string mName;		///< Music name.
	string mMelodizer;	///< Music melodizer.
	string mArtist;		///< Music artist.
	string mGenre;		///< Music genre.

	const static int attrIndentSize = 25; // 곡 정보를 화면에 표시할 때 들여쓰기 칸 수
};
