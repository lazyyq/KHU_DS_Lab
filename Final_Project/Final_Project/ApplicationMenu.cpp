#include "Application.h"
#include "menu/MenuScreen.h"

// Main menu
void Application::MenuMain() {
	const string title = "Main Menu";
	const string menus[] = {
		"Manage music",
		"Search music",
		"Play & Manage playlists",
		"",
		"Save music data",
		"Save and quit",
	};

	MenuScreen menu(title, begin(menus), end(menus));

	while (true) {
		switch (menu.GetSelection()) {
		case 1:
			MenuManage(); break; // Show menu for mananing music list
		case 2:
			MenuSearch(); break; // Show menu for searching music
		case 3:
			MenuPlaylists(); break; // Show menu for playing & managning playlist.
		case 5:
			Save(); Pause();  break; // 리스트를 파일에 저장
		case 6:
			Save(); return; // 저장하고 프로그램 종료
		default:
			break;
		}
	}
}

void Application::MenuManage() {
	const string title = "Manage Music";
	const string menus[] = {
		"List all music",
		"Add music manually",
		"Delete music",
		"Update music info",
		"Clear music list",
		"",
		"Return to previous menu",
	};

	MenuScreen menu(title, begin(menus), end(menus));

	while (true) {
		switch (menu.GetSelection()) {
		case 1:
			DisplayAllMusic(); break; // 모든 곡 정보 표시
		case 2:
			AddMusicManually(); break; // 곡 추가
		case 3:
			DeleteMusic(); break; // 곡 삭제
		case 4:
			ReplaceMusic(); break; // 곡 정보 업데이트(교체)
		case 5:
			MakeEmpty(); break; // 곡 리스트, 가수리스트, 장르 리스트, 플레이리스트 전부 초기화
		case 7:
			return;
		default:
			continue;
		}

		Pause();
	}
}

void Application::MenuSearch() {
	const string title = "Search Music";
	const string menus[] = {
		"Search by ID",
		"Search by name",
		"Search by singer(artist)",
		"Search by genre",
		"",
		"Return to previous menu",
	};

	MenuScreen menu(title, begin(menus), end(menus));

	while (true) {
		switch (menu.GetSelection()) {
		case 1:
			SearchById(); break; // ID로 곡 검색
		case 2:
			SearchByName(); break; // 곡 이름으로 검색
		case 3:
			SearchByArtist(); break; // 가수 이름으로 검색
		case 4:
			SearchByGenre(); break; // 장르 이름으로 검색
		case 6:
			return;
		default:
			continue;
		}

		Pause();
	}
}

void Application::MenuPlaylists() {
	const string title = "Playlists";
	const string menus[] = {
		"List all in playlist",
		"",
		"Choose a music andplay",
		"Play all from the start",
		"Shuffle",
		"",
		"Add music to playlist",
		"Delete music from playlist",
		"Empty playlist",
		"",
		"Return to previous menu",
	};

	MenuScreen menu(title, begin(menus), end(menus));

	while (true) {
		switch (menu.GetSelection()) {
		case 1:
			mPlayer.ListPlaylist(); break; // 플레이리스트의 곡 정보 다 표시
		case 3:
			mPlayer.ChooseAndPlay(); break; // 플레이리스트에서 골라서 재생
		case 4:
			mPlayer.PlayInInsertOrder(); break; // 맨 처음 곡부터 재생
		case 5:
			mPlayer.Shuffle(); break; // 랜덤으로 섞어서 재생
		case 7:
			mPlayer.AddToPlaylist(); break; // 플레이리스트에 곡 추가
		case 8:
			mPlayer.DeleteFromPlaylist(); break; // 플레이리스트에서 곡 삭제
		case 9:
			mPlayer.MakeEmpty(); break; // 플레이리스트 초기화
		case 11:
			return;
		default:
			continue;
		}

		Pause();
	}
}

// 왜 만들었는지 기억 안남
//void Application::MenuMisc() {
//	return;
//}
