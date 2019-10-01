#include "ItemType.h"

// Set music id from keyboard.
void ItemType::SetIdFromKB()
{
	cout << "\tID : ";
	cin >> mId;
}

// Set music type from keyboard.
void ItemType::SetTypeFromKB()
{
	cout << "\tType : ";
	cin >> mType;
}

// Set music name from keyboard.
void ItemType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> mName;
}

// Set music melodizer from keyboard.
void ItemType::SetMelodizerFromKB()
{
	cout << "\tMelodizer : ";
	cin >> mMelodizer;
}

// Set music artist from keyboard.
void ItemType::SetArtistFromKB()
{
	cout << "\tArtist : ";
	cin >> mArtist;
}

// Set music genre from keyboard.
void ItemType::SetGenreFromKB()
{
	cout << "\tGenre : ";
	cin >> mGenre;
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
	fin >> mId;
	fin >> mType;
	fin >> mName;
	fin >> mMelodizer;
	fin >> mArtist;
	fin >> mGenre;

	return 1;
};

// Write a record into file.
int ItemType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << mId << " ";
	fout << mType << " ";
	fout << mName << " ";
	fout << mMelodizer << " ";
	fout << mArtist << " ";
	fout << mGenre;

	return 1;
}

// Compare two records
bool ItemType::operator==(const ItemType& that) const {
	return this->mId.compare(that.mId) == 0;
}

// Compare two records
bool ItemType::operator!=(const ItemType& that) const {
	return !(*this == that);
}

bool ItemType::operator>(const ItemType& that) const
{
	return this->mId > that.mId;
}

bool ItemType::operator>=(const ItemType& that) const
{
	return this->mId >= that.mId;
}

bool ItemType::operator<(const ItemType& that) const
{
	return this->mId < that.mId;
}

bool ItemType::operator<=(const ItemType& that) const
{
	return this->mId <= that.mId;
}
