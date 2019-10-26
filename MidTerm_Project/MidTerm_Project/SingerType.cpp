#include "SingerType.h"

// Constructors
SongType::SongType() {
	mId = "";
	mName = "";
}

SongType::SongType(const string &inId, const string &inName) {
	mId = inId;
	mName = inName;
}

// Destructor
SongType::~SongType() {}

// Get id
string SongType::GetId() {
	return mId;
}

// Get name
string SongType::GetName() {
	return mName;
}

// Set id
void SongType::SetId(string &inId) {
	mId = inId;
}

// Set name
void SongType::SetName(string &inName) {
	mName = inName;
}

// Set info from keyboard input
void SongType::SetInfoFromKB() {
	SetIdFromKB();
	SetNameFromKB();
}

// Set id from keyboard input
void SongType::SetIdFromKB() {
	cout << setw(attrIndentSize) << "Song id (String) : ";
	getline(cin, mId);
}

// Set name from keyboard input
void SongType::SetNameFromKB() {
	cout << setw(attrIndentSize) << "Song name (String) : ";
	getline(cin, mName);
}

// Compare operators
bool SongType::operator==(const SongType &that) const {
	return this->mId.compare(that.mId) == 0;
}

bool SongType::operator!=(const SongType &that) const {
	return !(*this == that);
}

bool SongType::operator<(const SongType &that) const {
	return this->mId.compare(that.mId) < 0;
}

bool SongType::operator<=(const SongType &that) const {
	return this->mId.compare(that.mId) <= 0;
}

bool SongType::operator>(const SongType &that) const {
	return this->mId.compare(that.mId) > 0;
}

bool SongType::operator>=(const SongType &that) const {
	return this->mId.compare(that.mId) >= 0;
}

// Constructors
SingerType::SingerType() {
	mName = "";
	mAge = -1;
	mSex = NULL;
}

SingerType::SingerType(const string &inName,
	const int inAge, const char &inSex) {
	mName = inName;
	mAge = inAge;
	mSex = inSex;
}

// Destructor
SingerType::~SingerType() {
	// Clean linked list
	mSongList.MakeEmpty();
}

// Get name
string SingerType::GetName() {
	return mName;
}

// Get age
int SingerType::GetAge() {
	return mAge;
}

// Get sex
char SingerType::GetSex() {
	return mSex;
}

// Get song list
UnsortedLinkedList<SongType> SingerType::GetSongList() {
	return mSongList;
}

// Set name
void SingerType::SetName(string &inName) {
	mName = inName;
}

// Set age
void SingerType::SetAge(int inAge) {
	mAge = inAge;
}

// Set sex
void SingerType::SetSex(char inSex) {
	mSex = inSex;
}

// Set info from keyboard input
void SingerType::SetInfoFromKB() {
	SetNameFromKB();
	SetAgeFromKB();
	SetSexFromKB();
}

// Set name from keyboard input
void SingerType::SetNameFromKB() {
	cout << setw(attrIndentSize) << "Singer name (String) : ";
	getline(cin, mName);
}

// Set age from keyboard input
void SingerType::SetAgeFromKB() {
	while (true) {
		cout << setw(attrIndentSize) << "Singer age (Int) : ";
		cin >> mAge;

		// Check if input is integer.
		int result = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (result != 1) {
			// Success
			break;
		} else {
			cout << setw(attrIndentSize) << "Wrong input!\n";
		}
	}
}

// Set sex from keyboard input
void SingerType::SetSexFromKB() {
	cout << setw(attrIndentSize) << "Singer sex (Char) : ";
	cin >> mSex;
	cin.ignore(100, '\n');
}

// Add song to song list
int SingerType::AddSong(const SongType &song) {
	return this->mSongList.Add(song);
}

// Remove song from song list
int SingerType::RemoveSong(const SongType &song) {
	return mSongList.Delete(song);
}

// Compare operators
bool SingerType::operator==(const SingerType &that) const {
	return this->mName.compare(that.mName) == 0;
}

bool SingerType::operator!=(const SingerType &that) const {
	return !(*this == that);
}

bool SingerType::operator<(const SingerType &that) const {
	return this->mName.compare(that.mName) < 0;
}

bool SingerType::operator<=(const SingerType &that) const {
	return this->mName.compare(that.mName) <= 0;
}

bool SingerType::operator>(const SingerType &that) const {
	return this->mName.compare(that.mName) > 0;
}

bool SingerType::operator>=(const SingerType &that) const {
	return this->mName.compare(that.mName) >= 0;
}
