#include "Singer.h"

// Constructors
SongItem::SongItem() {
	mId = "";
	mName = "";
}

SongItem::SongItem(const string &inId, const string &inName) {
	mId = inId;
	mName = inName;
}

// Destructor
SongItem::~SongItem() {}

// Get id
string SongItem::GetId() {
	return mId;
}

// Get name
string SongItem::GetName() {
	return mName;
}

// Set id
void SongItem::SetId(string &inId) {
	mId = inId;
}

// Set name
void SongItem::SetName(string &inName) {
	mName = inName;
}

// Set info from keyboard input
void SongItem::SetInfoFromKB() {
	SetIdFromKB();
	SetNameFromKB();
}

// Set id from keyboard input
void SongItem::SetIdFromKB() {
	cout << setw(attrIndentSize) << "Song id (String) : ";
	getline(cin, mId);
}

// Set name from keyboard input
void SongItem::SetNameFromKB() {
	cout << setw(attrIndentSize) << "Song name (String) : ";
	getline(cin, mName);
}

// Compare operators
bool SongItem::operator==(const SongItem &that) const {
	return this->mId.compare(that.mId) == 0;
}

bool SongItem::operator!=(const SongItem &that) const {
	return !(*this == that);
}

bool SongItem::operator<(const SongItem &that) const {
	return this->mId.compare(that.mId) < 0;
}

bool SongItem::operator<=(const SongItem &that) const {
	return this->mId.compare(that.mId) <= 0;
}

bool SongItem::operator>(const SongItem &that) const {
	return this->mId.compare(that.mId) > 0;
}

bool SongItem::operator>=(const SongItem &that) const {
	return this->mId.compare(that.mId) >= 0;
}

// Constructors
Singer::Singer() {
	mName = "";
	mAge = -1;
	mSex = NULL;
}

Singer::Singer(const string &inName,
	const int inAge, const char &inSex) {
	mName = inName;
	mAge = inAge;
	mSex = inSex;
}

// Destructor
Singer::~Singer() {
	// Clean linked list
	mSongList.MakeEmpty();
}

// Get name
string Singer::GetName() {
	return mName;
}

// Get age
int Singer::GetAge() {
	return mAge;
}

// Get sex
char Singer::GetSex() {
	return mSex;
}

// Get song list
UnsortedLinkedList<SongItem> Singer::GetSongList() {
	return mSongList;
}

// Set name
void Singer::SetName(string &inName) {
	mName = inName;
}

// Set age
void Singer::SetAge(int inAge) {
	mAge = inAge;
}

// Set sex
void Singer::SetSex(char inSex) {
	mSex = inSex;
}

// Set info from keyboard input
void Singer::SetInfoFromKB() {
	SetNameFromKB();
	SetAgeFromKB();
	SetSexFromKB();
}

// Set name from keyboard input
void Singer::SetNameFromKB() {
	cout << setw(attrIndentSize) << "Singer name (String) : ";
	getline(cin, mName);
}

// Set age from keyboard input
void Singer::SetAgeFromKB() {
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
void Singer::SetSexFromKB() {
	cout << setw(attrIndentSize) << "Singer sex (Char) : ";
	cin >> mSex;
	cin.ignore(100, '\n');
}

// Add song to song list
int Singer::AddSong(const SongItem &song) {
	return this->mSongList.Add(song);
}

// Remove song from song list
int Singer::RemoveSong(const SongItem &song) {
	return mSongList.Delete(song);
}

// Compare operators
bool Singer::operator==(const Singer &that) const {
	return this->mName.compare(that.mName) == 0;
}

bool Singer::operator!=(const Singer &that) const {
	return !(*this == that);
}

bool Singer::operator<(const Singer &that) const {
	return this->mName.compare(that.mName) < 0;
}

bool Singer::operator<=(const Singer &that) const {
	return this->mName.compare(that.mName) <= 0;
}

bool Singer::operator>(const Singer &that) const {
	return this->mName.compare(that.mName) > 0;
}

bool Singer::operator>=(const Singer &that) const {
	return this->mName.compare(that.mName) >= 0;
}
