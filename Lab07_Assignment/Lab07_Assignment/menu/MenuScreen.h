#pragma once

#include <iostream>

#include "../DoublyLinkedList.h"

class MenuScreen {
public:
	MenuScreen(const std::string title);
	MenuScreen(const std::string title,
		const std::string *begin, const std::string *end);
	~MenuScreen();
	void AddMenu();
	void AddMenu(const std::string &title);
	void AddMenu(const std::string *begin, const std::string *end);
	int GetSelection() const;
	std::string GetTitle() const;
	void SetTitle(const std::string &title);

private:
	std::string mTitle;
	DoublyLinkedList<std::string> mMenuList;

	static inline void PrintNTimes(const std::string &str, const int n);
};

