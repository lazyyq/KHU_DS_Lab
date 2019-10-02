#include "ItemType.h"

ItemType::ItemType()
{
	mId = "";
	mType = -1;
	mName = "";
	mMelodizer = "";
	mArtist = "";
	mGenre = -1;
}

string ItemType::GetId()
{
	return mId;
}

int ItemType::GetType()
{
	return mType;
}

string ItemType::GetName()
{
	return mName;
}

string ItemType::GetMelodizer()
{
	return mMelodizer;
}

string ItemType::GetArtist()
{
	return mArtist;
}

int ItemType::GetGenre()
{
	return mGenre;
}

void ItemType::SetId(string inId)
{
	mId = inId;
}

void ItemType::SetType(int inType)
{
	mType = inType;
}

void ItemType::SetName(string inName)
{
	mName = inName;
}

void ItemType::SetMelodizer(string inMelodizer)
{
	mMelodizer = inMelodizer;
}

void ItemType::SetArtist(string inArtist)
{
	mArtist = inArtist;
}

void ItemType::SetGenre(int inGenre)
{
	mGenre = inGenre;
}

void ItemType::SetRecord(string inId, int inType, string inName, string inMelodizer, string inArtist, int inGenre)
{
	SetId(inId);
	SetType(inType);
	SetName(inName);
	SetMelodizer(inMelodizer);
	SetArtist(inArtist);
	SetGenre(inGenre);
}

void ItemType::DisplayIdOnScreen()
{
	cout << setw(ATTR_INDENT_SIZE) << "ID : " << mId << endl;
}

void ItemType::DisplayTypeOnScreen()
{
	cout << setw(ATTR_INDENT_SIZE) << "Type : " << mType << endl;
}

void ItemType::DisplayNameOnScreen()
{
	cout << setw(ATTR_INDENT_SIZE) << "Name : " << mName << endl;
}

void ItemType::DisplayMelodizerOnScreen()
{
	cout << setw(ATTR_INDENT_SIZE) << "Melodizer : " << mMelodizer << endl;
}

void ItemType::DisplayArtistOnScreen()
{
	cout << setw(ATTR_INDENT_SIZE) << "Artist : " << mArtist << endl;
}

void ItemType::DisplayGenreOnScreen()
{
	cout << setw(ATTR_INDENT_SIZE) << "Genre : " << mGenre << endl;
}

void ItemType::DisplayRecordOnScreen()
{
	DisplayIdOnScreen();
	DisplayTypeOnScreen();
	DisplayNameOnScreen();
	DisplayMelodizerOnScreen();
	DisplayArtistOnScreen();
	DisplayGenreOnScreen();
}

// Set music id from keyboard, where id is string.
void ItemType::SetIdFromKB()
{
	cout << setw(ATTR_INDENT_SIZE) << "ID (String) : ";
	getline(cin, mId);
}

// Set music type from keyboard, where type is int.
void ItemType::SetTypeFromKB()
{
	while (true) {
		cout << setw(ATTR_INDENT_SIZE) << "Type (Int) : ";
		cin >> mType;

		int result = cin.fail();
		cin.clear();
		cin.ignore(NUM_LIMIT, '\n');

		if (result != 1) {
			// Success
			break;
		}
		else {
			cout << setw(ATTR_INDENT_SIZE) << "Wrong input!\n";
		}
	}
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
	while (true) {
		cout << setw(ATTR_INDENT_SIZE) << "Genre (Int) : ";
		cin >> mGenre;

		int result = cin.fail();
		cin.clear();
		cin.ignore(NUM_LIMIT, '\n');

		if (result != 1) {
			// Success
			break;
		}
		else {
			cout << setw(ATTR_INDENT_SIZE) << "Wrong input!\n";
		}
	}
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
