#ifndef MDI_ID3_V1_READER
#define MDI_ID3_V1_READER

#include "ID3Reader.h"
#include "ID3v1.h"

namespace MetadataInfo {
	namespace ID3 {

		class ID3v11Reader : protected ID3Reader {
		public:
			ID3v11Reader(FILE *fp) : ID3Reader(fp) {}
			static  bool IsValidType(FILE *fp);
		public:
			virtual bool LoadHeader();
			virtual long GetBinarySize(InfoKind metadataType);
			virtual long GetBinaryValue(InfoKind metadataType, void *destBuffer, long size);
			virtual wstring GetStringValue(InfoKind metadataType);
			virtual bool ContainsInfo(InfoKind metadataType);
			virtual const vector<InfoKind> *ContainsInfoList();
		private:
			H_ID3v1 m_header;
			vector<InfoKind> m_info_list;
		};
	}
}

#endif