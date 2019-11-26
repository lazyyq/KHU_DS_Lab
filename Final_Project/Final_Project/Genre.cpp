#include "Genre.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#include "utils/StringUtils.h"

#define JSON_ATTR_GENRE			"Genre"
#define JSON_ATTR_SONGLIST		"Songs"
#define JSON_VALUE_STR_UNKNOWN	"Unknown"

using namespace std;
using namespace stringutils;

// Constructors
Genre::Genre() {
	mName = " ";
}

Genre::Genre(const string &inName) {
	mName = inName;
}

// Destructor
Genre::~Genre() {
	// Clean linked list
	mSongList.MakeEmpty();
}

// Get name
string Genre::GetName() {
	return mName;
}

// Set name
void Genre::SetName(string &inName) {
	mName = inName;
}

// Set name from keyboard input
void Genre::SetNameFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Genre name (String) : ";
	getline(cin, mName);
}

// Add song to song list
int Genre::AddSong(const SimpleItem &song) {
	return this->mSongList.Add(song);
}

// Remove song from song list
int Genre::RemoveSong(const SimpleItem &song) {
	return mSongList.Delete(song);
}

const SortedDoublyLinkedList<SimpleItem> &Genre::GetSongList() {
	return mSongList;
}

// Compare operators
bool Genre::operator==(const Genre &that) const {
	return this->mName.compare(that.mName) == 0;
}

bool Genre::operator!=(const Genre &that) const {
	return !(*this == that);
}

bool Genre::operator<(const Genre &that) const {
	return this->mName.compare(that.mName) < 0;
}

bool Genre::operator<=(const Genre &that) const {
	return this->mName.compare(that.mName) <= 0;
}

bool Genre::operator>(const Genre &that) const {
	return this->mName.compare(that.mName) > 0;
}

bool Genre::operator>=(const Genre &that) const {
	return this->mName.compare(that.mName) >= 0;
}

// Read record from JSON
Json::Value &operator>>(Json::Value &value, Genre &item) {
	item.mName = Utf8ToAnsi(value.get(JSON_ATTR_GENRE, JSON_VALUE_STR_UNKNOWN).asString());
	value[JSON_ATTR_SONGLIST] >> item.mSongList;

	return value;
}

// Write record to JSON
Json::Value &operator<<(Json::Value &value, const Genre &item) {
	value[JSON_ATTR_GENRE] = AnsiToUtf8(item.mName);
	value[JSON_ATTR_SONGLIST] << item.mSongList;

	return value;
}
