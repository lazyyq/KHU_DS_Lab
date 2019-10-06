#include "ItemType.h"

ItemType::ItemType() {
	mId = "";
	mType = -1;
	mName = "";
	mMelodizer = "";
	mArtist = "";
	mGenre = "";
}

string ItemType::GetId() {
	return mId;
}

int ItemType::GetType() {
	return mType;
}

string ItemType::GetName() {
	return mName;
}

string ItemType::GetMelodizer() {
	return mMelodizer;
}

string ItemType::GetArtist() {
	return mArtist;
}

string ItemType::GetGenre() {
	return mGenre;
}

void ItemType::SetId(string inId) {
	mId = inId;
}

void ItemType::SetType(int inType) {
	mType = inType;
}

void ItemType::SetName(string inName) {
	mName = inName;
}

void ItemType::SetMelodizer(string inMelodizer) {
	mMelodizer = inMelodizer;
}

void ItemType::SetArtist(string inArtist) {
	mArtist = inArtist;
}

void ItemType::SetGenre(string inGenre) {
	mGenre = inGenre;
}

// Set records.
void ItemType::SetRecord(string inId, int inType, string inName,
	string inMelodizer, string inArtist, string inGenre) {
	SetId(inId);
	SetType(inType);
	SetName(inName);
	SetMelodizer(inMelodizer);
	SetArtist(inArtist);
	SetGenre(inGenre);
}

void ItemType::DisplayIdOnScreen() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "ID : " << mId << endl;
}

void ItemType::DisplayTypeOnScreen() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Type : " << mType << endl;
}

void ItemType::DisplayNameOnScreen() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Name : " << mName << endl;
}

void ItemType::DisplayMelodizerOnScreen() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Melodizer : " << mMelodizer << endl;
}

void ItemType::DisplayArtistOnScreen() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Artist : " << mArtist << endl;
}

void ItemType::DisplayGenreOnScreen() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Genre : " << mGenre << endl;
}

void ItemType::DisplayRecordOnScreen() {
	DisplayIdOnScreen();
	DisplayTypeOnScreen();
	DisplayNameOnScreen();
	DisplayMelodizerOnScreen();
	DisplayArtistOnScreen();
	DisplayGenreOnScreen();
}

// Set music id from keyboard, where id is string.
void ItemType::SetIdFromKB() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "ID (String) : ";
	getline(cin, mId);
}

// Set music type from keyboard, where type is int.
void ItemType::SetTypeFromKB() {
	while (true) {
		cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Type (Int) : ";
		cin >> mType;

		// Check if input is integer.
		int result = cin.fail();
		cin.clear();
		cin.ignore(NUM_LIMIT, '\n');

		if (result != 1) {
			// Success
			break;
		}
		else {
			cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Wrong input!\n";
		}
	}
}

// Set music name from keyboard, where name is string.
void ItemType::SetNameFromKB() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Name (String) : ";
	getline(cin, mName);
}

// Set music melodizer from keyboard, where melodizer is string.
void ItemType::SetMelodizerFromKB() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Melodizer (String) : ";
	getline(cin, mMelodizer);
}

// Set music artist from keyboard, where artist is string.
void ItemType::SetArtistFromKB() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Artist (String) : ";
	getline(cin, mArtist);
}

// Set music genre from keyboard, where genre is string.
void ItemType::SetGenreFromKB() {
	cout << setw(ITEMTYPE_ATTR_INDENT_SIZE) << "Genre (String) : ";
	getline(cin, mGenre);
}

// Set music record from keyboard.
// Id is automatically generated using music name and artist.
void ItemType::SetRecordFromKB() {
	SetTypeFromKB();
	SetNameFromKB();
	SetMelodizerFromKB();
	SetArtistFromKB();
	SetGenreFromKB();

	// If music id does not already exist, automatically generate one.
	// Format is '`Music name` - `Artist`'
	if (this->mId.compare("") == 0) {
		mId = this->mName + " - " + this->mArtist;
	}
}

// Read a record from file.
// Store each line into respective variables.
int ItemType::ReadDataFromFile(ifstream& fin) {
	// Temporary variable to hold string
	// which will later be converted to int
	string temp;

	getline(fin, mId);
	// Skip empty lines.
	while (mId.length() == 0) {
		getline(fin, mId);
	}
	getline(fin, temp);
	mType = stoi(temp);
	getline(fin, mName);
	getline(fin, mMelodizer);
	getline(fin, mArtist);
	getline(fin, mGenre);

	return 1;
};

// Write a record into file.
int ItemType::WriteDataToFile(ofstream& fout) {
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

// Compare two records
bool ItemType::operator>(const ItemType& that) const {
	return this->mId > that.mId;
}

// Compare two records
bool ItemType::operator>=(const ItemType& that) const {
	return this->mId >= that.mId;
}

// Compare two records
bool ItemType::operator<(const ItemType& that) const {
	return this->mId < that.mId;
}

// Compare two records
bool ItemType::operator<=(const ItemType& that) const {
	return this->mId <= that.mId;
}
