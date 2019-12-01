// DllExport void __cdecl Header(void);


#ifndef MDI_ID3
#define MDI_ID3

#include <iostream>


#include "ID3ReaderFactory.h"
#include "ID3Reader.h"
#include "MetaInfo.h"


using namespace std;

namespace MetadataInfo {
	namespace ID3 {
		class __declspec(dllexport) ID3Tag {
		public:
			ID3Tag();
			ID3Tag(ID3ReaderFactory *factory);
			~ID3Tag();

		public:
			bool Open(const char *filePath);
			bool Open(const wchar_t *filePath);
			bool Close();

			wstring GetStringValue(InfoKind metadataType);
			long    GetBinarySize(InfoKind metadataType);
			long    GetBinaryValue(InfoKind metadataType, char *buffer, long size);
			bool    ContainsInfo(InfoKind metadataType);

			wstring GetStringValue(wstring frameId);
			long    GetBinarySize(wstring frameId);
			long    GetBinaryValue(wstring frameId, char *buffer, long size);
			bool    ContainsInfo(wstring frameId);

			const vector<InfoKind> *ContainsInfoList();
			const char *GetBinaryImage(const char *id3ImageData, long imageDataSize, long &outputSize);
		private:
			ID3ReaderFactory *m_factory;
			ID3Reader *m_reader;
			wstring filePath;
			FILE *pFile;
			bool m_isOpened;
		};
	}
}

#endif