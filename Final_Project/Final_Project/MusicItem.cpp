#include "MusicItem.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>
#include <time.h>

#include "Utils.h"

#define JSON_ATTR_ID			"ID"
#define JSON_ATTR_TITLE			"Title"
#define JSON_ATTR_COMPOSER		"Composer"
#define JSON_ATTR_ARTIST		"Artist"
#define JSON_ATTR_GENRE			"Genre"
#define JSON_VALUE_STR_UNKNOWN	"Unknown"

using namespace std;
using namespace utils;
namespace ID3 = MetadataInfo::ID3;

// ������
MusicItem::MusicItem() {
	mId = "";
	mName = "";
	mMelodizer = "";
	mArtist = "";
	mGenre = "";
}

MusicItem::MusicItem(ID3::ID3Tag &tag) {
	SetRecordFromTag(tag);
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

void MusicItem::SetRecordFromTag(MetadataInfo::ID3::ID3Tag &tag) {
	// �±׿��� ����, ��Ƽ��Ʈ, �۰, �帣 �о����
	const wstring wtitle = tag.GetStringValue(ID3::TITLE).compare(L"") ?
		tag.GetStringValue(ID3::TITLE) : L" ";

	const wstring wartist = tag.GetStringValue(ID3::ARTIST).compare(L"") ?
		tag.GetStringValue(ID3::ARTIST) : L" ";

	const wstring wcomposer = tag.GetStringValue(ID3::COMPOSERS).compare(L"") ?
		tag.GetStringValue(ID3::COMPOSERS) : L" ";

	// �帣�� ��� GENRE �±׸� ���� �о�� ������ CONTENT_TYPE���� ����
	const wstring wgenre = tag.GetStringValue(ID3::GENRE).compare(L"") ?
		tag.GetStringValue(ID3::CONTENT_TYPE) :
		tag.GetStringValue(ID3::CONTENT_TYPE).compare(L"") ?
		tag.GetStringValue(ID3::CONTENT_TYPE) : L" ";

	// wstring -> string
	mName = WstrToStr(wtitle);
	mArtist = WstrToStr(wartist);
	mMelodizer = WstrToStr(wcomposer);
	mGenre = WstrToStr(wgenre);
	mId = GenerateMusicId(*this);
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

// Read record from JSON
Json::Value &operator>>(Json::Value &value, MusicItem &item) {
	item.mId = value.get(JSON_ATTR_ID, JSON_VALUE_STR_UNKNOWN).asString();
	item.mName = value.get(JSON_ATTR_TITLE, JSON_VALUE_STR_UNKNOWN).asString();
	item.mMelodizer = value.get(JSON_ATTR_COMPOSER, JSON_VALUE_STR_UNKNOWN).asString();
	item.mArtist = value.get(JSON_ATTR_ARTIST, JSON_VALUE_STR_UNKNOWN).asString();
	item.mGenre = value.get(JSON_ATTR_GENRE, JSON_VALUE_STR_UNKNOWN).asString();

	return value;
}

// Write record to JSON
Json::Value &operator<<(Json::Value &root, const MusicItem &item) {
	Json::Value newValue;
	newValue[JSON_ATTR_ID] = item.mId;
	newValue[JSON_ATTR_TITLE] = item.mName;
	newValue[JSON_ATTR_COMPOSER] = item.mMelodizer;
	newValue[JSON_ATTR_ARTIST] = item.mArtist;
	newValue[JSON_ATTR_GENRE] = item.mGenre;
	root.append(newValue); // Add to array

	return root;
}
