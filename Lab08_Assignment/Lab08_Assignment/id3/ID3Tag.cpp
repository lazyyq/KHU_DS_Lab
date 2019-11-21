#include "ID3Tag.h"
#include "ID3DefaultReaderFactory.h"

using namespace MetadataInfo::ID3;


// ID3 Default Reader Factory
namespace MetadataInfo {
	namespace ID3 {
		const MetadataInfo::ID3::ID3ReaderFactory *DefaultReaderFactory = (ID3ReaderFactory *)new ID3DefaultReaderFactory();
	}
}



//==========================
// Constructor
//==========================
ID3Tag::ID3Tag() {
	this->m_factory = (ID3ReaderFactory *)(ID3::DefaultReaderFactory);
	this->m_reader = NULL;
	this->pFile = NULL;
	this->m_isOpened = false;

	std::locale system_locale("");
	std::locale::global(system_locale); // 맨 처음
}



//==========================
// Constructor with factory
//==========================
ID3Tag::ID3Tag(ID3ReaderFactory *factory) {
	this->m_factory = factory;
	this->m_reader = NULL;
	this->pFile = NULL;
	this->m_isOpened = false;

	std::locale system_locale("");
	std::locale::global(system_locale); // 맨 처음
}



//==========================
// Destructor
//==========================
ID3Tag::~ID3Tag() {
	this->Close();
}



//==========================
// Open Media File
//==========================
bool ID3Tag::Open(const char *filePath) {
	/*int length = filePath.size()+1;
	char * buffer = (char *)malloc(sizeof(char) * length);
	memset(buffer, 0, length);
	wcstombs(buffer, filePath.c_str(), length);*/

	// check
	if (this->m_isOpened == true) { this->Close(); }

	//this->pFile = fopen(filePath, "rb");
	fopen_s(&this->pFile, filePath, "rb");
	//free(buffer);

	if (this->pFile != NULL) {
		this->m_isOpened = true;
		this->m_reader = this->m_factory->CreateReader(this->pFile);
		return this->m_reader->LoadHeader();
	}
	return (this->pFile != NULL);
}


//==========================
// Open Media File
//==========================
bool ID3Tag::Open(const wchar_t *filePath) {
	/*int length = filePath.size()+1;
	char * buffer = (char *)malloc(sizeof(char) * length);
	memset(buffer, 0, length);
	wcstombs(buffer, filePath.c_str(), length);*/

	// check
	if (this->m_isOpened == true) { this->Close(); }

	//this->pFile = fopen(filePath, "rb");
	_wfopen_s(&this->pFile, filePath, L"rb");
	//free(buffer);

	if (this->pFile != NULL) {
		this->m_isOpened = true;
		this->m_reader = this->m_factory->CreateReader(this->pFile);
		return this->m_reader->LoadHeader();
	}
	return (this->pFile != NULL);
}



//==========================
// Close File
//==========================
bool ID3Tag::Close() {
	int result = 0;
	if (this->pFile != NULL) { result = fclose(this->pFile); this->pFile = NULL; }
	if (this->m_reader != NULL) { delete this->m_reader;        this->m_reader = NULL; }
	this->m_isOpened = false;
	return (result == 0);
}



//==========================
// Read Meta in Text
//==========================
wstring ID3Tag::GetStringValue(InfoKind metadataType) {
	return this->m_reader->GetStringValue(metadataType);
}



//==========================
// Get Binary Data Size
//==========================
long ID3Tag::GetBinarySize(InfoKind metadataType) {
	return this->m_reader->GetBinarySize(metadataType);
}



//==========================
// Read Meta in Binary
//==========================
long ID3Tag::GetBinaryValue(InfoKind metadataType, char *buffer, long size) {
	return this->m_reader->GetBinaryValue(metadataType, buffer, size);
}



//==========================
// Read Meta in Text
//==========================
wstring ID3Tag::GetStringValue(wstring frameId) {
	return this->m_reader->GetStringValue(frameId);
}



//==========================
// Get Binary Data Size
//==========================
long ID3Tag::GetBinarySize(wstring frameId) {
	return this->m_reader->GetBinarySize(frameId);
}



//==========================
// Read Meta in Binary
//==========================
long ID3Tag::GetBinaryValue(wstring frameId, char *buffer, long size) {
	return this->m_reader->GetBinaryValue(frameId, buffer, size);
}



bool ID3Tag::ContainsInfo(InfoKind metadataType) {
	return this->m_reader->ContainsInfo(metadataType);
}


bool ID3Tag::ContainsInfo(wstring frameId) {
	return this->m_reader->ContainsInfo(frameId);
}




const vector<InfoKind> *ID3Tag::ContainsInfoList() {
	return this->m_reader->ContainsInfoList();
}


const char *ID3Tag::GetBinaryImage(const char *id3ImageData, long imageDataSize, long &outputSize) {
	const char *pt = id3ImageData;
	char encoding = *pt;
	pt++; // SKIP text-encoding
	while (*pt != 00) { pt++; }	// SKIP mime-type
	pt++;
	pt++;	// SKIP Picture type
	while (*pt != 00) { pt++; }	// SKIP Description
	pt++;
	if (encoding > 0x00) { pt++; }
	outputSize = imageDataSize - (pt - id3ImageData);
	return pt;
}