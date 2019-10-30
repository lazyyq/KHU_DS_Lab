#include "Application.h"

void Application::MenuMain() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t忙式式式式式式式式  Main Menu  式式式式式式式式式式式式式式忖\n";
		cout << "\t弛                                   弛\n";
		cout << "\t弛     1  : Manage music             弛\n";
		cout << "\t弛     2  : Search music             弛\n";
		cout << "\t弛     3  : Manage playlists         弛\n";
		cout << "\t弛     4  : Misc                     弛\n";
		cout << "\t弛                                   弛\n";
		cout << "\t弛     9  : Save music data          弛\n";
		cout << "\t弛     0  : Quit                     弛\n";
		cout << "\t弛                                   弛\n";
		cout << "\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n";

		cout << "\t      Choose a command : ";

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
		case 9:
			Save(); Pause();  break;
		case 0:
			Save(); return;
		default:
			break;
		}
	}
}

void Application::MenuManage() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t忙式式式式式式式式  Manage Music  式式式式式式式式式式式式式式式忖\n";
		cout << "\t弛                                       弛\n";
		cout << "\t弛     1  : List all music               弛\n";
		cout << "\t弛     2  : Add music                    弛\n";
		cout << "\t弛     3  : Delete music                 弛\n";
		cout << "\t弛     4  : Update music info            弛\n";
		cout << "\t弛     5  : Clear music list             弛\n";
		cout << "\t弛                                       弛\n";
		cout << "\t弛     0  : Return to previous menu      弛\n";
		cout << "\t弛                                       弛\n";
		cout << "\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n";

		cout << "\t      Choose a command : ";

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
		cout << "\t忙式式式式式式式式  Search Music  式式式式式式式式式式式式式式式忖\n";
		cout << "\t弛                                       弛\n";
		cout << "\t弛     1  : Search by ID                 弛\n";
		cout << "\t弛     2  : Search by name               弛\n";
		cout << "\t弛     3  : Search by artist             弛\n";
		cout << "\t弛     4  : Search by genre              弛\n";
		cout << "\t弛                                       弛\n";
		cout << "\t弛     0  : Return to previous menu      弛\n";
		cout << "\t弛                                       弛\n";
		cout << "\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n";

		cout << "\t      Choose a command : ";

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
		cout << "\t忙式式式式式式式式  Playlists  式式式式式式式式式式式式式式式式式式式式式忖\n";
		cout << "\t弛                                          弛\n";
		cout << "\t弛     1  : List all in playlist            弛\n";
		cout << "\t弛                                          弛\n";
		cout << "\t弛     2  : Choose a music and play         弛\n";
		cout << "\t弛     3  : Play all from the start         弛\n";
		cout << "\t弛     4  : Shuffle                         弛\n";
		cout << "\t弛                                          弛\n";
		cout << "\t弛     5  : Add music to playlist           弛\n";
		cout << "\t弛     6  : Delete music from playlist      弛\n";
		cout << "\t弛     7  : Empty playlist                  弛\n";
		cout << "\t弛                                          弛\n";
		cout << "\t弛     0  : Return to previous menu         弛\n";
		cout << "\t弛                                          弛\n";
		cout << "\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n\n";

		cout << "\t      Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue;
		}

		switch (command) {
		case 1:
			mPlayer.ListPlaylist(); break;
		case 2:
			mPlayer.ChooseAndPlay(); break;
		case 3:
			mPlayer.PlayInInsertOrder(); break;
		case 4:
			mPlayer.Shuffle(); break;
		case 5:
			mPlayer.AddToPlaylist(); break;
		case 6:
			mPlayer.DeleteFromPlaylist(); break;
		case 7:
			mPlayer.MakeEmpty(); break;
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
