#pragma once

#include <conio.h>
#include <Windows.h>
#include <iostream>

#define KEY_ARROW		224
#define KEY_UP			72
#define KEY_DOWN		80
#define KEY_LEFT		75
#define KEY_RIGHT		77
#define KEY_ENTER		13
#define KEY_SPACEBAR	32

class CursorManager {
public:
	CursorManager(int xFrom = 0, int xTo = INT_MAX,
		int yFrom = 0, int yTo = INT_MAX);
	void SetRange(int xFrom, int xTo, int yFrom, int yTo);
	int GetCurrentSelection();
	int StartSelectMode();
	static COORD GetCursorPosition(HANDLE handle);

private:
	int xFrom, xTo, yFrom, yTo;
	HANDLE handle;
	COORD coord;
	COORD orig;

	void SetCursorPoisition(COORD c);
	void GotoXY(int x, int y);
	void SetCursorVisibility(bool b);
};