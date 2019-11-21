#ifndef MDI_ID3_V2_READER
#define MDI_ID3_V2_READER

#include "ID3Reader.h"
#include "ID3v2.h"
#include <vector>


namespace MetadataInfo {
	namespace ID3 {
		// Abstract Class
		class ID3v2Reader : protected ID3Reader {
		public:
			ID3v2Reader(FILE *fp) : ID3Reader(fp) {}
			static long Convert3BytesToLittleEndian(char *buffer);
			static long Convert4BytesToLittleEndian(char *buffer);
			static  int ReadSynchSize(char *synchSize);

		public:
			virtual bool    LoadHeader() = 0;
			virtual long    GetBinarySize(InfoKind metadataType) = 0;
			virtual long    GetBinaryValue(InfoKind metadataType, void *destBuffer, long size) = 0;
			virtual wstring GetStringValue(InfoKind metadataType) = 0;
			virtual bool    ContainsInfo(InfoKind metadataType) = 0;
			virtual const vector<InfoKind> *ContainsInfoList();

		protected:
			H_ID3V2 m_header;
			vector<H_FRAME_POS_ID3V2> m_frame_list;
			vector<InfoKind> m_info_list;
		};

	}
}

#endif