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

void MusicItem::DisplayIdOnScreen() {
	cout << setw(attrIndentSize) << "ID : " << mId << endl;
}

void MusicItem::DisplayTypeOnScreen() {
	cout << setw(attrIndentSize) << "Type : " << mType << endl;
}

void MusicItem::DisplayNameOnScreen() {
	cout << setw(attrIndentSize) << "Name : " << mName << endl;
}

void MusicItem::DisplayMelodizerOnScreen() {
	cout << setw(attrIndentSize) << "Melodizer : " << mMelodizer << endl;
}

void MusicItem::DisplayArtistOnScreen() {
	cout << setw(attrIndentSize) << "Artist : " << mArtist << endl;
}

void MusicItem::DisplayGenreOnScreen() {
	cout << setw(attrIndentSize) << "Genre : " << mGenre << endl;
}

void MusicItem::DisplayRecordOnScreen() {
	DisplayIdOnScreen();
	DisplayTypeOnScreen();
	DisplayNameOnScreen();
	DisplayMelodizerOnScreen();
	DisplayArtistOnScreen();
	DisplayGenreOnScreen();
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

// Set music record from keyboard.
// Id is automatically generated using music name and artist.
void MusicItem::SetRecordFromKB() {
	SetTypeFromKB();
	SetNameFromKB();
	SetMelodizerFromKB();
	SetArtistFromKB();
	SetGenreFromKB();

	// If music id does not already exist, automatically generate one.
	if (this->mId.compare("") == 0) {
		mId = GenerateMusicId();
	}
}

string MusicItem::GenerateMusicId() {
	time_t now = time(0); //현재 시간을 time_t 타입으로 저장
	struct tm timeinfo;
	char ch[20];
	localtime_s(&timeinfo, &now);
	strftime(ch, sizeof(ch), "%y%m%d-%H%M%S", &timeinfo); // YYYY-MM-DD.HH:mm:ss 형태의 스트링

	return string(ch);
}

// Read a record from file.
// Store each line into respective variables.
int MusicItem::ReadDataFromFile(ifstream &fin) {
	// Temporary variable to hold string
	// which will later be converted to int
	string temp;

	getline(fin, mId);
	// Skip empty lines.
	while (mId.length() == 0) {
		getline(fin, mId);
	}
	getline(fin, temp);
	mType = stoi(temp);
	getline(fin, mName);
	getline(fin, mMelodizer);
	getline(fin, mArtist);
	getline(fin, mGenre);

	return 1;
};

// Write a record into file.
int MusicItem::WriteDataToFile(ofstream &fout) {
	fout << endl << endl;
	fout << mId << endl;
	fout << mType << endl;
	fout << mName << endl;
	fout << mMelodizer << endl;
	fout << mArtist << endl;
	fout << mGenre;

	return 1;
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
