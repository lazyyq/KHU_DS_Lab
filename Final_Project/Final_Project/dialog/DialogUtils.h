#pragma once

#include <string>

class DialogUtils {
public:
	static bool GetFolder(std::wstring &folderpath,
		const wchar_t *szCaption = NULL/*, HWND owner = NULL*/);

	static bool GetFile(std::wstring &filename,
		const wchar_t *filter = L"All Files (*.*)\0*.*\0"/*,
		HWND owner = NULL*/);
};

