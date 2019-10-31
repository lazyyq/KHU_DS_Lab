#include "Utils.h"

using namespace std;

// Clear console.
void utils::Clear() {
	system("cls");
}

// Pause console.
void utils::Pause() {
	Pause("\n\tPress any key to continue.\n");
}

// Display message and pause console.
void utils::Pause(const string &message) {
	cout << message;
	system("pause >nul");
}

// Get number from keyboard input
int utils::GetNum(int &n) {
	int result = 1, input;

	cin >> input;
	if (cin.fail() == 1) { // Error, input is probably not int
		cin.clear(); // Clear fail flags
		result = 0; // We return 0 on failure
	} else {
		// We should not cin directly to n because
		// bad input such as char is recognized as 0,
		// which might be considered a valid number
		// by the function that called GetNum(n).
		n = input;
	}
	cin.ignore(100, '\n'); // Ignore buffer until '\n'

	return result;
}
