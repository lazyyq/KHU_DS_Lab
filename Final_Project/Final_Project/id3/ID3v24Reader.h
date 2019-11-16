#ifndef MDI_ID3_V24_READER
#define MDI_ID3_V24_READER

#include "ID3v2Reader.h"

namespace MetadataInfo {
	namespace ID3 {

		class ID3v24Reader : protected ID3v2Reader {
		public:
			static  bool IsValidType(FILE *fp);
			virtual bool LoadHeader();
			virtual long GetBinarySize(InfoKind metadataType);
			virtual long GetBinaryValue(InfoKind metadataType, void *destBuffer, long size);
			virtual wstring GetStringValue(InfoKind metadataType);
			virtual bool ContainsInfo(InfoKind metadataType);
		};

	}
}

#endif