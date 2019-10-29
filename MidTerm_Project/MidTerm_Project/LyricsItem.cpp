#include "LyricsItem.h"

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

int LyricsItem::GetLyrics(string &lyrics) {
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
		ifs.close();
	}
	return 1;
}
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
