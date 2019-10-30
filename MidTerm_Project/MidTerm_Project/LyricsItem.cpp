#include "LyricsItem.h"

// 생성자들
LyricsItem::LyricsItem() {
	mName = " ";
	mArtist = " ";
	mFileName = " ";
}

LyricsItem::LyricsItem(string inName, string inArtist) {
	mName = inName;
	mArtist = inArtist;
	mFileName = " ";
}

LyricsItem::LyricsItem(string inName, string inArtist,
	string inFileName) {
	mName = inName;
	mArtist = inArtist;
	mFileName = inFileName;
}

LyricsItem::~LyricsItem() {}

// 가사 가져오기
int LyricsItem::GetLyrics(string &lyrics) {
	// 가사가 담긴 파일 열기
	ifstream ifs(mFileName);
	if (!ifs || ifs.peek() == EOF) {
		return 0;
	}

	string line; // string to store lines from file
	// Skip the first two lines of file
	getline(ifs, line); // Skip music title
	getline(ifs, line); // Skip artist
	while (ifs) {
		getline(ifs, line);
		lyrics += '\t' + line + '\n'; // Add to lyrics string
	}

	if (ifs.is_open()) {
		ifs.close(); // 파일 닫기
	}
	return 1;
}

// 비교 연산자 오버로딩
// Primary key 는 곡명과 아티스트명.
// 곡명을 먼저 비교하고 같으면 아티스트명 비교.
bool LyricsItem::operator==(const LyricsItem &that) const {
	return this->mName.compare(that.mName) == 0 &&
		this->mArtist.compare(that.mArtist) == 0;
}

bool LyricsItem::operator<(const LyricsItem &that) const {
	if (this->mName.compare(that.mName) == 0) {
		return this->mArtist.compare(that.mArtist) < 0;
	} else {
		return this->mName.compare(that.mName) < 0;
	}
}

bool LyricsItem::operator<=(const LyricsItem &that) const {
	if (this->mName.compare(that.mName) == 0) {
		return this->mArtist.compare(that.mArtist) <= 0;
	} else {
		return this->mName.compare(that.mName) < 0;
	}
}

bool LyricsItem::operator>(const LyricsItem &that) const {
	if (this->mName.compare(that.mName) == 0) {
		return this->mArtist.compare(that.mArtist) > 0;
	} else {
		return this->mName.compare(that.mName) > 0;
	}
}

bool LyricsItem::operator>=(const LyricsItem &that) const {
	if (this->mName.compare(that.mName) == 0) {
		return this->mArtist.compare(that.mArtist) >= 0;
	} else {
		return this->mName.compare(that.mName) > 0;
	}
}
