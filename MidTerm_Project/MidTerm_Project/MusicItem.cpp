#include "MusicItem.h"

MusicItem::MusicItem() {
	mId = "";
	mType = -1;
	mName = "";
	mMelodizer = "";
	mArtist = "";
	mGenre = "";
}

string MusicItem::GetId() {
	return mId;
}

int MusicItem::GetType() {
	return mType;
}

string MusicItem::GetName() {
	return mName;
}

string MusicItem::GetMelodizer() {
	return mMelodizer;
}

string MusicItem::GetArtist() {
	return mArtist;
}

string MusicItem::GetGenre() {
	return mGenre;
}

void MusicItem::SetId(string inId) {
	mId = inId;
}

void MusicItem::SetType(int inType) {
	mType = inType;
}

void MusicItem::SetName(string inName) {
	mName = inName;
}

void MusicItem::SetMelodizer(string inMelodizer) {
	mMelodizer = inMelodizer;
}

void MusicItem::SetArtist(string inArtist) {
	mArtist = inArtist;
}

void MusicItem::SetGenre(string inGenre) {
	mGenre = inGenre;
}

// Set records.
void MusicItem::SetRecord(string inId, int inType, string inName,
	string inMelodizer, string inArtist, string inGenre) {
	SetId(inId);
	SetType(inType);
	SetName(inName);
	SetMelodizer(inMelodizer);
	SetArtist(inArtist);
	SetGenre(inGenre);
}

void MusicItem::DisplayIdOnScreen() const {
	cout << setw(attrIndentSize) << "ID : " << mId << endl;
}

void MusicItem::DisplayTypeOnScreen() const {
	cout << setw(attrIndentSize) << "Type : " << mType << endl;
}

void MusicItem::DisplayNameOnScreen() const {
	cout << setw(attrIndentSize) << "Name : " << mName << endl;
}

void MusicItem::DisplayMelodizerOnScreen() const {
	cout << setw(attrIndentSize) << "Melodizer : " << mMelodizer << endl;
}

void MusicItem::DisplayArtistOnScreen() const {
	cout << setw(attrIndentSize) << "Artist : " << mArtist << endl;
}

void MusicItem::DisplayGenreOnScreen() const {
	cout << setw(attrIndentSize) << "Genre : " << mGenre << endl;
}

// Set music id from keyboard, where id is string.
void MusicItem::SetIdFromKB() {
	cout << setw(attrIndentSize) << "ID (String) : ";
	getline(cin, mId);
}

// Set music type from keyboard, where type is int.
void MusicItem::SetTypeFromKB() {
	while (true) {
		cout << setw(attrIndentSize) << "Type (Int) : ";
		cin >> mType;

		// Check if input is integer.
		int result = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (result != 1) {
			// Success
			break;
		} else {
			cout << setw(attrIndentSize) << "Wrong input!\n";
		}
	}
}

// Set music name from keyboard, where name is string.
void MusicItem::SetNameFromKB() {
	cout << setw(attrIndentSize) << "Name (String) : ";
	getline(cin, mName);
}

// Set music melodizer from keyboard, where melodizer is string.
void MusicItem::SetMelodizerFromKB() {
	cout << setw(attrIndentSize) << "Melodizer (String) : ";
	getline(cin, mMelodizer);
}

// Set music artist from keyboard, where artist is string.
void MusicItem::SetArtistFromKB() {
	cout << setw(attrIndentSize) << "Artist (String) : ";
	getline(cin, mArtist);
}

// Set music genre from keyboard, where genre is string.
void MusicItem::SetGenreFromKB() {
	cout << setw(attrIndentSize) << "Genre (String) : ";
	getline(cin, mGenre);
}

string MusicItem::GenerateMusicId() {
	time_t now = time(0); //���� �ð��� time_t Ÿ������ ����
	struct tm timeinfo;
	char ch[20];
	localtime_s(&timeinfo, &now);
	strftime(ch, sizeof(ch), "%y%m%d-%H%M%S", &timeinfo); // YYYY-MM-DD.HH:mm:ss ������ ��Ʈ��

	return string(ch);
}

// Compare two records
bool MusicItem::operator==(const MusicItem &that) const {
	return this->mId.compare(that.mId) == 0;
}

// Compare two records
bool MusicItem::operator!=(const MusicItem &that) const {
	return !(*this == that);
}

// Compare two records
bool MusicItem::operator>(const MusicItem &that) const {
	return this->mId > that.mId;
}

// Compare two records
bool MusicItem::operator>=(const MusicItem &that) const {
	return this->mId >= that.mId;
}

// Compare two records
bool MusicItem::operator<(const MusicItem &that) const {
	return this->mId < that.mId;
}

// Compare two records
bool MusicItem::operator<=(const MusicItem &that) const {
	return this->mId <= that.mId;
}

// Set music record from keyboard.
// Id is automatically generated using music name and artist.
istream &operator>>(istream &is, MusicItem &item) {
	item.SetTypeFromKB();
	item.SetNameFromKB();
	item.SetMelodizerFromKB();
	item.SetArtistFromKB();
	item.SetGenreFromKB();

	// If music id does not already exist, automatically generate one.
	if (item.mId.compare("") == 0) {
		item.mId = MusicItem::GenerateMusicId();
	}

	return is;
}

ostream &operator<<(ostream &os, const MusicItem &item) {
	item.DisplayIdOnScreen();
	item.DisplayTypeOnScreen();
	item.DisplayNameOnScreen();
	item.DisplayMelodizerOnScreen();
	item.DisplayArtistOnScreen();
	item.DisplayGenreOnScreen();

	return os;
}

// Read a record from file.
// Store each line into respective variables.
ifstream &operator>>(ifstream &ifs, MusicItem &item) {
	// Temporary variable to hold string
	// which will later be converted to int
	string temp;

	getline(ifs, item.mId);
	// Skip empty lines.
	while (item.mId.length() == 0) {
		getline(ifs, item.mId);
	}
	getline(ifs, temp);
	item.mType = stoi(temp);
	getline(ifs, item.mName);
	getline(ifs, item.mMelodizer);
	getline(ifs, item.mArtist);
	getline(ifs, item.mGenre);

	return ifs;
}

// Write a record into file.
ofstream &operator<<(ofstream &ofs, const MusicItem &item) {
	ofs << endl << endl;
	ofs << item.mId << endl;
	ofs << item.mType << endl;
	ofs << item.mName << endl;
	ofs << item.mMelodizer << endl;
	ofs << item.mArtist << endl;
	ofs << item.mGenre;

	return ofs;
}