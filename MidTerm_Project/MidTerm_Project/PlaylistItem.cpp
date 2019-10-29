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
	cout << setw(attrIndentSize) << "ID (String) : ";
	getline(cin, mId);
}

// Increase played count.
void PlaylistItem::IncreasePlayedTimes() {
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

ifstream &operator>>(ifstream &ifs, PlaylistItem &item) {
	getline(ifs, item.mId);
	// Skip empty lines.
	while (item.mId.length() == 0) {
		getline(ifs, item.mId);
	}
	ifs >> item.mPlayedTimes;
	getline(ifs, item.mInsertedTime);

	return ifs;
}

ofstream &operator<<(ofstream &ofs, const PlaylistItem &item) {
	ofs << endl << endl;
	ofs << item.mId.c_str() << endl;
	ofs << item.mPlayedTimes << endl;
	ofs << item.mInsertedTime.c_str();

	return ofs;
}

string PlaylistItem::GetCurrentTime() {
	time_t now = time(0); // Save current time as time_t
	tm timeinfo;
	char ch[20];
	localtime_s(&timeinfo, &now); // Convert time to timeinfo
	// String of format HHmmss. ex) 130328
	strftime(ch, sizeof(ch), "%H%M%S", &timeinfo);
	return ch;
}
