#include "SingerType.h"

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
	cout << setw(SINGERTYPE_ATTR_INDENT_SIZE) << "Song id (String) : ";
	getline(cin, mId);
}

// Set name from keyboard input
void SongItem::SetNameFromKB() {
	cout << setw(SINGERTYPE_ATTR_INDENT_SIZE) << "Song name (String) : ";
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
UnsortedLinkedList<SongItem> SingerType::GetSongList() {
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
	cout << setw(SINGERTYPE_ATTR_INDENT_SIZE) << "Singer name (String) : ";
	getline(cin, mName);
}

// Set age from keyboard input
void SingerType::SetAgeFromKB() {
	while (true) {
		cout << setw(SINGERTYPE_ATTR_INDENT_SIZE) << "Singer age (Int) : ";
		cin >> mAge;

		// Check if input is integer.
		int result = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (result != 1) {
			// Success
			break;
		} else {
			cout << setw(SINGERTYPE_ATTR_INDENT_SIZE) << "Wrong input!\n";
		}
	}
}

// Set sex from keyboard input
void SingerType::SetSexFromKB() {
	cout << setw(SINGERTYPE_ATTR_INDENT_SIZE) << "Singer sex (Char) : ";
	cin >> mSex;
	cin.ignore(100, '\n');
}

// Add song to song list
int SingerType::AddSong(const SongItem &song) {
	return this->mSongList.Add(song);
}

// Remove song from song list
int SingerType::RemoveSong(const SongItem &song) {
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
