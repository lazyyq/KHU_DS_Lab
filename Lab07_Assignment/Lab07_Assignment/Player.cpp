#include "Player.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <json/json.h>

#include "Utils.h"

#define PLAYLIST_FILENAME	"files/list_playlist.json"

using namespace std;
using namespace utils;

// ������
Player::Player(SortedList<MusicItem> &inList) :
	mInsertOrder(0), mMusicList(inList) {
	ReadPlaylistFromFile(); // ���Ϸκ��� �о����
}

// �ı���
Player::~Player() {
	mPlaylist.MakeEmpty(); // ����Ʈ �ʱ�ȭ
}

// �÷��̸���Ʈ �׸� ����
void Player::ListPlaylist() {
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tNo item in playlist! Playlist is hungry!\n";
		return;
	}

	MusicItem music; // �����͸���Ʈ���� �޾ƿ� ������ ����� ����
	PlaylistItem item; // �÷��̸���Ʈ���� �޾ƿ� �������� ����� ����
	int num = 1;

	cout << endl;

	// iterator
	SortedDoublyIterator<PlaylistItem> iter(mPlaylist);
	item = iter.Next();
	while (iter.NextNotNull()) {
		music.SetId(item.GetId()); // item�� ���̵� ����
		if (mMusicList.Retrieve(music) != -1) { // ����� ���̵�� �����͸���Ʈ �˻�
			// Music found in music list
			cout << "\n\t#" << num++ << " \"" << music.GetName()
				<< "\" by " << music.GetArtist() << endl
				<< "\t\t- ID: \"" << item.GetId() << "\"\n"
				<< "\t\t- Played " << item.GetPlayedTimes() << " times\n";
		}
		item = iter.Next();
	}
	cout << endl;
}

// Ư�� �� ��� �ű⼭���� ���
void Player::ChooseAndPlay() {
	// ����ֳ�?
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tOnly when the playlist is not empty can you play anything!\n";
		return;
	}

	ListPlaylist(); // ����Ʈ ǥ��

	// ����Ʈ���� �ϳ� ����� ���
	int choice = -1;
	while (!(1 <= choice && choice <= mPlaylist.GetLength())) {
		cout << "\n\tSelect a (valid) number from the list: ";
		GetNum(choice);
	}
	// �ش� �����Ǻ��� ���
	PlayFromPosition(choice);
}

// Ư�� �����Ǻ��� ���
void Player::PlayFromPosition(int position) {
	PlaylistItem item; // Variable to hold item info from playlist

	SortedDoublyIterator<PlaylistItem> iter(mPlaylist); // Initialize iterator
	for (int i = 0; i < position; ++i) {
		item = iter.Next(); // Get first item from list
	}
	bool keepPlaying = true; // ��� ����� �� ����
	while (keepPlaying) {
		if (!iter.PrevNotNull()) {
			// DoublyLinkedList�� ������ ���.
			cout << "\n\n\tThis is the first item of playlist.\n";
			item = iter.Next(); // Set current pointer to first item
		} else if (!iter.NextNotNull()) {
			// DoublyLinkedList�� ������. ��� ����.
			cout << "\n\n\tThis is the end of playlist.\n";
			break;
		}

		Play(item); // ���

		// ������ �� ����� �� ����
		int choice = -1;
		while (!(0 <= choice && choice <= 3)) {
			cout << "\n\tWhat would you like to play next? \n"
				<< "\t(1: Previous / 2: Replay / 3: Next / "
				<< "0: Stop playing): ";
			if (!GetNum(choice)) {
				continue;
			}
		}
		switch (choice) {
		case 1:
			item = iter.Prev(); break; // ���� �� ���
		case 2:
			break; // �ٽ����
		case 3:
			item = iter.Next(); break; // ���� �� ���
		case 0:
		default:
			keepPlaying = false; break; // ��� ����
		}
	}
}

// �� ���, ������ ǥ���ϴ� �ɷ� ��ü
void Player::Play(PlaylistItem &item) {
	MusicItem music; // �����͸���Ʈ �˻���
	music.SetId(item.GetId());
	// Search with id and check if music exists in music list
	if (mMusicList.Retrieve(music) != -1) {
		// Music found in list
		music.Play();

		item.IncreasePlayedTimes(); // Increase played count
		mPlaylist.Replace(item); // Apply change to list

		// Get lyrics and display if exists
		mLyricsManager.ShowLyrics(music);

		cout << "\n\n\t       ��  End of " << music.GetName() << "  ��\n\n";
	} else {
		// Music not found
		cout << "\n\n\tMusic \"" << music.GetName()
			<< "\" does not exist. Skipping.\n";
	}
}

// Add music to playlist.
void Player::AddToPlaylist() {
	MusicItem music; // Temporary variable to hold info

	cout << endl;
	music.SetIdFromKB(); // Get id to search
	if (mMusicList.Retrieve(music) != -1) { // Check if music exists in list
		// Music exists
		// Create a music item to put in playlist
		PlaylistItem playItem(music.GetId());
		mPlaylist.Add(playItem); // Add to playlist
		cout << "\n\n\tAdded music \"" << music.GetId() << "\" to playlist.\n";
	} else {
		cout << "\n\n\tMusic does not exist in list, aborting.\n";
	}
}

// Play music from playlist in order.
void Player::PlayInInsertOrder() {
	// Check if playlist is empty
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tList is empty.\n";
		return;
	}

	PlayFromPosition(1); // �� ù ����� ���. �������� �ε����� �ٸ�.
}

// �� ����.
// ���� �÷��̸���Ʈ���� �տ������� �������� �ϳ��� ������
// primary key�� ���Խð��� �����ϰ� �����ϰ� �� ����Ʈ�� �߰������ν�
// ������ �� ����Ʈ�� ��� �ش� ����Ʈ�� �����.
void Player::Shuffle() {
	// ����ֳ�?
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tPlaylist is empty! Nothing to shuffle!\n";
		return;
	}

	// ���� �÷��̸���Ʈ �����, ���ø���Ʈ�� ���� �ϳ��� �ʱ�ȭ
	SortedDoublyLinkedList<PlaylistItem> bak = mPlaylist, shuffled;
	SortedDoublyIterator<PlaylistItem> iter(mPlaylist); // Iterator
	PlaylistItem origItem; // ���� �����͸���Ʈ���� ������ ���� ����
	srand(time(0)); // �õ� ����

	// ���� ���� ���� ���ڸ� ������ ����Ʈ.
	// �ߺ��� ���� ���ڰ� ������ �Ǹ� DoublyLinkedList�� ���� ����������
	// �Ǵ��Ͽ� ������ �ź���. ���� �׷� ���� ���� ���ڸ� ���� ������
	// �ش� ���ڰ� �� ����Ʈ�� �����ϴ��� Ȯ���Ͽ� ������ ���� �� �ִ�
	// ���������� Ȯ��.
	SortedList<int> randoms;

	origItem = iter.Next();
	while (iter.NextNotNull()) {
		// ������ ������ 100����� ������ ���� �ȿ��� �ϳ� �̱�
		int random = rand() % (mPlaylist.GetLength() * 100);
		// �̹� ������ �ִ� �����ΰ� Ȯ��.
		if (randoms.Retrieve(random) != -1) {
			continue; // �ٽ� ����.
		}
		randoms.Add(random); // ���� ���ڸ� ����ϱ� ���� ����Ʈ�� �߰�.
		// �� ������ ����
		PlaylistItem newItem(origItem.GetId(), 0, to_string(random));
		shuffled.Add(newItem); // ���� ����Ʈ�� �߰�
		origItem = iter.Next(); // iter �̵�
	}

	mPlaylist = shuffled; // ���� �÷��̸���Ʈ�� ���õ� �ɷ� ��� ��ü
	PlayFromPosition(1); // ���
	mPlaylist = bak; // �ٽ� ���� �÷��̸���Ʈ ����
}

// Delete music from playlist
void Player::DeleteFromPlaylist() {
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tPlaylist is empty!\n"
			<< "\tMaybe you should add anything before deleting.\n";
		return;
	}
	PlaylistItem item; // Temporary variable to hold info

	cout << endl;
	item.SetIdFromKB(); // Get id to search from playlist
	string id = item.GetId(); // ������ ���

	// Iterator
	// ����Ʈ�� Delete�� �ٷ� ���� �ʴ� ������ primary Ű�� ID�� �ƴϱ� ����.
	SortedDoublyIterator<PlaylistItem> iter(mPlaylist);
	item = iter.Next();
	bool found = false;
	while (iter.NextNotNull()) {
		if (item.GetId().compare(id) == 0) {
			// ID�� ��ġ. �� �߰�.
			found = true;
			iter.Prev(); // ���� ���� �����ؾ� �ϹǷ� ������ �ڷ� ��ĭ �̵�.
			mPlaylist.Delete(item); // ����
		}
		item = iter.Next();
	}
	if (found) {
		cout << "\n\n\tSuccessfully deleted from list.\n";
	} else {
		cout << "\n\n\tCouldn't find " << item.GetId() << " in list.\n";
	}
}

// �÷��̸���Ʈ ���Ϸ� ����
int Player::SavePlaylistToFile() {
	ofstream ofs(PLAYLIST_FILENAME); //Open file
	if (!ofs) {
		return 0;
	}

	cout << "\n\tSaving playlist..\n";

	// Put each data to JSON
	Json::Value root;
	SortedDoublyIterator<PlaylistItem> iter(mPlaylist);
	for (PlaylistItem data = iter.Next();
		iter.NextNotNull(); data = iter.Next()) {
		root << data;
	}
	ofs << root; // Write to file

	ofs.close();

	return 1;
}

// ���Ϸκ��� �÷��̸���Ʈ �б�
int Player::ReadPlaylistFromFile() {
	ifstream ifs(PLAYLIST_FILENAME);
	if (!ifs) {
		return 0;
	}

	Json::Value root;
	PlaylistItem data;

	// Convert each value to PlaylistItem
	ifs >> root;
	for (auto &value : root) {
		value >> data;
		mPlaylist.Add(data);
	}

	ifs.close();

	return 1;
}

// ����Ʈ �ʱ�ȭ
void Player::MakeEmpty() {
	mPlaylist.MakeEmpty();
}
