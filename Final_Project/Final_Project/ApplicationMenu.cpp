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
			Save(); Pause();  break; // ����Ʈ�� ���Ͽ� ����
		case 6:
			Save(); return; // �����ϰ� ���α׷� ����
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
			DisplayAllMusic(); break; // ��� �� ���� ǥ��
		case 2:
			AddMusicManually(); break; // �� �߰�
		case 3:
			DeleteMusic(); break; // �� ����
		case 4:
			ReplaceMusic(); break; // �� ���� ������Ʈ(��ü)
		case 5:
			MakeEmpty(); break; // �� ����Ʈ, ��������Ʈ, �帣 ����Ʈ, �÷��̸���Ʈ ���� �ʱ�ȭ
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
			SearchById(); break; // ID�� �� �˻�
		case 2:
			SearchByName(); break; // �� �̸����� �˻�
		case 3:
			SearchByArtist(); break; // ���� �̸����� �˻�
		case 4:
			SearchByGenre(); break; // �帣 �̸����� �˻�
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
			mPlayer.ListPlaylist(); break; // �÷��̸���Ʈ�� �� ���� �� ǥ��
		case 3:
			mPlayer.ChooseAndPlay(); break; // �÷��̸���Ʈ���� ��� ���
		case 4:
			mPlayer.PlayInInsertOrder(); break; // �� ó�� ����� ���
		case 5:
			mPlayer.Shuffle(); break; // �������� ��� ���
		case 7:
			mPlayer.AddToPlaylist(); break; // �÷��̸���Ʈ�� �� �߰�
		case 8:
			mPlayer.DeleteFromPlaylist(); break; // �÷��̸���Ʈ���� �� ����
		case 9:
			mPlayer.MakeEmpty(); break; // �÷��̸���Ʈ �ʱ�ȭ
		case 11:
			return;
		default:
			continue;
		}

		Pause();
	}
}

// �� ��������� ��� �ȳ�
//void Application::MenuMisc() {
//	return;
//}
