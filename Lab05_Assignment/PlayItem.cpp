#include "PlayItem.h"

// Constructors
PlayItem::PlayItem() {
	mId = "";
	mNumPlay = -1;
	mInTime = -1;
}

PlayItem::PlayItem(string inId, int inNumPlay, int inInTime) {
	mId = inId;
	mNumPlay = inNumPlay;
	mInTime = inInTime;
}

// Destructor
PlayItem::~PlayItem() {}

// Get id
string PlayItem::GetId() {
	return mId;
}

// Get played count
int PlayItem::GetNumPlay() {
	return mNumPlay;
}

// Get inserted time
int PlayItem::GetInTime() {
	return mInTime;
}

// Set id
void PlayItem::SetId(string inId) {
	mId = inId;
}

// Set played count
void PlayItem::SetNumPlay(int inNumPlay) {
	mNumPlay = inNumPlay;
}

// Set inserted time
void PlayItem::SetInTime(int inInTime) {
	mInTime = inInTime;
}

// Set music id from keyboard, where id is string.
void PlayItem::SetIdFromKB() {
	cout << setw(PLAYITEM_ATTR_INDENT_SIZE) << "ID (String) : ";
	getline(cin, mId);
}

// Increase played count.
void PlayItem::IncreaseNumPlay() {
	++mNumPlay;
}

// Compare two items
bool PlayItem::operator==(const PlayItem &that) const {
	return this->mInTime == that.mInTime;
}

bool PlayItem::operator<(const PlayItem &that) const {
	return this->mInTime < that.mInTime;
}

bool PlayItem::operator<=(const PlayItem &that) const {
	return this->mInTime <= that.mInTime;
}

bool PlayItem::operator>(const PlayItem &that) const {
	return this->mInTime > that.mInTime;
}

bool PlayItem::operator>=(const PlayItem &that) const {
	return this->mInTime >= that.mInTime;
}
