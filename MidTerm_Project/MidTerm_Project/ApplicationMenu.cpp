#include "Application.h"

// Main menu
void Application::MenuMain() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t������������������  Main Menu  ����������������������������������������\n";
		cout << "\t��                                        ��\n";
		cout << "\t��     1  : Manage music                  ��\n";
		cout << "\t��     2  : Search music                  ��\n";
		cout << "\t��     3  : Play & Manage playlists       ��\n";
		cout << "\t��                                        ��\n";
		cout << "\t��     9  : Save music data               ��\n";
		cout << "\t��     0  : Quit                          ��\n";
		cout << "\t��                                        ��\n";
		cout << "\t������������������������������������������������������������������������������������\n\n";

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
			Save(); Pause();  break; // ����Ʈ�� ���Ͽ� ����
		case 0:
			Save(); return; // �����ϰ� ���α׷� ����
		default:
			break;
		}
	}
}

void Application::MenuManage() {
	while (true) {
		Clear();
		cout << endl << endl << endl;
		cout << "\t������������������  Manage Music  ��������������������������������\n";
		cout << "\t��                                       ��\n";
		cout << "\t��     1  : List all music               ��\n";
		cout << "\t��     2  : Add music                    ��\n";
		cout << "\t��     3  : Delete music                 ��\n";
		cout << "\t��     4  : Update music info            ��\n";
		cout << "\t��     5  : Clear music list             ��\n";
		cout << "\t��                                       ��\n";
		cout << "\t��     0  : Return to previous menu      ��\n";
		cout << "\t��                                       ��\n";
		cout << "\t����������������������������������������������������������������������������������\n\n";

		cout << "\t      Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue; // ��ǲ�� ���ڰ� �ƴϸ� �� �޴� �ٽ� ǥ��
		}

		switch (command) {
		case 1:
			DisplayAllMusic(); break; // ��� �� ���� ǥ��
		case 2:
			AddMusic(); break; // �� �߰�
		case 3:
			DeleteMusic(); break; // �� ����
		case 4:
			ReplaceMusic(); break; // �� ���� ������Ʈ(��ü)
		case 5:
			MakeEmpty(); break; // �� ����Ʈ, ��������Ʈ, �帣 ����Ʈ, �÷��̸���Ʈ ���� �ʱ�ȭ
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
		cout << "\t������������������  Search Music  ��������������������������������\n";
		cout << "\t��                                       ��\n";
		cout << "\t��     1  : Search by ID                 ��\n";
		cout << "\t��     2  : Search by name               ��\n";
		cout << "\t��     3  : Search by singer (artist)    ��\n";
		cout << "\t��     4  : Search by genre              ��\n";
		cout << "\t��                                       ��\n";
		cout << "\t��     0  : Return to previous menu      ��\n";
		cout << "\t��                                       ��\n";
		cout << "\t����������������������������������������������������������������������������������\n\n";

		cout << "\t      Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue; // ��ǲ�� ���ڰ� �ƴϸ� �޴� �ٽ� ǥ��
		}

		switch (command) {
		case 1:
			SearchById(); break; // ID�� �� �˻�
		case 2:
			SearchByName(); break; // �� �̸����� �˻�
		case 3:
			SearchByArtist(); break; // ���� �̸����� �˻�
		case 4:
			SearchByGenre(); break; // �帣 �̸����� �˻�
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
		cout << "\t������������������  Playlists  ��������������������������������������������\n";
		cout << "\t��                                          ��\n";
		cout << "\t��     1  : List all in playlist            ��\n";
		cout << "\t��                                          ��\n";
		cout << "\t��     2  : Choose a music and play         ��\n";
		cout << "\t��     3  : Play all from the start         ��\n";
		cout << "\t��     4  : Shuffle                         ��\n";
		cout << "\t��                                          ��\n";
		cout << "\t��     5  : Add music to playlist           ��\n";
		cout << "\t��     6  : Delete music from playlist      ��\n";
		cout << "\t��     7  : Empty playlist                  ��\n";
		cout << "\t��                                          ��\n";
		cout << "\t��     0  : Return to previous menu         ��\n";
		cout << "\t��                                          ��\n";
		cout << "\t����������������������������������������������������������������������������������������\n\n";

		cout << "\t      Choose a command : ";

		int command;
		if (!GetNum(command)) {
			continue; // ��ǲ�� ���ڰ� �ƴϸ� �޴� �ٽ�ǥ��
		}

		switch (command) {
		case 1:
			mPlayer.ListPlaylist(); break; // �÷��̸���Ʈ�� �� ���� �� ǥ��
		case 2:
			mPlayer.ChooseAndPlay(); break; // �÷��̸���Ʈ���� ��� ���
		case 3:
			mPlayer.PlayInInsertOrder(); break; // �� ó�� ����� ���
		case 4:
			mPlayer.Shuffle(); break; // �������� ��� ���
		case 5:
			mPlayer.AddToPlaylist(); break; // �÷��̸���Ʈ�� �� �߰�
		case 6:
			mPlayer.DeleteFromPlaylist(); break; // �÷��̸���Ʈ���� �� ����
		case 7:
			mPlayer.MakeEmpty(); break; // �÷��̸���Ʈ �ʱ�ȭ
		case 0:
			return;
		default:
			break;
		}

		Pause();
	}
}

// �� ��������� ��� �ȳ�
//void Application::MenuMisc() {
//	return;
//}
