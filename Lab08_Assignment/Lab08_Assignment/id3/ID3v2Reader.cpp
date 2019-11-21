#include "ID3v2Reader.h"

using namespace MetadataInfo::ID3;


long ID3v2Reader::Convert3BytesToLittleEndian(char *buffer) {
	return ((buffer[0] & 0xFF) << 16 | (buffer[1] & 0xFF) << 8 | buffer[2] & 0xFF);
}



long ID3v2Reader::Convert4BytesToLittleEndian(char *buffer) {
	return ((buffer[0] & 0xFF) << 24 | (buffer[1] & 0xFF) << 16 | (buffer[2] & 0xFF) << 8 | buffer[3] & 0xFF);
}



int ID3v2Reader::ReadSynchSize(char *synchSize) {
	return (synchSize[0] & 0x7F) << 21 | (synchSize[1] & 0x7F) << 14 | (synchSize[2] & 0x7F) << 7 | (synchSize[3] & 0x7F);
}



const vector<InfoKind> *ID3v2Reader::ContainsInfoList() {
	return &this->m_info_list;
}
