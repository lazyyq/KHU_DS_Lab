#include "PlaylistItem.h"

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
string PlaylistItem::GetId() {
	return mId;
}

// Get played count
int PlaylistItem::GetPlayedTimes() {
	return mPlayedTimes;
}

// Get inserted time
string PlaylistItem::GetInsertedTime() {
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

#define JSON_ATTR_ID			"ID"
#define JSON_ATTR_PLAYEDTIMES	"PlayedTimes"
#define JSON_ATTR_INSERTEDTIME	"InsertedTime"
#define JSON_VALUE_STR_UNKNOWN	"Unknown"
#define JSON_VALUE_INT_UNKNOWN	"-1"

// Read record from JSON
Json::Value &operator>>(Json::Value &value, PlaylistItem &item) {
	item.mId = value.get(JSON_ATTR_ID, JSON_VALUE_STR_UNKNOWN).asString();
	item.mPlayedTimes = value.get(JSON_ATTR_PLAYEDTIMES, JSON_VALUE_INT_UNKNOWN).asInt();
	item.mInsertedTime = value.get(JSON_ATTR_INSERTEDTIME, JSON_VALUE_STR_UNKNOWN).asString();

	return value;
}

// Write record to JSON
Json::Value &operator<<(Json::Value &root, const PlaylistItem &item) {
	Json::Value newValue;
	newValue[JSON_ATTR_ID] = item.mId;
	newValue[JSON_ATTR_PLAYEDTIMES] = item.mPlayedTimes;
	newValue[JSON_ATTR_INSERTEDTIME] = item.mInsertedTime;
	root.append(newValue); // Add to array

	return root;
}

string PlaylistItem::GetCurrentTime() {
	time_t now = time(0); // Save current time as time_t
	tm timeinfo;
	char ch[20];
	localtime_s(&timeinfo, &now); // Convert time to timeinfo
	// String of format yymmdd-HHMMSS.
	// ex) 2019/10/20 13:03:28 -> 191020-130328
	strftime(ch, sizeof(ch), "%y%m%d-%H%M%S", &timeinfo);
	return ch;
}
