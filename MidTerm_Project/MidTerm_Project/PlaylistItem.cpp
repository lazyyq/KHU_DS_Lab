#include "PlaylistItem.h"

// Constructors
PlaylistItem::PlaylistItem() {
	mId = "";
	mNumPlay = -1;
	mInTime = -1;
}

PlaylistItem::PlaylistItem(string inId, int inNumPlay, int inInTime) {
	mId = inId;
	mNumPlay = inNumPlay;
	mInTime = inInTime;
}

// Destructor
PlaylistItem::~PlaylistItem() {}

// Get id
string PlaylistItem::GetId() {
	return mId;
}

// Get played count
int PlaylistItem::GetNumPlay() {
	return mNumPlay;
}

// Get inserted time
int PlaylistItem::GetInTime() {
	return mInTime;
}

// Set id
void PlaylistItem::SetId(string inId) {
	mId = inId;
}

// Set played count
void PlaylistItem::SetNumPlay(int inNumPlay) {
	mNumPlay = inNumPlay;
}

// Set inserted time
void PlaylistItem::SetInTime(int inInTime) {
	mInTime = inInTime;
}

// Set music id from keyboard, where id is string.
void PlaylistItem::SetIdFromKB() {
	cout << setw(attrIndentSize) << "ID (String) : ";
	getline(cin, mId);
}

// Increase played count.
void PlaylistItem::IncreaseNumPlay() {
	++mNumPlay;
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
