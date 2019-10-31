#include "Application.h"

// Main menu
void Application::MenuMain() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t┌────────  Main Menu  ───────────────────┐\n";
		cout << "\t│                                        │\n";
		cout << "\t│     1  : Manage music                  │\n";
		cout << "\t│     2  : Search music                  │\n";
		cout << "\t│     3  : Play & Manage playlists       │\n";
		cout << "\t│                                        │\n";
		cout << "\t│     9  : Save music data               │\n";
		cout << "\t│     0  : Quit                          │\n";
		cout << "\t│                                        │\n";
		cout << "\t└────────────────────────────────────────┘\n\n";

		cout << "\t      Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue; // Show this menu again if input is not number
		}

		switch (command) {
		case 1:
			MenuManage(); break; // Show menu for mananing music list
		case 2:
			MenuSearch(); break; // Show menu for searching music
		case 3:
			MenuPlaylists(); break; // Show menu for playing & managning playlist.
		//case 4:
		//	MenuMisc(); break;
		case 9:
			Save(); Pause();  break; // 리스트를 파일에 저장
		case 0:
			Save(); return; // 저장하고 프로그램 종료
		default:
			break;
		}
	}
}

void Application::MenuManage() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t┌────────  Manage Music  ───────────────┐\n";
		cout << "\t│                                       │\n";
		cout << "\t│     1  : List all music               │\n";
		cout << "\t│     2  : Add music                    │\n";
		cout << "\t│     3  : Delete music                 │\n";
		cout << "\t│     4  : Update music info            │\n";
		cout << "\t│     5  : Clear music list             │\n";
		cout << "\t│                                       │\n";
		cout << "\t│     0  : Return to previous menu      │\n";
		cout << "\t│                                       │\n";
		cout << "\t└───────────────────────────────────────┘\n\n";

		cout << "\t      Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue; // 인풋이 숫자가 아니면 이 메뉴 다시 표시
		}

		switch (command) {
		case 1:
			DisplayAllMusic(); break; // 모든 곡 정보 표시
		case 2:
			AddMusic(); break; // 곡 추가
		case 3:
			DeleteMusic(); break; // 곡 삭제
		case 4:
			ReplaceMusic(); break; // 곡 정보 업데이트(교체)
		case 5:
			MakeEmpty(); break; // 곡 리스트, 가수리스트, 장르 리스트, 플레이리스트 전부 초기화
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
		cout << "\t┌────────  Search Music  ───────────────┐\n";
		cout << "\t│                                       │\n";
		cout << "\t│     1  : Search by ID                 │\n";
		cout << "\t│     2  : Search by name               │\n";
		cout << "\t│     3  : Search by singer (artist)    │\n";
		cout << "\t│     4  : Search by genre              │\n";
		cout << "\t│                                       │\n";
		cout << "\t│     0  : Return to previous menu      │\n";
		cout << "\t│                                       │\n";
		cout << "\t└───────────────────────────────────────┘\n\n";

		cout << "\t      Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue; // 인풋이 숫자가 아니면 메뉴 다시 표시
		}

		switch (command) {
		case 1:
			SearchById(); break; // ID로 곡 검색
		case 2:
			SearchByName(); break; // 곡 이름으로 검색
		case 3:
			SearchByArtist(); break; // 가수 이름으로 검색
		case 4:
			SearchByGenre(); break; // 장르 이름으로 검색
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
		cout << "\t┌────────  Playlists  ─────────────────────┐\n";
		cout << "\t│                                          │\n";
		cout << "\t│     1  : List all in playlist            │\n";
		cout << "\t│                                          │\n";
		cout << "\t│     2  : Choose a music and play         │\n";
		cout << "\t│     3  : Play all from the start         │\n";
		cout << "\t│     4  : Shuffle                         │\n";
		cout << "\t│                                          │\n";
		cout << "\t│     5  : Add music to playlist           │\n";
		cout << "\t│     6  : Delete music from playlist      │\n";
		cout << "\t│     7  : Empty playlist                  │\n";
		cout << "\t│                                          │\n";
		cout << "\t│     0  : Return to previous menu         │\n";
		cout << "\t│                                          │\n";
		cout << "\t└──────────────────────────────────────────┘\n\n";

		cout << "\t      Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue; // 인풋이 숫자가 아니면 메뉴 다시표시
		}

		switch (command) {
		case 1:
			mPlayer.ListPlaylist(); break; // 플레이리스트의 곡 정보 다 표시
		case 2:
			mPlayer.ChooseAndPlay(); break; // 플레이리스트에서 골라서 재생
		case 3:
			mPlayer.PlayInInsertOrder(); break; // 맨 처음 곡부터 재생
		case 4:
			mPlayer.Shuffle(); break; // 랜덤으로 섞어서 재생
		case 5:
			mPlayer.AddToPlaylist(); break; // 플레이리스트에 곡 추가
		case 6:
			mPlayer.DeleteFromPlaylist(); break; // 플레이리스트에서 곡 삭제
		case 7:
			mPlayer.MakeEmpty(); break; // 플레이리스트 초기화
		case 0:
			return;
		default:
			break;
		}

		Pause();
	}
}

// 왜 만들었는지 기억 안남
//void Application::MenuMisc() {
//	return;
//}
