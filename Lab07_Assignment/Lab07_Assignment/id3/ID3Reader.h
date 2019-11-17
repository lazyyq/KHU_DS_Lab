#ifndef MDI_ID3_READER
#define MDI_ID3_READER


#include <iostream>
#include <vector>
#include "MetaInfo.h"



using namespace std;

namespace MetadataInfo {
	namespace ID3 {
		enum ValueType { TEXT, BINARY, NUMERIC };

		/*
		$00 - ISO-8859-1 (ASCII).
		$01 - UCS-2 (UTF-16 encoded Unicode with BOM), in ID3v2.2 and ID3v2.3.
		$02 - UTF-16BE encoded Unicode without BOM, in ID3v2.4.
		$03 - UTF-8 encoded Unicode, in ID3v2.4.
		*/
		enum CharSet { ISO_8859_1 = 0x00, UCS_2 = 0x01, UTF_16BE = 0x02, UTF_8 = 0x03 };

		class ID3Reader {
		protected:
			FILE *m_fp;
		public:
			ID3Reader(FILE *fp);
		public:
			virtual bool    LoadHeader() = 0;
			virtual long    GetBinarySize(InfoKind metadataType) = 0;
			virtual long    GetBinaryValue(InfoKind metadataType, void *destBuffer, long size) = 0;
			virtual wstring GetStringValue(InfoKind metadataType) = 0;
			virtual bool    ContainsInfo(InfoKind metadataType) = 0;
			virtual const vector<InfoKind> *ContainsInfoList() = 0;

			long    GetBinarySize(wstring frameId);
			long    GetBinaryValue(wstring frameId, void *destBuffer, long size);
			wstring GetStringValue(wstring frameId);
			bool    ContainsInfo(wstring frameId);
		protected:
			virtual ValueType GetValueType(InfoKind metadataType);
			virtual wstring ConvertToText(const char *buffer, int size, CharSet enc);
			virtual wstring ConvertToText(int num);
			virtual wstring ConvertToText(long num);
			InfoKind ConverToInfoKind(wstring frameId);
		};

	}
}

#endif