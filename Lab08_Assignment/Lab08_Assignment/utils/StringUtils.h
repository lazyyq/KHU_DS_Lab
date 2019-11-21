#pragma once

/**
*	Some common functions for working with strings
*/

#include <iostream>
#include <json/json.h>

#ifndef CP_ACP
#define CP_ACP		0
#endif
#ifndef CP_UTF8
#define CP_UTF8		65001
#endif

namespace stringutils {
	// Convert wstring to string
	std::string WstrToStr(const std::wstring &wstr,
		unsigned int codePage = CP_UTF8);

	// Convert string to wstring
	std::wstring StrToWstr(const std::string &str,
		unsigned int codePage = CP_UTF8);

	// Convert ansi text to utf8
	std::string AnsiToUtf8(const std::string &str);

	// Convert utf8 text to ansi
	std::string Utf8ToAnsi(const std::string &str);
};
