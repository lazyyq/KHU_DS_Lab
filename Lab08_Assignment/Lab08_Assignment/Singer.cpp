#include "Singer.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#include "utils/StringUtils.h"

#define JSON_ATTR_SINGER		"Singer"
#define JSON_ATTR_AGE			"Age"
#define JSON_ATTR_SEX			"Sex"
#define JSON_ATTR_SONGLIST		"Songs"
#define JSON_VALUE_STR_UNKNOWN	"Unknown"
#define JSON_VALUE_CHAR_UNKNOWN	' '
#define JSON_VALUE_INT_UNKNOWN	-1

using namespace std;
using namespace stringutils;

// Constructors
Singer::Singer() {
	mName = " ";
	mAge = -1;
	mSex = ' ';
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
	cout << "\t" << setw(attrIndentSize) << "Singer name (String) : ";
	getline(cin, mName);
}

// Set age from keyboard input
void Singer::SetAgeFromKB() {
	while (true) {
		cout << "\t" << setw(attrIndentSize) << "Singer age (Int) : ";
		cin >> mAge;

		// Check if input is integer.
		int result = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (result != 1) {
			// Success
			break;
		} else {
			cout << "Wrong input!\n";
		}
	}
}

// Set sex from keyboard input
void Singer::SetSexFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Singer sex (Char) : ";
	cin >> mSex;
	cin.ignore(100, '\n');
}

// Add song to song list
int Singer::AddSong(const SimpleItem &song) {
	return this->mSongList.Add(song);
}

// Remove song from song list
int Singer::RemoveSong(const SimpleItem &song) {
	return mSongList.Delete(song);
}

const SortedDoublyLinkedList<SimpleItem> &Singer::GetSongList() {
	return mSongList;
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

// Read record from JSON
Json::Value &operator>>(Json::Value &value, Singer &item) {
	item.mName = Utf8ToAnsi(value.get(JSON_ATTR_SINGER, JSON_VALUE_STR_UNKNOWN).asString());
	item.mAge = value.get(JSON_ATTR_AGE, JSON_VALUE_INT_UNKNOWN).asInt();
	item.mSex = value.get(JSON_ATTR_SEX, JSON_VALUE_CHAR_UNKNOWN).asInt();
	// Get song list
	Json::Value songs = value[JSON_ATTR_SONGLIST];
	SimpleItem simple;
	for (auto &i : songs) {
		i >> simple;
		item.mSongList.Add(simple);
	}

	return value;
}

// Write record to JSON
Json::Value &operator<<(Json::Value &root, const Singer &item) {
	Json::Value newValue;
	newValue[JSON_ATTR_SINGER] = AnsiToUtf8(item.mName);
	newValue[JSON_ATTR_AGE] = item.mAge;
	newValue[JSON_ATTR_SEX] = item.mSex;
	// Add song list
	Json::Value songs;
	SortedDoublyIterator<SimpleItem> iter(item.mSongList);
	for (SimpleItem simple = iter.Next();
		iter.NextNotNull();	simple = iter.Next()) {
		songs << simple;
	}
	newValue[JSON_ATTR_SONGLIST] = songs;
	root.append(newValue);

	return root;
}
