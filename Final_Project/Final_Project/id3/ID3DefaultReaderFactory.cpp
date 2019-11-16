#include "ID3DefaultReaderFactory.h"

#include "ID3InvalidReader.h"
#include "ID3v11Reader.h"
#include "ID3v11ExtReader.h"
#include "ID3v22Reader.h"
#include "ID3v23Reader.h"
#include "ID3v24Reader.h"

using namespace MetadataInfo::ID3;




ID3DefaultReaderFactory::ID3DefaultReaderFactory() {}



ID3Reader *ID3DefaultReaderFactory::CreateReader(FILE *fp) {
	if (ID3v23Reader::IsValidType(fp) == true) {
		return (ID3Reader *)new ID3v23Reader(fp);
	} else if (ID3v22Reader::IsValidType(fp) == true) {
		return (ID3Reader *)new ID3v22Reader(fp);
	} else if (ID3v11ExtReader::IsValidType(fp) == true) {
		return (ID3Reader *)new ID3v11ExtReader(fp);
	} else if (ID3v11Reader::IsValidType(fp) == true) {
		return (ID3Reader *)new ID3v11Reader(fp);
	}

	return (ID3Reader *)(new ID3InvalidReader(fp));
}