#include "PlayItem.h"

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

PlayItem::~PlayItem() {
}

string PlayItem::GetId() {
	return mId;
}

int PlayItem::GetNumPlay() {
	return mNumPlay;
}

int PlayItem::GetInTime() {
	return mInTime;
}

void PlayItem::SetId(string inId) {
	mId = inId;
}

void PlayItem::SetNumPlay(int inNumPlay) {
	mNumPlay = inNumPlay;
}

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
bool PlayItem::operator==(const PlayItem& that) const {
	return this->mId.compare(that.mId) == 0;
}
