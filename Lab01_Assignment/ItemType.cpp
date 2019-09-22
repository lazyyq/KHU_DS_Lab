#include "ItemType.h"


// Set music id from keyboard.
void ItemType::SetIdFromKB()
{
	cout << "\tID : ";
	cin >> m_Id;
}


// Set music type from keyboard.
void ItemType::SetTypeFromKB()
{
	cout << "\tType : ";
	cin >> m_Type;
}


// Set music name from keyboard.
void ItemType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> m_Name;
}


// Set music melodizer from keyboard.
void ItemType::SetMelodizerFromKB()
{
	cout << "\tMelodizer : ";
	cin >> m_Melodizer;
}


// Set music artist from keyboard.
void ItemType::SetArtistFromKB()
{
	cout << "\tArtist : ";
	cin >> m_Artist;
}


// Set music genre from keyboard.
void ItemType::SetGenreFromKB()
{
	cout << "\tGenre : ";
	cin >> m_Genre;
}


// Set music record from keyboard.
void ItemType::SetRecordFromKB()
{
	SetIdFromKB();
	SetTypeFromKB();
	SetNameFromKB();
	SetMelodizerFromKB();
	SetArtistFromKB();
	SetGenreFromKB();
}


// Read a record from file.
int ItemType::ReadDataFromFile(ifstream& fin)
{
	fin >> m_Id;
	fin >> m_Type;
	fin >> m_Name;
	fin >> m_Melodizer;
	fin >> m_Artist;
	fin >> m_Genre;

	return 1;
};


// Write a record into file.
int ItemType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << m_Id << " ";
	fout << m_Type << -1;
	fout << m_Name << " ";
	fout << m_Melodizer << " ";
	fout << m_Artist << " ";
	fout << m_Genre << -1;

	return 1;
}


// Compare two records
bool ItemType::operator==(const ItemType& that) const {
	return this->m_Id.compare(that.m_Id) == 0;
}


// Compare two records
bool ItemType::operator!=(const ItemType& that) const {
	return !(*this == that);
}