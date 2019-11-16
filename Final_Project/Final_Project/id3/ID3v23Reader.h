#ifndef MDI_ID3_V23_READER
#define MDI_ID3_V23_READER


#include "ID3v22Reader.h"

namespace MetadataInfo {
	namespace ID3 {

		class ID3v23Reader : protected ID3v22Reader {
		public:
			ID3v23Reader(FILE *fp) : ID3v22Reader(fp) {}
			static  bool IsValidType(FILE *fp);
		public:
			virtual bool LoadHeader();
			virtual long GetBinarySize(InfoKind metadataType);
			virtual long GetBinaryValue(InfoKind metadataType, void *destBuffer, long size);
			virtual wstring GetStringValue(InfoKind metadataType);
			//virtual bool ContainsInfo(InfoKind metadataType);
		protected:
			//virtual TEXT_ENCODING GetTextEncoding(char * buffer);
			virtual InfoKind  FrameIdTometadataType(const char *dest);
			virtual void ReadAllFrame(FILE *fp);
			//virtual int  GetFramePosition(InfoKind metadataType);
		private:
			H_EXT_ID3V2 m_ext_header;
		protected:
			virtual bool ContainsExtenedHeader();
			virtual bool IsExperimentalStage();
			virtual bool IsUnsynchronisationUsed();
		private:
			bool IsTagAlterPreservation(H_FRAME_ID3V23 frame);
			bool IsFileAlterPreservation(H_FRAME_ID3V23 frame);
			bool IsReadOnly(H_FRAME_ID3V23 frame);
			bool IsCompression(H_FRAME_ID3V23 frame);
			bool IsEncryption(H_FRAME_ID3V23 frame);
			bool IsGroupingID(H_FRAME_ID3V23 frame);
		};

	}
}

#endif