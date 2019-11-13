#include "MenuScreen.h"

#include <conio.h>
#include <Windows.h>
#include <algorithm>

#include "CursorManager.h"

#define MENU_SIDE_MARGIN	24
#define MENU_MARGIN_START	(MENU_SIDE_MARGIN / 2)

using namespace std;

MenuScreen::MenuScreen(const string title) :
	mTitle(title) {}

MenuScreen::MenuScreen(const std::string title,
	const std::string *begin, const std::string *end) :
	mTitle(title) {
	AddMenu(begin, end);
}

MenuScreen::~MenuScreen() {
	mMenuList.MakeEmpty();
}

void MenuScreen::AddMenu() {
	mMenuList.Add("");
}

void MenuScreen::AddMenu(const string &title) {
	mMenuList.Add(title);
}

void MenuScreen::AddMenu(const std::string *begin, const std::string *end) {
	std::for_each(begin, end, [&](const auto &str) {
		mMenuList.Add(str);
		});
}

int MenuScreen::GetSelection() const {
	//
	// WARNING: DIRTY CODE AHEAD!!!
	//

	// Show menu
	system("cls");
	cout << endl << endl << endl;
	size_t width = mTitle.length() + MENU_SIDE_MARGIN;
	// Get longest title
	DoublyIterator<string> iter(mMenuList);
	for (string menu = iter.Next();
		iter.NextNotNull(); menu = iter.Next()) {
		if (width < menu.length() + MENU_SIDE_MARGIN) {
			width = menu.length() + MENU_SIDE_MARGIN;
		}
	}

	if (width < mTitle.length() + MENU_SIDE_MARGIN) {
		width = mTitle.length() + MENU_SIDE_MARGIN;
	}
	cout << "\t¦£";
	PrintNTimes("¦¡", MENU_MARGIN_START - 1);
	cout << " " << mTitle << " ";
	PrintNTimes("¦¡", MENU_MARGIN_START - 1);
	PrintNTimes("¦¡", width - (mTitle.length() + MENU_SIDE_MARGIN));
	cout << "¦¤\n";

	PrintNTimes("\t¦¢" + string(width, ' ') + "¦¢\n", 3);

	bool isFirstItem = true;
	COORD firstItemCursorPos = { 0, 0 };
	iter.ResetPointer();
	for (string menu = iter.Next();
		iter.NextNotNull(); menu = iter.Next()) {
		cout << "\t¦¢";
		cout << string(MENU_MARGIN_START, ' ');
		if (isFirstItem) {
			firstItemCursorPos =
				CursorManager::GetCursorPosition(
					GetStdHandle(STD_OUTPUT_HANDLE));
			firstItemCursorPos.X -= 2;
			isFirstItem = false;
		}
		cout << menu;
		cout << string(width - (menu.length() + MENU_MARGIN_START), ' ');
		cout << "¦¢\n";
	}

	PrintNTimes("\t¦¢" + string(width, ' ') + "¦¢\n", 3);

	cout << "\t¦¦";
	PrintNTimes("¦¡", width);
	cout << "¦¥\n";
	// Done showing menu

	CursorManager cm(firstItemCursorPos.X, firstItemCursorPos.X,
		firstItemCursorPos.Y, firstItemCursorPos.Y + mMenuList.GetLength() - 1);

	return cm.StartSelectMode();
}

string MenuScreen::GetTitle() const {
	return mTitle;
}

void MenuScreen::SetTitle(const string &title) {
	mTitle = title;
}

inline void MenuScreen::PrintNTimes(const string &str, const int n) {
	for (int i = 0; i < n; ++i) {
		cout << str;
	}
}
