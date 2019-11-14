#include "CursorManager.h"

#define CURSOR_EMPTY	' '
#define CURSOR_CURRENT	'>'

using namespace std;

CursorManager::CursorManager(int xFrom, int xTo,
	int yFrom, int yTo) :
	handle(GetStdHandle(STD_OUTPUT_HANDLE)),
	coord({ (short)xFrom, (short)yFrom }) {
	SetRange(xFrom, xTo, yFrom, yTo);
}

void CursorManager::SetRange(int _xFrom, int _xTo,
	int _yFrom, int _yTo) {
	xFrom = _xFrom;
	xTo = _xTo;
	yFrom = _yFrom;
	yTo = _yTo;

	if (_xFrom > _xTo) {
		xTo = _xFrom;
	}
	if (_yFrom > _yTo) {
		yTo = _yFrom;
	}
}

int CursorManager::GetCurrentSelection() {
	return coord.Y - yFrom + 1;
}

int CursorManager::StartSelectMode() {
	orig = GetCursorPosition(handle);
	SetCursorPoisition(coord);
	SetCursorVisibility(false);
	cout << CURSOR_CURRENT;

	while (int c = _getch()) {
		switch (c) {
		case KEY_ARROW:
			c = _getch();

			SetCursorPoisition(coord);
			cout << CURSOR_EMPTY;

			switch (c) {
			case KEY_UP:
				if (coord.Y > yFrom) --coord.Y;
				else coord.Y = yTo;
				break;
			case KEY_DOWN:
				if (coord.Y < yTo) ++coord.Y;
				else coord.Y = yFrom;
				break;
			case KEY_LEFT:
				if (coord.X > xFrom) --coord.X;
				else coord.X = xTo;
				break;
			case KEY_RIGHT:
				if (coord.X < xTo) ++coord.X;
				else coord.X = xFrom;
				break;
			}

			SetCursorPoisition(coord);
			cout << CURSOR_CURRENT;
			break;
		case KEY_ENTER:
		case KEY_SPACEBAR:
			// End cursor mode
			int choice = GetCurrentSelection();
			SetCursorPoisition(orig);
			SetCursorVisibility(true);
			return choice;
		}
	}

	return -1;
}

void CursorManager::SetCursorPoisition(COORD c) {
	SetConsoleCursorPosition(handle, c);
}

void CursorManager::GotoXY(int x, int y) {
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

void CursorManager::SetCursorVisibility(bool b) {
	CONSOLE_CURSOR_INFO info;

	GetConsoleCursorInfo(handle, &info);
	info.bVisible = b; // set the cursor visibility
	SetConsoleCursorInfo(handle, &info);
}

COORD CursorManager::GetCursorPosition(HANDLE handle) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (GetConsoleScreenBufferInfo(handle, &info)) {
		return info.dwCursorPosition;
	} else {
		return { 0, 0 };
	}
}
