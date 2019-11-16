#pragma warning(disable: 4996)

#include "ID3v11ExtReader.h"

using namespace MetadataInfo::ID3;



bool ID3v11ExtReader::IsValidType(FILE *fp) {
	H_ID3v1_EXT temp;
	fseek(fp, -(int)sizeof(temp), SEEK_END);
	fread(&temp, sizeof(temp), 1, fp);

	return (memcmp(temp.marker, "TAG+", 4) == 0 && memcmp(temp.ID3v1_header.marker, "TAG", 3) == 0);
}



bool ID3v11ExtReader::LoadHeader() {
	bool result = false;

	fseek(this->m_fp, -(int)sizeof(this->m_header), SEEK_END);
	fread(&this->m_header, sizeof(this->m_header), 1, this->m_fp);

	if (memcmp(this->m_header.marker, "TAG+", 4) == 0) {
		result = (memcmp(this->m_header.ID3v1_header.marker, "TAG", 3) == 0);

		// concatnate info
		memset(this->m_title, 0, 30 + 60);
		memcpy(this->m_title, this->m_header.ID3v1_header.title, 30);
		memcpy(this->m_title + 30, this->m_header.title, 60);

		memset(this->m_artist, 0, 30 + 60);
		memcpy(this->m_artist, this->m_header.ID3v1_header.artist, 30);
		memcpy(this->m_artist + 30, this->m_header.artist, 60);

		memset(this->m_album, 0, 30 + 60);
		memcpy(this->m_album, this->m_header.ID3v1_header.album, 30);
		memcpy(this->m_album + 30, this->m_header.album, 60);
	}
	return result;
}



long ID3v11ExtReader::GetBinarySize(InfoKind metadataType) {
	switch (metadataType) {
	case TITLE:
		return 30 + 60;
		break;
	case ARTIST:
		return 30 + 60;
		break;
	case ALBUM:
		return 30 + 60;
		break;
	case YEAR:
		return 4;
		break;
	case COMMENT:
		if (this->m_header.ID3v1_header.comment[30 - 2] == 0x00) {
			return 30 - 2;
		} else {
			return 30;
		}
		break;
	case START_TIME:
		return 6;
		break;
	case END_TIME:
		return 6;
		break;
	case GENRE:
		return 30;
	}

	return 0L;
}



long ID3v11ExtReader::GetBinaryValue(InfoKind metadataType, void *destBuffer, long size) {
	switch (metadataType) {
	case TITLE:
		memcpy(destBuffer, this->m_title, size);
		break;
	case ARTIST:
		memcpy(destBuffer, this->m_artist, size);
		break;
	case ALBUM:
		memcpy(destBuffer, this->m_album, size);
		break;
	case YEAR:
		memcpy(destBuffer, this->m_header.ID3v1_header.year, size);
		break;
	case COMMENT:
		memcpy(destBuffer, this->m_header.ID3v1_header.comment, size);
		break;
	case START_TIME:
		memcpy(destBuffer, this->m_header.start_time, size);
		break;
	case END_TIME:
		memcpy(destBuffer, this->m_header.end_time, size);
		break;
	case GENRE:
		memcpy(destBuffer, this->m_header.genre, size);
	case SPEED:
		return (int)this->m_header.genre;
	case TRACK:
		if (this->m_header.ID3v1_header.comment[30 - 2] == 0x00) {
			return (long)this->m_header.ID3v1_header.comment[30 - 1];
		}
	}
	return size;
}



wstring ID3v11ExtReader::GetStringValue(InfoKind metadataType) {
	long size = this->GetBinarySize(metadataType);
	if (size <= 0) { return L""; }

	char *buffer = (char *)malloc(sizeof(char) * size);
	wchar_t *destBuffer = (wchar_t *)malloc(sizeof(wchar_t) * size);

	this->GetBinaryValue(metadataType, buffer, size);

	mbstowcs(destBuffer, buffer, size);
	wstring result(destBuffer, size * 2);

	free(buffer);
	free(destBuffer);

	return result;
}



bool ID3v11ExtReader::ContainsInfo(InfoKind metadataType) {
	if (metadataType == InfoKind::TITLE ||
		metadataType == InfoKind::ARTIST ||
		metadataType == InfoKind::ALBUM ||
		metadataType == InfoKind::YEAR ||
		metadataType == InfoKind::COMMENT ||
		metadataType == InfoKind::START_TIME ||
		metadataType == InfoKind::END_TIME ||
		metadataType == InfoKind::GENRE ||
		metadataType == InfoKind::SPEED) {
		return true;
	} else if (metadataType == InfoKind::TRACK) {
		return (this->m_header.ID3v1_header.comment[30 - 2] == 0x00);
	} else {
		return false;
	}
}



const vector<InfoKind> *ID3v11ExtReader::ContainsInfoList() {
	return &this->m_info_list;
}