#include "Launcher.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <json/json.h>

#include "Application.h"
#include "../menu/MenuScreen.h"
#include "../utils/StringUtils.h"
#include "../utils/Utils.h"

#define CONSOLE_COLOR			"70"
#define SETTINGS_FILENAME		"data/settings.json"
#define KEY_IS_FIRST_LAUNCH		"IsFirstLaunch"
#define KEY_IS_ADMIN			"IsAdmin"
#define KEY_USER_ID				"ID"
#define KEY_USER_PW				"PW"

using namespace std;
using namespace utils;
using namespace stringutils;

// Start program after login or registration
void Launcher::StartApp() {
	if (IsFirstLaunch()) {
		// Create admin account on first launch
		cout << "\n\tHi! This is your first time launching this app.\n" <<
			"\tPlease create an admin account.\n";
		if (!CreateAccount(true)) {
			cout << "\n\tCreating account failed.\n";
			return;
		}
		// Write record of first launch
		ofstream ofs(SETTINGS_FILENAME);
		if (!ofs) {
			return;
		}
		Json::Value value;
		value[KEY_IS_FIRST_LAUNCH] = false;
		ofs << value;
		if (ofs.is_open()) {
			ofs.close();
		}
		cout << endl;
		Pause(); Clear();
	}

	// Show menu
	const string title = "Welcome";
	const string menus[] = {
		"Login",
		"Create a new account",
		"",
		"Exit"
	};

	MenuScreen menu(title, begin(menus), end(menus));

	while (true) {
		switch (menu.GetSelection()) {
		case 1: // Login
			Clear();
			Login();
			break;
		case 2: // Register
			Clear();
			if (CreateAccount(false)) {
				Clear();
				Login();
			}
			break;
		case 4: return; // Exit program
		}
	}
}

// Check if this is first launch
bool Launcher::IsFirstLaunch() const {
	ifstream ifs(SETTINGS_FILENAME);
	// Consider as first launch if settings file is not found
	if (!ifs || ifs.peek() == EOF) {
		if (ifs.is_open()) {
			ifs.close();
		}
		return true;
	}
	Json::Value json;
	ifs >> json;
	bool isFirstLaunch = json.get(KEY_IS_FIRST_LAUNCH, true).asBool();
	if (ifs.is_open()) {
		ifs.close();
	}
	return isFirstLaunch;
}

// Show login window and start program.
void Launcher::Login() {
	while (true) {
		string id, pw;
		cout << "\n\tLogin\n\n";
		// Get id
		while (true) {
			cout << "\n\t" << setw(15) << std::left << "ID " << ": ";
			getline(cin, id);
			// Check if empty string
			if (id.length() == 0) {
				cout << "\n\tID cannot be empty!\n";
				continue;
			} else {
				break;
			}
		}
		// Get password
		cout << "\t" << setw(15) << std::left << "Password " << ": ";
		GetPassword(pw);

		bool isAdmin = false;
		// Check if id and pw match, then start program
		if (Authorize(id, pw, isAdmin)) {
			Start(id, isAdmin);
			break;
		} else {
			cout << "\n\tNonexistent username or wrong password! Try again.\n";
			Pause(); Clear();
		}
	}
}

// Create a new account
bool Launcher::CreateAccount(const bool isAdmin) {
	string id, pw, pwre;
	//cout << "\n\tCreate a new account\n\n";
	// Get user id
	while (true) {
		cout << "\n\t" << setw(15) << std::left << "ID " << ": ";
		getline(cin, id);
		// Check if empty string
		if (id.length() == 0) {
			cout << "\n\tID cannot be empty!\n";
			continue;
		}
		// Check if id already exists
		string path = "data/user/" + id;
		if (filesystem::exists(path) && filesystem::is_directory(path)) { // already exists
			cout << "\n\tID unavailable. Looks like someone else is already using it.\n";
			continue;
		} else { // available
			break;
		}
	}
	// Get password
	// We allow empty password for now
	cout << "\n\t" << setw(15) << std::left << "Password " << ": ";
	GetPassword(pw);
	while (true) {
		cout << "\n\t" << setw(15) << std::left << "Password (re) " << ": ";
		GetPassword(pwre);
		if (pw.compare(pwre) == 0) { // Password matches
			break;
		} else { // Wrong password
			cout << "\n\tWrong password! Try again.\n";
		}
	}

	Json::Value account;
	account[KEY_USER_ID] = AnsiToUtf8(id);
	account[KEY_USER_PW] = AnsiToUtf8(pw);
	account[KEY_IS_ADMIN] = isAdmin;

	// Write account info to file
	string accountinfo = "data/user/" + id + "/accountinfo.json";

	// Create directory first if not exists
	filesystem::path path = filesystem::current_path().string() +
		string("/") + accountinfo;
	if (!filesystem::exists(path.parent_path())) {
		try {
			filesystem::create_directories(path.parent_path());
		} catch (std::filesystem::filesystem_error & e) {
			cout << "\n\tFS error:\n";
			cout << e.what() << endl;
			return false;
		}
	}
	// Write to file
	ofstream ofs(accountinfo);
	if (!ofs) {
		cout << "\n\tFailed to open account info file. (" << accountinfo << ")\n";
		return false;
	}
	ofs << account;
	ofs.close();

	return true;
}

// Check user id and password
bool Launcher::Authorize(const string &inputId, const string &inputPw, bool &isAdmin) const {
	// Get user account info 
	const string path = "data/user/" + inputId + "/accountinfo.json";
	ifstream ifs(path);
	if (!ifs || ifs.peek() == EOF) {
		//cout << "\n\tFailed to open account info file. (" << path << ")\n";
		if (ifs.is_open()) {
			ifs.close();
		}
		return false;
	}
	// Get id & password from file
	Json::Value value;
	ifs >> value;
	const string id = Utf8ToAnsi(value.get(KEY_USER_ID, "").asString());
	const string pw = Utf8ToAnsi(value.get(KEY_USER_PW, "").asString());
	// Compare id & password
	if (inputId.compare(id) == 0 && inputPw.compare(pw) == 0) {
		isAdmin = value.get(KEY_IS_ADMIN, false).asBool();
		return true;
	}
	return false;
}

// Get password from keyboard
// Keyboard input is not displayed on console
// while user is typing password. (= echo off)
void Launcher::GetPassword(std::string &pw) const {
	DWORD mode, oldMode;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(handle, &oldMode);
	mode = oldMode;

	// Disable echo
	mode &= ~ENABLE_ECHO_INPUT;
	SetConsoleMode(handle, mode);

	// Get passwod
	getline(cin, pw);
	cout << endl;

	// Restore echo
	SetConsoleMode(handle, oldMode);
}

// Start program with given id
void Launcher::Start(const string &id, const bool isAdmin) {
	Application app;
	app.Run(id, isAdmin);
}

// Set cmd window color scheme
void Launcher::SetConsoleColor() {
	system("color " CONSOLE_COLOR);
}
