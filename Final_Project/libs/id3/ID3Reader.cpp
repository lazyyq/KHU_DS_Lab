#include "ID3Reader.h"
#include <sstream>

#include "Encoding.h"

using namespace MetadataInfo::ID3;


ID3Reader::ID3Reader(FILE *fp) {
	this->m_fp = fp;
}



ValueType ID3Reader::GetValueType(InfoKind metadataType) {
	if ((int)metadataType >= 0x01000000) {
		return ValueType::TEXT;
	}
	return ValueType::BINARY;
}


InfoKind ID3Reader::ConverToInfoKind(wstring frameId) {
	if (_wcsicmp(frameId.c_str(), L"TITLE") == 0) { return InfoKind::TITLE; }
	if (_wcsicmp(frameId.c_str(), L"ARTIST") == 0) { return InfoKind::ARTIST; }
	if (_wcsicmp(frameId.c_str(), L"ALBUM") == 0) { return InfoKind::ALBUM; }
	if (_wcsicmp(frameId.c_str(), L"YEAR") == 0) { return InfoKind::YEAR; }
	if (_wcsicmp(frameId.c_str(), L"COMMENT") == 0) { return InfoKind::COMMENT; }
	if (_wcsicmp(frameId.c_str(), L"TRACK") == 0) { return InfoKind::TRACK; }
	if (_wcsicmp(frameId.c_str(), L"GENRE") == 0) { return InfoKind::GENRE; }
	if (_wcsicmp(frameId.c_str(), L"SPEED") == 0) { return InfoKind::SPEED; }
	if (_wcsicmp(frameId.c_str(), L"START_TIME") == 0) { return InfoKind::START_TIME; }
	if (_wcsicmp(frameId.c_str(), L"END_TIME") == 0) { return InfoKind::END_TIME; }
	if (_wcsicmp(frameId.c_str(), L"UNIQUE_FILE_ID") == 0) { return InfoKind::UNIQUE_FILE_ID; }
	if (_wcsicmp(frameId.c_str(), L"CONTENT_GROUP") == 0) { return InfoKind::CONTENT_GROUP; }
	if (_wcsicmp(frameId.c_str(), L"SUBTITLE") == 0) { return InfoKind::SUBTITLE; }
	if (_wcsicmp(frameId.c_str(), L"BAND") == 0) { return InfoKind::BAND; }
	if (_wcsicmp(frameId.c_str(), L"CONDUCTOR") == 0) { return InfoKind::CONDUCTOR; }
	if (_wcsicmp(frameId.c_str(), L"MODIFIER") == 0) { return InfoKind::MODIFIER; }
	if (_wcsicmp(frameId.c_str(), L"COMPOSERS") == 0) { return InfoKind::COMPOSERS; }
	if (_wcsicmp(frameId.c_str(), L"LYRICIST") == 0) { return InfoKind::LYRICIST; }
	if (_wcsicmp(frameId.c_str(), L"LANGUAGE") == 0) { return InfoKind::LANGUAGE; }
	if (_wcsicmp(frameId.c_str(), L"CONTENT_TYPE") == 0) { return InfoKind::CONTENT_TYPE; }
	if (_wcsicmp(frameId.c_str(), L"PART") == 0) { return InfoKind::PART; }
	if (_wcsicmp(frameId.c_str(), L"ITNL_STD_RCD_CDE") == 0) { return InfoKind::ITNL_STD_RCD_CDE; }
	if (_wcsicmp(frameId.c_str(), L"DATE") == 0) { return InfoKind::DATE; }
	if (_wcsicmp(frameId.c_str(), L"TIME") == 0) { return InfoKind::TIME; }
	if (_wcsicmp(frameId.c_str(), L"RECORDING_DATE") == 0) { return InfoKind::RECORDING_DATE; }
	if (_wcsicmp(frameId.c_str(), L"MEDIA_TYPE") == 0) { return InfoKind::MEDIA_TYPE; }
	if (_wcsicmp(frameId.c_str(), L"FILE_TYPE") == 0) { return InfoKind::FILE_TYPE; }
	if (_wcsicmp(frameId.c_str(), L"BPM") == 0) { return InfoKind::BPM; }
	if (_wcsicmp(frameId.c_str(), L"COPYRIGHT") == 0) { return InfoKind::COPYRIGHT; }
	if (_wcsicmp(frameId.c_str(), L"PUBLISHER") == 0) { return InfoKind::PUBLISHER; }
	if (_wcsicmp(frameId.c_str(), L"ENCODER") == 0) { return InfoKind::ENCODER; }
	if (_wcsicmp(frameId.c_str(), L"ENCODING_SETTING") == 0) { return InfoKind::ENCODING_SETTING; }
	if (_wcsicmp(frameId.c_str(), L"ORIGIN_FILENAME") == 0) { return InfoKind::ORIGIN_FILENAME; }
	if (_wcsicmp(frameId.c_str(), L"LENGTH") == 0) { return InfoKind::LENGTH; }
	if (_wcsicmp(frameId.c_str(), L"SIZE") == 0) { return InfoKind::SIZE; }
	if (_wcsicmp(frameId.c_str(), L"PLAYLIST_DELAY") == 0) { return InfoKind::PLAYLIST_DELAY; }
	if (_wcsicmp(frameId.c_str(), L"INITIAL_KEY") == 0) { return InfoKind::INITIAL_KEY; }
	if (_wcsicmp(frameId.c_str(), L"ORIGIN_ALBUM") == 0) { return InfoKind::ORIGIN_ALBUM; }
	if (_wcsicmp(frameId.c_str(), L"ORIGIN_ARTIST") == 0) { return InfoKind::ORIGIN_ARTIST; }
	if (_wcsicmp(frameId.c_str(), L"ORIGIN_LYRICIST") == 0) { return InfoKind::ORIGIN_LYRICIST; }
	if (_wcsicmp(frameId.c_str(), L"ORIGIN_YEAR") == 0) { return InfoKind::ORIGIN_YEAR; }
	if (_wcsicmp(frameId.c_str(), L"FILE_WEB") == 0) { return InfoKind::FILE_WEB; }
	if (_wcsicmp(frameId.c_str(), L"ARTIST_WEB") == 0) { return InfoKind::ARTIST_WEB; }
	if (_wcsicmp(frameId.c_str(), L"SOURCE_WEB") == 0) { return InfoKind::SOURCE_WEB; }
	if (_wcsicmp(frameId.c_str(), L"COMMERCIAL_WEB") == 0) { return InfoKind::COMMERCIAL_WEB; }
	if (_wcsicmp(frameId.c_str(), L"COPYRIGHT_WEB") == 0) { return InfoKind::COPYRIGHT_WEB; }
	if (_wcsicmp(frameId.c_str(), L"PUBLISHER_WEB") == 0) { return InfoKind::PUBLISHER_WEB; }
	if (_wcsicmp(frameId.c_str(), L"INVOLVED_PEOPLES") == 0) { return InfoKind::INVOLVED_PEOPLES; }
	if (_wcsicmp(frameId.c_str(), L"CD_ID") == 0) { return InfoKind::CD_ID; }
	if (_wcsicmp(frameId.c_str(), L"EVENT_CODES") == 0) { return InfoKind::EVENT_CODES; }
	if (_wcsicmp(frameId.c_str(), L"AUDIO_ENCRYPT") == 0) { return InfoKind::AUDIO_ENCRYPT; }
	if (_wcsicmp(frameId.c_str(), L"COVER_IMAGE") == 0) { return InfoKind::COVER_IMAGE; }
	if (_wcsicmp(frameId.c_str(), L"COMMERCIAL_FRAME") == 0) { return InfoKind::COMMERCIAL_FRAME; }
	if (_wcsicmp(frameId.c_str(), L"ENCRYPT_METHOD") == 0) { return InfoKind::ENCRYPT_METHOD; }
	if (_wcsicmp(frameId.c_str(), L"EQUALIZATION") == 0) { return InfoKind::EQUALIZATION; }
	if (_wcsicmp(frameId.c_str(), L"GENERAL_ENCAPSULATED_OBJ") == 0) { return InfoKind::GENERAL_ENCAPSULATED_OBJ; }
	if (_wcsicmp(frameId.c_str(), L"GROUP_ID") == 0) { return InfoKind::GROUP_ID; }
	if (_wcsicmp(frameId.c_str(), L"LINK_INFO") == 0) { return InfoKind::LINK_INFO; }
	if (_wcsicmp(frameId.c_str(), L"LOCATION_TABLE") == 0) { return InfoKind::LOCATION_TABLE; }
	if (_wcsicmp(frameId.c_str(), L"OWNERSHIP_FRAME") == 0) { return InfoKind::OWNERSHIP_FRAME; }
	if (_wcsicmp(frameId.c_str(), L"PRIVATE_FRAME") == 0) { return InfoKind::PRIVATE_FRAME; }
	if (_wcsicmp(frameId.c_str(), L"PLAY_COUNTER") == 0) { return InfoKind::PLAY_COUNTER; }
	if (_wcsicmp(frameId.c_str(), L"POPULARIMETER") == 0) { return InfoKind::POPULARIMETER; }
	if (_wcsicmp(frameId.c_str(), L"POSITION_SYNCHRONISATION_FRAME") == 0) { return InfoKind::POSITION_SYNCHRONISATION_FRAME; }
	if (_wcsicmp(frameId.c_str(), L"RECOMMENDED_BUFFER_SIZE") == 0) { return InfoKind::RECOMMENDED_BUFFER_SIZE; }
	if (_wcsicmp(frameId.c_str(), L"RELATIVE_VOLUME_ADJUSTMENT") == 0) { return InfoKind::RELATIVE_VOLUME_ADJUSTMENT; }
	if (_wcsicmp(frameId.c_str(), L"REVERBB") == 0) { return InfoKind::REVERBB; }
	if (_wcsicmp(frameId.c_str(), L"SYNCH_LYRIC") == 0) { return InfoKind::SYNCH_LYRIC; }
	if (_wcsicmp(frameId.c_str(), L"SYNCH_TEMPO_CODES") == 0) { return InfoKind::SYNCH_TEMPO_CODES; }
	if (_wcsicmp(frameId.c_str(), L"ORIGIN_TITLE") == 0) { return InfoKind::ORIGIN_TITLE; }
	if (_wcsicmp(frameId.c_str(), L"FILE_OWNER") == 0) { return InfoKind::FILE_OWNER; }
	if (_wcsicmp(frameId.c_str(), L"INTERNET_RADIO_STATION_NAME") == 0) { return InfoKind::INTERNET_RADIO_STATION_NAME; }
	if (_wcsicmp(frameId.c_str(), L"INTERNET_RADIO_STATION_OWNER") == 0) { return InfoKind::INTERNET_RADIO_STATION_OWNER; }
	if (_wcsicmp(frameId.c_str(), L"TERMS_OF_USER") == 0) { return InfoKind::TERMS_OF_USER; }
	if (_wcsicmp(frameId.c_str(), L"LYRIC") == 0) { return InfoKind::LYRIC; }
	if (_wcsicmp(frameId.c_str(), L"INTERNET_RADIO_STATION_WEB") == 0) { return InfoKind::INTERNET_RADIO_STATION_WEB; }
	if (_wcsicmp(frameId.c_str(), L"PAYMENT_WEB") == 0) { return InfoKind::PAYMENT_WEB; }
	if (_wcsicmp(frameId.c_str(), L"USER_DEFINED_WEB") == 0) { return InfoKind::USER_DEFINED_WEB; }
	if (_wcsicmp(frameId.c_str(), L"USER_DEFINED") == 0) { return InfoKind::USER_DEFINED; }
	if (_wcsicmp(frameId.c_str(), L"NONE") == 0) { return InfoKind::NONE; }

	return InfoKind::NONE;
}


long ID3Reader::GetBinarySize(wstring frameId) {
	return this->GetBinarySize(this->ConverToInfoKind(frameId));
}


long ID3Reader::GetBinaryValue(wstring frameId, void *destBuffer, long size) {
	return this->GetBinaryValue(this->ConverToInfoKind(frameId), destBuffer, size);
}


wstring ID3Reader::GetStringValue(wstring frameId) {
	return this->GetStringValue(this->ConverToInfoKind(frameId));
}


bool ID3Reader::ContainsInfo(wstring frameId) {
	return this->ContainsInfo(frameId);
}




wstring ID3Reader::ConvertToText(const char *buffer, int size, CharSet enc) {
	wstring result;

	switch (enc) {
	case UTF_8:
		result.assign((wchar_t *)buffer, size);
		break;
	case UCS_2:
		result.assign((wchar_t *)buffer, size);
		break;
	case ISO_8859_1: default:
		result.assign(Encoding::mbstowstr(buffer, size));
		break;
	}

	return result;
}



wstring ID3Reader::ConvertToText(int num) {
	wstringstream s;
	s << num;
	return s.str();
}



wstring ID3Reader::ConvertToText(long num) {
	wstringstream s;
	s << num;
	return s.str();
}