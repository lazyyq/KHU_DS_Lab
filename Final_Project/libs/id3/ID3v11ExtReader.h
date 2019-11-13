#ifndef MDI_ID3_V11_READER
#define MDI_ID3_V11_READER

#include "ID3Reader.h"
#include "ID3v1.h"

namespace MetadataInfo {
	namespace ID3 {

		class ID3v11ExtReader : protected ID3Reader {
		public:
			ID3v11ExtReader(FILE *fp) : ID3Reader(fp) {}
		private:
			char m_title[30 + 60];
			char m_artist[30 + 60];
			char m_album[30 + 60];
		public:
			static  bool IsValidType(FILE *fp);
		public:
			virtual bool LoadHeader();
			virtual long GetBinarySize(InfoKind metadataType);
			virtual long GetBinaryValue(InfoKind metadataType, void *destBuffer, long size);
			virtual wstring GetStringValue(InfoKind metadataType);
			virtual bool ContainsInfo(InfoKind metadataType);
			virtual const vector<InfoKind> *ContainsInfoList();
		private:
			H_ID3v1_EXT m_header;
			vector<InfoKind> m_info_list;
		};
	}
}

#endif