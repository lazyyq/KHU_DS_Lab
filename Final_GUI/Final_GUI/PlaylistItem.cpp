#include "PlaylistItem.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "utils/StringUtils.h"

#define PLAYITEM_ATTR_INDENT_SIZE	25

#define JSON_ATTR_ID			"ID"
#define JSON_ATTR_PLAYEDTIMES	"PlayedTimes"
#define JSON_ATTR_INSERTEDTIME	"InsertedTime"
#define JSON_VALUE_STR_UNKNOWN	"Unknown"
#define JSON_VALUE_INT_UNKNOWN	"-1"

using namespace std;
using namespace stringutils;

string PlaylistItem::mLastInsertTime = "0";
int PlaylistItem::mLastInsertBit = 0;

// Constructors
PlaylistItem::PlaylistItem() {
	mId = "";
	mPlayedTimes = 0;
	mInsertedTime = "0";
}

PlaylistItem::PlaylistItem(string inId) {
	mId = inId;
	mPlayedTimes = 0;
	mInsertedTime = GetCurrentTime();
}

PlaylistItem::PlaylistItem(string inId, int inPlayedTimes,
	string inInsertedTime) {
	mId = inId;
	mPlayedTimes = inPlayedTimes;
	mInsertedTime = inInsertedTime;
}

// Destructor
PlaylistItem::~PlaylistItem() {}

// Get id
string PlaylistItem::GetId() const {
	return mId;
}

// Get played count
int PlaylistItem::GetPlayedTimes() const {
	return mPlayedTimes;
}

// Get inserted time
string PlaylistItem::GetInsertedTime() const {
	return mInsertedTime;
}

// Set id
void PlaylistItem::SetId(string inId) {
	mId = inId;
}

// Set played count
void PlaylistItem::SetPlayedTimes(int inPlayedTimes) {
	mPlayedTimes = inPlayedTimes;
}

// Set music id from keyboard, where id is string.
void PlaylistItem::SetIdFromKB() {
	cout << "\t" << setw(attrIndentSize) << "ID (String) : ";
	getline(cin, mId);
}

// Increase played count.
void PlaylistItem::IncreasePlayedTimes() {
	++mPlayedTimes;
}

// Compare two items
bool PlaylistItem::operator==(const PlaylistItem &that) const {
	return this->mInsertedTime.compare(that.mInsertedTime) == 0;
}

bool PlaylistItem::operator<(const PlaylistItem &that) const {
	return this->mInsertedTime.compare(that.mInsertedTime) < 0;
}

bool PlaylistItem::operator<=(const PlaylistItem &that) const {
	return this->mInsertedTime.compare(that.mInsertedTime) <= 0;
}

bool PlaylistItem::operator>(const PlaylistItem &that) const {
	return this->mInsertedTime.compare(that.mInsertedTime) > 0;
}

bool PlaylistItem::operator>=(const PlaylistItem &that) const {
	return this->mInsertedTime.compare(that.mInsertedTime) >= 0;
}

// Read record from JSON
Json::Value &operator>>(Json::Value &value, PlaylistItem &item) {
	item.mId = Utf8ToAnsi(value.get(JSON_ATTR_ID, JSON_VALUE_STR_UNKNOWN).asString());
	item.mPlayedTimes = value.get(JSON_ATTR_PLAYEDTIMES, JSON_VALUE_INT_UNKNOWN).asInt();
	item.mInsertedTime = Utf8ToAnsi(value.get(JSON_ATTR_INSERTEDTIME, JSON_VALUE_STR_UNKNOWN).asString());

	return value;
}

// Write record to JSON
Json::Value &operator<<(Json::Value &value, const PlaylistItem &item) {
	value[JSON_ATTR_ID] = AnsiToUtf8(item.mId);
	value[JSON_ATTR_PLAYEDTIMES] = item.mPlayedTimes;
	value[JSON_ATTR_INSERTEDTIME] = AnsiToUtf8(item.mInsertedTime);

	return value;
}

string PlaylistItem::GetCurrentTime() {
	time_t now = time(0); // Save current time as time_t
	tm timeinfo;
	char ch[20];
	localtime_s(&timeinfo, &now); // Convert time to timeinfo
	// String of format yymmdd-HHMMSS.
	// ex) 2019/10/20 13:03:28 -> 191020-130328
	strftime(ch, sizeof(ch), "%y%m%d-%H%M%S", &timeinfo);
	string str = ch;

	// Since our smallest time unit is 1 second, we can only add 1 song per sec.
	// Resolve this by adding an extra 4 bits of integers to the end.
	if (str > mLastInsertTime) {
		// New current time is bigger than the last value, we're good to go.
		// Reset bit to 0 and last inserted time to current time.
		mLastInsertBit = 0;
		mLastInsertTime = str;
	}
	// Insert last bit to prevent duplicate time
	stringstream ss;
	ss << setw(4) << setfill('0') << mLastInsertBit++; // ex) 0001, 0003
	str += ss.str();
	return str;
}
