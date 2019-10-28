#include "Application.h"

void Application::MenuMain() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t-------- Main Menu ---------------\n\n";

		cout << "\t    1  : Manage music\n";
		cout << "\t    2  : Search music\n";
		cout << "\t    3  : Manage playlists\n";
		cout << "\t    4  : Misc\n\n";

		cout << "\t    0  : Quit\n\n";

		cout << "\t----------------------------------\n\n";

		cout << "\t    Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue;
		}

		switch (command) {
		case 1:
			MenuManage(); break;
		case 2:
			MenuSearch(); break;
		case 3:
			MenuPlaylists(); break;
		case 4:
			MenuMisc(); break;
		case 0:
			Finish(); return;
		default:
			break;
		}
	}
}

void Application::MenuManage() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t-------- Manage Music ------------\n\n";

		cout << "\t    1  : List all music\n";
		cout << "\t    2  : Add music\n";
		cout << "\t    3  : Delete music\n";
		cout << "\t    4  : Replace music\n";
		cout << "\t    5  : Clear music list\n\n";

		cout << "\t    0  : Return to previous menu\n\n";

		cout << "\t----------------------------------\n\n";

		cout << "\t    Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue;
		}

		switch (command) {
		case 1:
			DisplayAllMusic(); break;
		case 2:
			AddMusic(); break;
		case 3:
			DeleteMusic(); break;
		case 4:
			ReplaceMusic(); break;
		case 5:
			MakeEmpty(); break;
		case 0:
			return;
		default:
			break;
		}

		Pause();
	}
}

void Application::MenuSearch() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t-------- Search Music ------------\n\n";

		cout << "\t    1  : Search by ID\n";
		cout << "\t    2  : Search by name\n";
		cout << "\t    3  : Search by artist\n";
		cout << "\t    4  : Search by genre\n\n";

		cout << "\t    0  : Return to previous menu\n\n";

		cout << "\t----------------------------------\n\n";

		cout << "\t    Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue;
		}

		switch (command) {
		case 1:
			SearchById(); break;
		case 2:
			SearchByName(); break;
		case 3:
			SearchByArtist(); break;
		case 4:
			SearchByGenre(); break;
		case 0:
			return;
		default:
			break;
		}

		Pause();
	}
}

void Application::MenuPlaylists() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t-------- Playlists ---------------\n\n";

		cout << "\t    1  : Play music in playlist\n";
		cout << "\t    2  : Add music to playlist\n";
		cout << "\t    3  : Delete music from playlist\n\n";

		cout << "\t    0  : Return to previous menu\n\n";

		cout << "\t----------------------------------\n\n";

		cout << "\t    Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue;
		}

		switch (command) {
		case 1:
			mPlayer.PlayInInsertOrder(); break;
		case 2:
			mPlayer.AddToPlaylist(); break;
		case 3:
			mPlayer.DeleteFromPlaylist(); break;
		case 0:
			return;
		default:
			break;
		}

		Pause();
	}
}

void Application::MenuMisc() {
	return;
}
