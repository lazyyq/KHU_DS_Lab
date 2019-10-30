#include "SimpleItem.h"

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
