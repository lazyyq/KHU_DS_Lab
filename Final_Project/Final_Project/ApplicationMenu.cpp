#include "Application.h"

#include "menu/MenuScreen.h"
#include "Utils.h"

using namespace std;
using namespace utils;

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
			Save(); Pause(); break; // ����Ʈ�� ���Ͽ� ����
		case 6:
			Save(); return; // �����ϰ� ���α׷� ����
		}
	}
}

void Application::MenuManage() {
	const string title = "Manage Music";
	const string menus[] = {
		"List all music",
		"Add music",
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
			DisplayAllMusic(); Pause(); break; // ��� �� ���� ǥ��
		case 2:
			MenuAddMusic(); break; // �� �߰� �޴� ǥ��
		case 3:
			DeleteMusic(); Pause(); break; // �� ����
		case 4:
			ReplaceMusic(); Pause(); break; // �� ���� ������Ʈ(��ü)
		case 5:
			MakeEmpty(); Pause(); break; // �� ����Ʈ, ��������Ʈ, �帣 ����Ʈ, �÷��̸���Ʈ ���� �ʱ�ȭ
		case 7:
			return;
		}
	}
}

void Application::MenuAddMusic() {
	const string title = "Manage Music";
	const string menus[] = {
		"Add music manually",
		"Add music from file",
		"Add music from folder",
		"",
		"Return to previous menu",
	};

	MenuScreen menu(title, begin(menus), end(menus));

	while (true) {
		switch (menu.GetSelection()) {
		case 1:
			AddMusicManually(); Pause(); break; // �� ������ ���� �Է��Ͽ� �߰�
		case 2:
			AddMusicFromFile(); Pause(); break; // MP3 ���Ͽ��� �� ���� �߰�
		case 3:
			AddMusicFromFolder(); Pause(); break; // ���� ���� MP3 ���Ͽ��� �� ���� �߰�
		case 5:
			return;
		}
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
			SearchById(); Pause(); break; // ID�� �� �˻�
		case 2:
			SearchByName(); Pause(); break; // �� �̸����� �˻�
		case 3:
			SearchByArtist(); Pause(); break; // ���� �̸����� �˻�
		case 4:
			SearchByGenre(); Pause(); break; // �帣 �̸����� �˻�
		case 6:
			return;
		}
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
			mPlayer.ListPlaylist(); Pause(); break; // �÷��̸���Ʈ�� �� ���� �� ǥ��
		case 3:
			mPlayer.ChooseAndPlay(); Pause(); break; // �÷��̸���Ʈ���� ��� ���
		case 4:
			mPlayer.PlayInInsertOrder(); Pause(); break; // �� ó�� ����� ���
		case 5:
			mPlayer.Shuffle(); Pause(); break; // �������� ��� ���
		case 7:
			mPlayer.AddToPlaylist(); Pause(); break; // �÷��̸���Ʈ�� �� �߰�
		case 8:
			mPlayer.DeleteFromPlaylist(); Pause(); break; // �÷��̸���Ʈ���� �� ����
		case 9:
			mPlayer.MakeEmpty(); Pause(); break; // �÷��̸���Ʈ �ʱ�ȭ
		case 11:
			return;
		}
	}
}

// �� ��������� ��� �ȳ�
//void Application::MenuMisc() {
//	return;
//}
