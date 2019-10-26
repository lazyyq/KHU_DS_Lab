
#ifndef _MUSICTYPE_H_
#define _MUSICTYPE_H_

#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

/**
*	item information class.
*/
class MusicType {
public:
	/**
	*	default constructor.
	*/
	MusicType();

	/**
	*	destructor.
	*/
	~MusicType() {}

	/**
	*	@brief	Get music id.
	*	@pre	Music id is set.
	*	@post	None.
	*	@return	Music id.
	*/
	string GetId();

	/**
	*	@brief	Get music type.
	*	@pre	Music type is set.
	*	@post	None.
	*	@return	Music type.
	*/
	int GetType();

	/**
	*	@brief	Get music name.
	*	@pre	Music name is set.
	*	@post	None.
	*	@return	Music name.
	*/
	string GetName();

	/**
	*	@brief	Get music melodizer.
	*	@pre	Music melodizer is set.
	*	@post	None.
	*	@return	Music melodizer.
	*/
	string GetMelodizer();

	/**
	*	@brief	Get music artist.
	*	@pre	Music artist is set.
	*	@post	None.
	*	@return	Music artist.
	*/
	string GetArtist();

	/**
	*	@brief	Get music genre.
	*	@pre	Music genre is set.
	*	@post	None.
	*	@return	Music genre.
	*/
	string GetGenre();

	/**
	*	@brief	Set music id.
	*	@pre	none.
	*	@post	Music id is set.
	*	@param	inId	Music id.
	*/
	void SetId(string inId);

	/**
	*	@brief	Set music type.
	*	@pre	none.
	*	@post	Music type is set.
	*	@param	inType	Music type.
	*/
	void SetType(int inType);

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
	*	@param	inType	Music type.
	*	@param	inName	Music name.
	*	@param	inMelodizer		Music melodizer.
	*	@param	inArtist	Music artist.
	*	@param	inGenre		Music genre.
	*/
	void SetRecord(string inId, int inType, string inName,
		string inMelodizer, string inArtist, string inGenre);

	/**
	*	@brief	Display music id on screen.
	*	@pre	Music id is set.
	*	@post	Music id is on screen.
	*/
	void DisplayIdOnScreen();

	/**
	*	@brief	Display music type on screen.
	*	@pre	Music type is set.
	*	@post	Music type is on screen.
	*/
	void DisplayTypeOnScreen();

	/**
	*	@brief	Display music name on screen.
	*	@pre	Music name is set.
	*	@post	Music name is on screen.
	*/
	void DisplayNameOnScreen();

	/**
	*	@brief	Display music melodizer on screen.
	*	@pre	Music melodizer is set.
	*	@post	Music melodizer is on screen.
	*/
	void DisplayMelodizerOnScreen();

	/**
	*	@brief	Display music artist on screen.
	*	@pre	Music artist is set.
	*	@post	Music artist is on screen.
	*/
	void DisplayArtistOnScreen();

	/**
	*	@brief	Display music genre on screen.
	*	@pre	Music genre is set.
	*	@post	Music genre is on screen.
	*/
	void DisplayGenreOnScreen();

	/**
	*	@brief	Display a music record on screen.
	*	@pre	music record is set.
	*	@post	music record is on screen.
	*/
	void DisplayRecordOnScreen();

	/**
	*	@brief	Set music id from keyboard.
	*	@pre	none.
	*	@post	music id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Set music type from keyboard.
	*	@pre	none.
	*	@post	music type is set.
	*/
	void SetTypeFromKB();

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
	*	@brief	Set music record from keyboard.
	*			Id is automatically generated using music name and artist.
	*	@pre	none.
	*	@post	music record is set.
	*/
	void SetRecordFromKB();

	string GenerateMusicId();

	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	music record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile(ifstream &fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new music record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile(ofstream &fout);

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None.
	*	@param	that	target item for comparing.
	*	@return	return true if the ids are same, false otherwise.
	*/
	bool operator==(const MusicType &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None.
	*	@param	that	target item for comparing.
	*	@return	return true if the ids differ, false otherwise.
	*/
	bool operator!=(const MusicType &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None..
	*	@param	that	target item for comparing.
	*	@return	return true if this > that, false otherwise.
	*/
	bool operator>(const MusicType &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None..
	*	@param	that	target item for comparing.
	*	@return	return true if this >= that, false otherwise.
	*/
	bool operator>=(const MusicType &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None..
	*	@param	that	target item for comparing.
	*	@return	return true if this < that, false otherwise.
	*/
	bool operator<(const MusicType &that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	None..
	*	@param	that	target item for comparing.
	*	@return	return true if this <= that, false otherwise.
	*/
	bool operator<=(const MusicType &that) const;

protected:
	string mId;			///< Music ID.
	int mType;			///< Music type.
	string mName;		///< Music name.
	string mMelodizer;	///< Music melodizer.
	string mArtist;		///< Music artist.
	string mGenre;		///< Music genre.

	const static int attrIndentSize = 25;
};

#endif	// _MUSICTYPE_H_
