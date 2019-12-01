#include "DialogUtils.h"

#include <Windows.h>
#include <ShlObj.h>
#include <string>

using namespace std;

bool DialogUtils::GetFolder(std::wstring &folderpath,
	const wchar_t *szCaption/*, HWND owner*/) {
	HWND owner = NULL;
	bool result = false;

	// The BROWSEINFO struct tells the shell 
	// how it should display the dialog.
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.ulFlags = BIF_USENEWUI;
	bi.hwndOwner = owner;
	bi.lpszTitle = szCaption;

	// must call this if using BIF_USENEWUI
	::OleInitialize(NULL);
	// Show the dialog and get the itemIDList for the 
	// selected folder.
	LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);
	if (pIDL != NULL) {
		// Create a buffer to store the path, then 
		// get the path.
		wchar_t buffer[_MAX_PATH] = { '\0' };
		if (::SHGetPathFromIDList(pIDL, buffer) != 0) {
			// Set the string value.
			folderpath = wstring(buffer);
			result = true;
		}
		// free the item id list
		CoTaskMemFree(pIDL);
	}
	::OleUninitialize();

	return result;
}

bool DialogUtils::GetFile(std::wstring &filename,
	const wchar_t *filter/*, HWND owner*/) {

	HWND owner = NULL;
	OPENFILENAME ofn;
	wchar_t tempFilename[_MAX_PATH] = L"";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = tempFilename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_NOCHANGEDIR | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"";

	if (GetOpenFileName(&ofn)) {
		filename = tempFilename;
		return true;
	} else {
		return false;
	}
}
