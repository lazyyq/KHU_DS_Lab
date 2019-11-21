#include "MusicItem.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>
#include <time.h>

#include "utils/StringUtils.h"
#include "utils/Utils.h"

#define ATTR_VALUE_UNKNOWN		"Unknown"
#define W_ATTR_VALUE_UNKNOWN	L"Unknown"

#define JSON_ATTR_ID			"ID"
#define JSON_ATTR_TITLE			"Title"
#define JSON_ATTR_COMPOSER		"Composer"
#define JSON_ATTR_ARTIST		"Artist"
#define JSON_ATTR_GENRE			"Genre"
#define JSON_VALUE_STR_UNKNOWN	"Unknown"

using namespace std;
using namespace utils;
using namespace stringutils;
namespace ID3 = MetadataInfo::ID3;

// 생성자
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

// 재생
void MusicItem::Play() {
	cout << "\n\n\t>\n"
		<< "\t>      ♩♪♬   Now playing   ♩♪♬\n"
		<< "\t>\n"
		<< "\t>      ♬  " << mName << "   by " << mArtist << "  ♬\n"
		<< "\t>\n\n";
}

// 멤버 변수들에 대한 Getter 들
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

// 멤버 변수들에 대한 Setter 들
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

// 곡 정보를 화면에 표시하기 위한 함수들
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
	while (true) {
		cout << "\t" << setw(attrIndentSize) << "Name (String) : ";
		getline(cin, mName);
		// Don't accept empty name
		if (mName.compare("") == 0) {
			cout << "\tTitle cannot be empty!\n\n";
		} else {
			break;
		}
	}
}

// Set music melodizer from keyboard, where melodizer is string.
void MusicItem::SetMelodizerFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Melodizer (String) : ";
	getline(cin, mMelodizer);
	mMelodizer = mMelodizer.compare("") != 0 ? mMelodizer : ATTR_VALUE_UNKNOWN;
}

// Set music artist from keyboard, where artist is string.
void MusicItem::SetArtistFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Artist (String) : ";
	getline(cin, mArtist);
	mArtist = mArtist.compare("") != 0 ? mArtist : ATTR_VALUE_UNKNOWN;
}

// Set music genre from keyboard, where genre is string.
void MusicItem::SetGenreFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Genre (String) : ";
	getline(cin, mGenre);
	mGenre = mGenre.compare("") != 0 ? mGenre : ATTR_VALUE_UNKNOWN;
}

void MusicItem::SetRecordFromTag(MetadataInfo::ID3::ID3Tag &tag) {
	// 태그에서 제목, 아티스트, 작곡가, 장르 읽어오기
	const wstring wtitle = tag.GetStringValue(ID3::TITLE).compare(L"") ?
		tag.GetStringValue(ID3::TITLE) : W_ATTR_VALUE_UNKNOWN;

	const wstring wartist = tag.GetStringValue(ID3::ARTIST).compare(L"") ?
		tag.GetStringValue(ID3::ARTIST) : W_ATTR_VALUE_UNKNOWN;

	const wstring wcomposer = tag.GetStringValue(ID3::COMPOSERS).compare(L"") ?
		tag.GetStringValue(ID3::COMPOSERS) : W_ATTR_VALUE_UNKNOWN;

	// 장르의 경우 GENRE 태그를 먼저 읽어보고 없으면 CONTENT_TYPE에서 추출
	const wstring wgenre = tag.GetStringValue(ID3::GENRE).compare(L"") ?
		tag.GetStringValue(ID3::CONTENT_TYPE) :
		tag.GetStringValue(ID3::CONTENT_TYPE).compare(L"") ?
		tag.GetStringValue(ID3::CONTENT_TYPE) : W_ATTR_VALUE_UNKNOWN;

	// wstring -> string
	mName = WstrToStr(wtitle, CP_ACP);
	mArtist = WstrToStr(wartist, CP_ACP);
	mMelodizer = WstrToStr(wcomposer, CP_ACP);
	mGenre = WstrToStr(wgenre, CP_ACP);
	mId = GenerateMusicId(*this);
}

// 곡의 아이디를 생성
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

// 곡의 자세한 정보를 화면에 표시.
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
	item.mId = Utf8ToAnsi(value.get(JSON_ATTR_ID, JSON_VALUE_STR_UNKNOWN).asString());
	item.mName = Utf8ToAnsi(value.get(JSON_ATTR_TITLE, JSON_VALUE_STR_UNKNOWN).asString());
	item.mMelodizer = Utf8ToAnsi(value.get(JSON_ATTR_COMPOSER, JSON_VALUE_STR_UNKNOWN).asString());
	item.mArtist = Utf8ToAnsi(value.get(JSON_ATTR_ARTIST, JSON_VALUE_STR_UNKNOWN).asString());
	item.mGenre = Utf8ToAnsi(value.get(JSON_ATTR_GENRE, JSON_VALUE_STR_UNKNOWN).asString());

	return value;
}

// Write record to JSON
Json::Value &operator<<(Json::Value &root, const MusicItem &item) {
	Json::Value newValue;
	newValue[JSON_ATTR_ID] = AnsiToUtf8(item.mId);
	newValue[JSON_ATTR_TITLE] = AnsiToUtf8(item.mName);
	newValue[JSON_ATTR_COMPOSER] = AnsiToUtf8(item.mMelodizer);
	newValue[JSON_ATTR_ARTIST] = AnsiToUtf8(item.mArtist);
	newValue[JSON_ATTR_GENRE] = AnsiToUtf8(item.mGenre);
	root.append(newValue); // Add to array

	return root;
}
