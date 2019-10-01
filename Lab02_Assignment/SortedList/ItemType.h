
#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/**
*	Relation between two items.
*/
enum RelationType { LESS, GREATER, EQUAL };


/**
*	item information class.
*/
class ItemType
{
public:
	/**
	*	default constructor.
	*/
	ItemType()
	{
		m_Id = "";
		m_Type = -1;
		m_Name = "";
		m_Melodizer = "";
		m_Artist = "";
		m_Genre = -1;
	}

	/**
	*	destructor.
	*/
	~ItemType() {}

	/**
	*	@brief	Get music id.
	*	@pre	Music id is set.
	*	@post	None.
	*	@return	Music id.
	*/
	string GetId()
	{
		return m_Id;
	}

	/**
	*	@brief	Get music type.
	*	@pre	Music type is set.
	*	@post	None.
	*	@return	Music type.
	*/
	int GetType()
	{
		return m_Type;
	}

	/**
	*	@brief	Get music name.
	*	@pre	Music name is set.
	*	@post	None.
	*	@return	Music name.
	*/
	string GetName()
	{
		return m_Name;
	}

	/**
	*	@brief	Get music melodizer.
	*	@pre	Music melodizer is set.
	*	@post	None.
	*	@return	Music melodizer.
	*/
	string GetMelodizer()
	{
		return m_Melodizer;
	}

	/**
	*	@brief	Get music artist.
	*	@pre	Music artist is set.
	*	@post	None.
	*	@return	Music artist.
	*/
	string GetArtist()
	{
		return m_Artist;
	}

	/**
	*	@brief	Get music genre.
	*	@pre	Music genre is set.
	*	@post	None.
	*	@return	Music genre.
	*/
	int GetGenre()
	{
		return m_Genre;
	}

	/**
	*	@brief	Set music id.
	*	@pre	none.
	*	@post	Music id is set.
	*	@param	inId	Music id.
	*/
	void SetId(string inId)
	{
		m_Id = inId;
	}

	/**
	*	@brief	Set music type.
	*	@pre	none.
	*	@post	Music type is set.
	*	@param	inType	Music type.
	*/
	void SetType(int inType)
	{
		m_Type = inType;
	}

	/**
	*	@brief	Set music name.
	*	@pre	none.
	*	@post	Music name is set.
	*	@param	inName	Music name.
	*/
	void SetName(string inName)
	{
		m_Name = inName;
	}

	/**
	*	@brief	Set music melodizer.
	*	@pre	none.
	*	@post	Music melodizer is set.
	*	@param	inMelodizer		Music melodizer.
	*/
	void SetMelodizer(string inMelodizer)
	{
		m_Melodizer = inMelodizer;
	}

	/**
	*	@brief	Set music artist.
	*	@pre	none.
	*	@post	Music artist is set.
	*	@param	inArtist		Music artist.
	*/
	void SetArtist(string inArtist)
	{
		m_Artist = inArtist;
	}

	/**
	*	@brief	Set music genre.
	*	@pre	none.
	*	@post	Music genre is set.
	*	@param	inGenre		Music genre.
	*/
	void SetGenre(int inGenre)
	{
		m_Genre = inGenre;
	}

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
		string inMelodizer, string inArtist, int inGenre)
	{
		SetId(inId);
		SetType(inType);
		SetName(inName);
		SetMelodizer(inMelodizer);
		SetArtist(inArtist);
		SetGenre(inGenre);
	}

	/**
	*	@brief	Display music id on screen.
	*	@pre	Music id is set.
	*	@post	Music id is on screen.
	*/
	void DisplayIdOnScreen()
	{
		cout << "\tID   : " << m_Id << endl;
	};

	/**
	*	@brief	Display music type on screen.
	*	@pre	Music type is set.
	*	@post	Music type is on screen.
	*/
	void DisplayTypeOnScreen()
	{
		cout << "\tType   : " << m_Type << endl;
	};

	/**
	*	@brief	Display music name on screen.
	*	@pre	Music name is set.
	*	@post	Music name is on screen.
	*/
	void DisplayNameOnScreen()
	{
		cout << "\tName   : " << m_Name << endl;
	};

	/**
	*	@brief	Display music melodizer on screen.
	*	@pre	Music melodizer is set.
	*	@post	Music melodizer is on screen.
	*/
	void DisplayMelodizerOnScreen()
	{
		cout << "\tMelodizer   : " << m_Melodizer << endl;
	};

	/**
	*	@brief	Display music artist on screen.
	*	@pre	Music artist is set.
	*	@post	Music artist is on screen.
	*/
	void DisplayArtistOnScreen()
	{
		cout << "\tArtist   : " << m_Artist << endl;
	};

	/**
	*	@brief	Display music genre on screen.
	*	@pre	Music genre is set.
	*	@post	Music genre is on screen.
	*/
	void DisplayGenreOnScreen()
	{
		cout << "\tGenre   : " << m_Genre << endl;
	};

	/**
	*	@brief	Display a music record on screen.
	*	@pre	music record is set.
	*	@post	music record is on screen.
	*/
	void DisplayRecordOnScreen()
	{
		DisplayIdOnScreen();
		DisplayTypeOnScreen();
		DisplayNameOnScreen();
		DisplayMelodizerOnScreen();
		DisplayArtistOnScreen();
		DisplayGenreOnScreen();
	};

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
	*	@pre	none.
	*	@post	music record is set.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	music record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new music record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile(ofstream& fout);

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	the target file is included the new item record.
	*	@param	that	target item for comparing.
	*	@return	return true if the ids are same, false otherwise.
	*/
	bool operator==(const ItemType& that) const;

	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	the target file is included the new item record.
	*	@param	that	target item for comparing.
	*	@return	return true if the ids differ, false otherwise.
	*/
	bool operator!=(const ItemType& that) const;

protected:
	string m_Id;		///< Music ID.
	int m_Type;			///< Music type.
	string m_Name;		///< Music name.
	string m_Melodizer;	///< Music melodizer.
	string m_Artist;	///< Music artist.
	int m_Genre;		///< Music genre.
};

#endif	// _ITEMTYPE_H
