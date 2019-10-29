#include "PlaylistItem.h"

// Constructors
PlaylistItem::PlaylistItem() {
	mId = "";
	mPlayedTimes = -1;
	mInsertedTime = -1;
}

PlaylistItem::PlaylistItem(string inId, int inNumPlay,
	int inInsertedTime) {
	mId = inId;
	mPlayedTimes = inNumPlay;
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
int PlaylistItem::GetInsertedTime() {
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

// Set inserted time
void PlaylistItem::SetInsertedTime(int inInsertedTime) {
	mInsertedTime = inInsertedTime;
}

// Set music id from keyboard, where id is string.
void PlaylistItem::SetIdFromKB() {
	cout << setw(attrIndentSize) << "ID (String) : ";
	getline(cin, mId);
}

// Increase played count.
void PlaylistItem::IncreaseNumPlay() {
	++mPlayedTimes;
}

// Compare two items
bool PlaylistItem::operator==(const PlaylistItem &that) const {
	return this->mId.compare(that.mId) == 0;
}

bool PlaylistItem::operator<(const PlaylistItem &that) const {
	return this->mId.compare(that.mId) < 0;
}

bool PlaylistItem::operator<=(const PlaylistItem &that) const {
	return this->mId.compare(that.mId) <= 0;
}

bool PlaylistItem::operator>(const PlaylistItem &that) const {
	return this->mId.compare(that.mId) > 0;
}

bool PlaylistItem::operator>=(const PlaylistItem &that) const {
	return this->mId.compare(that.mId) >= 0;
}
