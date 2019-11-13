#include "ID3v11Reader.h"

using namespace MetadataInfo::ID3;


//namespace MetadataInfo {
//    namespace ID3 {
//        const InfoKind _info_array[] = { TITLE, ARTIST, ALBUM, YEAR, COMMENT, GENRE, TRACK };
//        const InfoKind _info_array_without_track[] = { TITLE, ARTIST, ALBUM, YEAR, COMMENT, GENRE };
//        const vector<InfoKind> _info_list(_info_array, _info_array + sizeof(_info_array));
//        const vector<InfoKind> _info_list_without_track(_info_array_without_track, _info_array_without_track + sizeof(_info_array_without_track));
//    }
//}


bool ID3v11Reader::IsValidType(FILE *fp) {
	H_ID3v1 temp;
	fseek(fp, -(int)sizeof(temp), SEEK_END);
	fread(&temp, sizeof(temp), 1, fp);

	return (memcmp(temp.marker, "TAG", 3) == 0);
}



bool ID3v11Reader::LoadHeader() {
	fseek(this->m_fp, -(int)sizeof(this->m_header), SEEK_END);
	fread(&this->m_header, sizeof(this->m_header), 1, this->m_fp);

	return (memcmp(this->m_header.marker, "TAG", 3) == 0);
}



long ID3v11Reader::GetBinarySize(InfoKind metadataType) {
	switch (metadataType) {
	case TITLE:
		return 30;
		break;
	case ARTIST:
		return 30;
		break;
	case ALBUM:
		return 30;
		break;
	case YEAR:
		return 4;
		break;
	case COMMENT:
		if (this->m_header.comment[30 - 2] == 0x00) {
			return 30 - 2;
		} else {
			return 30;
		}
		break;
	}
	return 0L;
}



long ID3v11Reader::GetBinaryValue(InfoKind metadataType, void *destBuffer, long size) {
	switch (metadataType) {
	case TITLE:
		memcpy(destBuffer, this->m_header.title, size);
		return size;
		break;
	case ARTIST:
		memcpy(destBuffer, this->m_header.artist, size);
		return size;
		break;
	case ALBUM:
		memcpy(destBuffer, this->m_header.album, size);
		return size;
		break;
	case YEAR:
		memcpy(destBuffer, this->m_header.year, size);
		return size;
		break;
	case COMMENT:
		memcpy(destBuffer, this->m_header.comment, size);
		return size;
		break;
	case GENRE:
		return (int)this->m_header.genre;
	case TRACK:
		if (this->m_header.comment[30 - 2] == 0x00) {
			return (long)this->m_header.comment[30 - 1];
		}
	}
	return 0L;
}



wstring ID3v11Reader::GetStringValue(InfoKind metadataType) {
	return L"";
}



bool ID3v11Reader::ContainsInfo(InfoKind metadataType) {
	if (metadataType == InfoKind::TITLE ||
		metadataType == InfoKind::ARTIST ||
		metadataType == InfoKind::ALBUM ||
		metadataType == InfoKind::YEAR ||
		metadataType == InfoKind::COMMENT ||
		metadataType == InfoKind::GENRE ||
		metadataType == InfoKind::TRACK) {
		return true;
	} else if (metadataType == InfoKind::TRACK) {
		return (this->m_header.comment[30 - 2] == 0x00);
	} else {
		return false;
	}
}



const vector<InfoKind> *ID3v11Reader::ContainsInfoList() {
	return &this->m_info_list;
}