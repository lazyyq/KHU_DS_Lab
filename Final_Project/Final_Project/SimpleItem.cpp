#include "SimpleItem.h"

#include <iostream>
#include <string>
#include <iomanip>

#include "utils/StringUtils.h"

#define JSON_ATTR_ID			"ID"
#define JSON_ATTR_TITLE			"Title"
#define JSON_ATTR_ARTIST		"Artist"
#define JSON_VALUE_STR_UNKNOWN	"Unknown"

using namespace std;
using namespace stringutils;

// Constructors
SimpleItem::SimpleItem() {
	mId = "";
	mName = "";
}

SimpleItem::SimpleItem(const string &inId, const string &inName,
	const string &inArtist) {
	mId = inId;
	mName = inName;
	mArtist = inArtist;
}

// Destructor
SimpleItem::~SimpleItem() {}

// Get id
string SimpleItem::GetId() const {
	return mId;
}

// Get name
string SimpleItem::GetName() const {
	return mName;
}

// Get artist name
string SimpleItem::GetArtist() const {
	return mArtist;
}

// Set id
void SimpleItem::SetId(string &inId) {
	mId = inId;
}

// Set name
void SimpleItem::SetName(string &inName) {
	mName = inName;
}

// Set artist name
void SimpleItem::SetArtist(string &inArtist) {
	mArtist = inArtist;
}

// Compare operators
bool SimpleItem::operator==(const SimpleItem &that) const {
	return this->mId.compare(that.mId) == 0;
}

bool SimpleItem::operator!=(const SimpleItem &that) const {
	return !(*this == that);
}

bool SimpleItem::operator<(const SimpleItem &that) const {
	return this->mId.compare(that.mId) < 0;
}

bool SimpleItem::operator<=(const SimpleItem &that) const {
	return this->mId.compare(that.mId) <= 0;
}

bool SimpleItem::operator>(const SimpleItem &that) const {
	return this->mId.compare(that.mId) > 0;
}

bool SimpleItem::operator>=(const SimpleItem &that) const {
	return this->mId.compare(that.mId) >= 0;
}

// Read record from JSON
Json::Value &operator>>(Json::Value &value, SimpleItem &item) {
	item.mId = Utf8ToAnsi(value.get(JSON_ATTR_ID, JSON_VALUE_STR_UNKNOWN).asString());
	item.mName = Utf8ToAnsi(value.get(JSON_ATTR_TITLE, JSON_VALUE_STR_UNKNOWN).asString());
	item.mArtist = Utf8ToAnsi(value.get(JSON_ATTR_ARTIST, JSON_VALUE_STR_UNKNOWN).asString());

	return value;
}

// Write record to JSON
Json::Value &operator<<(Json::Value &value, const SimpleItem &item) {
	value[JSON_ATTR_ID] = AnsiToUtf8(item.mId);
	value[JSON_ATTR_TITLE] = AnsiToUtf8(item.mName);
	value[JSON_ATTR_ARTIST] = AnsiToUtf8(item.mArtist);

	return value;
}
