#ifndef MDI_ID3_INVALID_READER
#define MDI_ID3_INVALID_READER

#include "ID3Reader.h"

namespace MetadataInfo {
	namespace ID3 {

		class ID3InvalidReader : ID3Reader {
		public:
			ID3InvalidReader(FILE *fp) : ID3Reader(fp) {}
			bool LoadHeader();
			long GetBinarySize(InfoKind metadataType);
			long GetBinaryValue(InfoKind metadataType, void *destBuffer, long size);
			wstring GetStringValue(InfoKind metadataType);
			bool    ContainsInfo(InfoKind metadataType);
			const vector<InfoKind> *ContainsInfoList();
		private:
			const static vector<InfoKind> m_info_list;
		};
	}
}

#endif