#include "ID3InvalidReader.h"

using namespace MetadataInfo::ID3;


namespace MetadataInfo {
	namespace ID3 {
		const vector<InfoKind> empty_info_list;
	}
}


bool ID3InvalidReader::LoadHeader() {
	return false;
}




long ID3InvalidReader::GetBinarySize(InfoKind metadataType) {
	return 0L;
}



long ID3InvalidReader::GetBinaryValue(InfoKind metadataType, void *destBuffer, long size) {
	return false;
}



wstring ID3InvalidReader::GetStringValue(InfoKind metadataType) {
	return L"";
}



bool ID3InvalidReader::ContainsInfo(InfoKind metadataType) {
	return false;
}


const vector<InfoKind> *ID3InvalidReader::ContainsInfoList() {
	return &empty_info_list;
}