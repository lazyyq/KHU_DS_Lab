#include "StringUtils.h"

#include <Windows.h>

// Convert wstring to string
std::string stringutils::WstrToStr(const std::wstring &wstr,
	unsigned int codePage) {
	std::string ret;
	// Get length
	int len = WideCharToMultiByte(codePage, 0, wstr.c_str(),
		wstr.length(), NULL, 0, NULL, NULL);
	if (len > 0) {
		ret.resize(len);
		// Actual conversion
		WideCharToMultiByte(codePage, 0, wstr.c_str(),
			wstr.length(), &ret[0], len, NULL, NULL);
	}
	return ret;
}

// Convert string to wstring
std::wstring stringutils::StrToWstr(const std::string &str,
	unsigned int codePage) {
	std::wstring ret;
	// Get length
	int len = MultiByteToWideChar(codePage, 0, str.c_str(),
		str.length(), NULL, 0);
	if (len > 0) {
		ret.resize(len);
		// Actual conversion
		MultiByteToWideChar(codePage, 0, str.c_str(),
			str.length(), &ret[0], len);
	}
	return ret;
}

// Convert ansi text to utf8
std::string stringutils::AnsiToUtf8(const std::string &str) {
	// Convert to wstring first
	std::wstring wstr = StrToWstr(str, CP_ACP);
	// then convert back to string
	return WstrToStr(wstr, CP_UTF8);
}

// Convert utf8 text to ansi
std::string stringutils::Utf8ToAnsi(const std::string &str) {
	// Convert to wstring first
	std::wstring wstr = StrToWstr(str, CP_UTF8);
	// then convert back to string
	return WstrToStr(wstr, CP_ACP);
}
