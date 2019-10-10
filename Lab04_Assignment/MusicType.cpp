#include "MusicType.h"

MusicType::MusicType() {
	mId = "";
	mType = -1;
	mName = "";
	mMelodizer = "";
	mArtist = "";
	mGenre = "";
}

string MusicType::GetId() {
	return mId;
}

int MusicType::GetType() {
	return mType;
}

string MusicType::GetName() {
	return mName;
}

string MusicType::GetMelodizer() {
	return mMelodizer;
}

string MusicType::GetArtist() {
	return mArtist;
}

string MusicType::GetGenre() {
	return mGenre;
}

void MusicType::SetId(string inId) {
	mId = inId;
}

void MusicType::SetType(int inType) {
	mType = inType;
}

void MusicType::SetName(string inName) {
	mName = inName;
}

void MusicType::SetMelodizer(string inMelodizer) {
	mMelodizer = inMelodizer;
}

void MusicType::SetArtist(string inArtist) {
	mArtist = inArtist;
}

void MusicType::SetGenre(string inGenre) {
	mGenre = inGenre;
}

// Set records.
void MusicType::SetRecord(string inId, int inType, string inName,
	string inMelodizer, string inArtist, string inGenre) {
	SetId(inId);
	SetType(inType);
	SetName(inName);
	SetMelodizer(inMelodizer);
	SetArtist(inArtist);
	SetGenre(inGenre);
}

void MusicType::DisplayIdOnScreen() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "ID : " << mId << endl;
}

void MusicType::DisplayTypeOnScreen() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Type : " << mType << endl;
}

void MusicType::DisplayNameOnScreen() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Name : " << mName << endl;
}

void MusicType::DisplayMelodizerOnScreen() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Melodizer : " << mMelodizer << endl;
}

void MusicType::DisplayArtistOnScreen() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Artist : " << mArtist << endl;
}

void MusicType::DisplayGenreOnScreen() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Genre : " << mGenre << endl;
}

void MusicType::DisplayRecordOnScreen() {
	DisplayIdOnScreen();
	DisplayTypeOnScreen();
	DisplayNameOnScreen();
	DisplayMelodizerOnScreen();
	DisplayArtistOnScreen();
	DisplayGenreOnScreen();
}

// Set music id from keyboard, where id is string.
void MusicType::SetIdFromKB() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "ID (String) : ";
	getline(cin, mId);
}

// Set music type from keyboard, where type is int.
void MusicType::SetTypeFromKB() {
	while (true) {
		cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Type (Int) : ";
		cin >> mType;

		// Check if input is integer.
		int result = cin.fail();
		cin.clear();
		cin.ignore(NUM_LIMIT, '\n');

		if (result != 1) {
			// Success
			break;
		} else {
			cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Wrong input!\n";
		}
	}
}

// Set music name from keyboard, where name is string.
void MusicType::SetNameFromKB() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Name (String) : ";
	getline(cin, mName);
}

// Set music melodizer from keyboard, where melodizer is string.
void MusicType::SetMelodizerFromKB() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Melodizer (String) : ";
	getline(cin, mMelodizer);
}

// Set music artist from keyboard, where artist is string.
void MusicType::SetArtistFromKB() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Artist (String) : ";
	getline(cin, mArtist);
}

// Set music genre from keyboard, where genre is string.
void MusicType::SetGenreFromKB() {
	cout << setw(MUSICTYPE_ATTR_INDENT_SIZE) << "Genre (String) : ";
	getline(cin, mGenre);
}

// Set music record from keyboard.
// Id is automatically generated using music name and artist.
void MusicType::SetRecordFromKB() {
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
int MusicType::ReadDataFromFile(ifstream &fin) {
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
int MusicType::WriteDataToFile(ofstream &fout) {
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
bool MusicType::operator==(const MusicType &that) const {
	return this->mId.compare(that.mId) == 0;
}

// Compare two records
bool MusicType::operator!=(const MusicType &that) const {
	return !(*this == that);
}

// Compare two records
bool MusicType::operator>(const MusicType &that) const {
	return this->mId > that.mId;
}

// Compare two records
bool MusicType::operator>=(const MusicType &that) const {
	return this->mId >= that.mId;
}

// Compare two records
bool MusicType::operator<(const MusicType &that) const {
	return this->mId < that.mId;
}

// Compare two records
bool MusicType::operator<=(const MusicType &that) const {
	return this->mId <= that.mId;
}
