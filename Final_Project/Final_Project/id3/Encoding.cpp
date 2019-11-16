#pragma warning(disable: 4996)

#include "Encoding.h"

using namespace MetadataInfo::ID3;


wstring Encoding::mbstowstr(const char *buffer, int size) {
	char *temp = (char *)malloc(size + 1);
	memset(temp, 0, size + 1);
	memcpy(temp, buffer, size);

	int dest_size = (size + 1) * sizeof(wchar_t);
	wchar_t *destBuffer = (wchar_t *)malloc(dest_size);
	memset(destBuffer, 0, dest_size);
	mbstowcs(destBuffer, temp, size);

	wstring result(destBuffer);

	free(destBuffer);
	free(temp);

	return result;
}



wstring Encoding::mbstowstr_l(const char *buffer, int size, std::locale loc) {
	return L"";
}