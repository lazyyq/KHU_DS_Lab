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

ifstream &operator>>(ifstream &ifs, PlaylistItem &item) {
	string temp;

	getline(ifs, item.mId);
	// Skip empty lines.
	while (item.mId.length() == 0) {
		getline(ifs, item.mId);
	}
	getline(ifs, temp);
	item.mPlayedTimes = stoi(temp);
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
	// String of format yymmdd-HHMMSS.
	// ex) 2019/10/20 13:03:28 -> 191020-130328
	strftime(ch, sizeof(ch), "%y%m%d-%H%M%S", &timeinfo);
	return ch;
}
