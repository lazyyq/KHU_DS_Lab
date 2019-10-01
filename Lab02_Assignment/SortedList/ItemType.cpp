#include "ItemType.h"

// Set music id from keyboard, where id is string.
void ItemType::SetIdFromKB()
{
	cout << setw(ATTR_INDENT_SIZE) << "ID (String) : ";
	getline(cin, mId);
}

// Set music type from keyboard, where type is int.
void ItemType::SetTypeFromKB()
{
	cout << setw(ATTR_INDENT_SIZE) << "Type (Int) : ";
	cin >> mType;
	cin.ignore();
}

// Set music name from keyboard, where name is string.
void ItemType::SetNameFromKB()
{
	cout << setw(ATTR_INDENT_SIZE) << "Name (String) : ";
	getline(cin, mName);
}

// Set music melodizer from keyboard, where melodizer is string.
void ItemType::SetMelodizerFromKB()
{
	cout << setw(ATTR_INDENT_SIZE) << "Melodizer (String) : ";
	getline(cin, mMelodizer);
}

// Set music artist from keyboard, where artist is string
void ItemType::SetArtistFromKB()
{
	cout << setw(ATTR_INDENT_SIZE) << "Artist (String) : ";
	getline(cin, mArtist);
}

// Set music genre from keyboard, where genre is int.
void ItemType::SetGenreFromKB()
{
	cout << setw(ATTR_INDENT_SIZE) << "Genre (Int) : ";
	cin >> mGenre;
	cin.ignore();
}

// Set music record from keyboard.
void ItemType::SetRecordFromKB()
{
	SetTypeFromKB();
	SetNameFromKB();
	SetMelodizerFromKB();
	SetArtistFromKB();
	SetGenreFromKB();

	if (this->mId.compare("") == 0) {
		mId = this->mName + " - " + this->mArtist;
	}
}

// Read a record from file.
int ItemType::ReadDataFromFile(ifstream& fin)
{
	// Temporary variable to hold string
	// which will later be converted to int
	string temp;

	getline(fin, mId);
	while (mId.length() == 0) {
		getline(fin, mId);
	}
	getline(fin, temp);
	mType = stoi(temp);
	getline(fin, mName);
	getline(fin, mMelodizer);
	getline(fin, mArtist);
	getline(fin, temp);
	mGenre = stoi(temp);

	return 1;
};

// Write a record into file.
int ItemType::WriteDataToFile(ofstream& fout)
{
	fout << endl << endl;
	fout << mId << endl;
	fout << mType << endl;
	fout << mName << endl;
	fout << mMelodizer << endl;
	fout << mArtist << endl;
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
