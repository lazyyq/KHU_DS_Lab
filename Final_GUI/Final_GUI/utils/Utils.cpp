#include "Utils.h"

#include <algorithm>

// Clear console.
void utils::Clear() {
	system("cls");
}

// Pause console.
void utils::Pause() {
	Pause("\n\tPress any key to continue.\n");
}

// Display message and pause console.
void utils::Pause(const std::string &message) {
	std::cout << message;
	system("pause >nul");
}

// Get number from keyboard input
int utils::GetNum(int &n) {
	int result = 1, input;

	std::cin >> input;
	if (std::cin.fail() == 1) { // Error, input is probably not int
		std::cin.clear(); // Clear fail flags
		result = 0; // We return 0 on failure
	} else {
		// We should not cin directly to n because
		// bad input such as char is recognized as 0,
		// which might be considered a valid number
		// by the function that called GetNum(n).
		n = input;
	}
	std::cin.ignore(100, '\n'); // Ignore buffer until '\n'

	return result;
}

// Convert characters in string to lower case.
std::string utils::ToLowerCase(const std::string &str) {
	std::string converted = str;
	std::transform(converted.begin(), converted.end(), converted.begin(), tolower);
	return converted;
}
