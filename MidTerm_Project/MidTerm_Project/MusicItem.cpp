#include "MusicItem.h"

// ������
MusicItem::MusicItem() {
	mId = "";
	mName = "";
	mMelodizer = "";
	mArtist = "";
	mGenre = "";
}

// ���
void MusicItem::Play() {
	cout << "\n\n\t>\n"
		<< "\t>      �ۢܢ�   Now playing   �ۢܢ�\n"
		<< "\t>\n"
		<< "\t>      ��  " << mName << "   by " << mArtist << "  ��\n"
		<< "\t>\n\n";
}

// ��� �����鿡 ���� Getter ��
string MusicItem::GetId() const {
	return mId;
}

string MusicItem::GetName() const {
	return mName;
}

string MusicItem::GetMelodizer() const {
	return mMelodizer;
}

string MusicItem::GetArtist() const {
	return mArtist;
}

string MusicItem::GetGenre() const {
	return mGenre;
}

// ��� �����鿡 ���� Setter ��
void MusicItem::SetId(string inId) {
	mId = inId;
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
void MusicItem::SetRecord(string inId, string inName,
	string inMelodizer, string inArtist, string inGenre) {
	SetId(inId);
	SetName(inName);
	SetMelodizer(inMelodizer);
	SetArtist(inArtist);
	SetGenre(inGenre);
}

// �� ������ ȭ�鿡 ǥ���ϱ� ���� �Լ���
void MusicItem::DisplayIdOnScreen() const {
	cout << setw(attrIndentSize) << "ID : " << mId << endl;
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
	cout << "\t" << setw(attrIndentSize) << "ID (String) : ";
	getline(cin, mId);
}

// Set music name from keyboard, where name is string.
void MusicItem::SetNameFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Name (String) : ";
	getline(cin, mName);
}

// Set music melodizer from keyboard, where melodizer is string.
void MusicItem::SetMelodizerFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Melodizer (String) : ";
	getline(cin, mMelodizer);
}

// Set music artist from keyboard, where artist is string.
void MusicItem::SetArtistFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Artist (String) : ";
	getline(cin, mArtist);
}

// Set music genre from keyboard, where genre is string.
void MusicItem::SetGenreFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Genre (String) : ";
	getline(cin, mGenre);
}

// ���� ���̵� ����
string MusicItem::GenerateMusicId(const MusicItem &item) {
	return item.mName + " - " + item.mArtist;
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
	item.SetNameFromKB();
	item.SetMelodizerFromKB();
	item.SetArtistFromKB();
	item.SetGenreFromKB();

	// If music id does not already exist, automatically generate one.
	if (item.mId.compare("") == 0) {
		item.mId = MusicItem::GenerateMusicId(item);
	}

	return is;
}

// ���� �ڼ��� ������ ȭ�鿡 ǥ��.
ostream &operator<<(ostream &os, const MusicItem &item) {
	item.DisplayIdOnScreen();
	item.DisplayNameOnScreen();
	item.DisplayMelodizerOnScreen();
	item.DisplayArtistOnScreen();
	item.DisplayGenreOnScreen();

	return os;
}

// Read a record from file.
// Store each line into respective variables.
ifstream &operator>>(ifstream &ifs, MusicItem &item) {
	getline(ifs, item.mId);
	// Skip empty lines.
	while (item.mId.length() == 0) {
		getline(ifs, item.mId);
	}
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
	ofs << item.mName << endl;
	ofs << item.mMelodizer << endl;
	ofs << item.mArtist << endl;
	ofs << item.mGenre;

	return ofs;
}
