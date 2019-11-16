#ifndef MDI_ID3_V22_READER
#define MDI_ID3_V22_READER


#include <vector>
#include "ID3v2Reader.h"


namespace MetadataInfo {
	namespace ID3 {

		class ID3v22Reader : protected ID3v2Reader {
		public:
			ID3v22Reader(FILE *fp) : ID3v2Reader(fp) {}
			static  bool IsValidType(FILE *fp);
		public:
			virtual bool LoadHeader();
			virtual long GetBinarySize(InfoKind metadataType);
			virtual long GetBinaryValue(InfoKind metadataType, void *destBuffer, long size);
			virtual wstring GetStringValue(InfoKind metadataType);

		protected:
			virtual InfoKind  FrameIdTometadataType(const char *dest);
			virtual void ReadAllFrame(FILE *fp);
			virtual int  GetFramePosition(InfoKind metadataType);
			virtual bool ContainsInfo(InfoKind metadataType);

		protected:
			virtual bool IsUnsynchronisationUsed();
			virtual bool IsCompressionUsed();
		};

	}
}

#endif