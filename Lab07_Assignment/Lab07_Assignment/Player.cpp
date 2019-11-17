#include "Player.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <json/json.h>

#include "Utils.h"

#define PLAYLIST_FILENAME	"files/list_playlist.json"

using namespace std;
using namespace utils;

// 생성사
Player::Player(SortedList<MusicItem> &inList) :
	mInsertOrder(0), mMusicList(inList) {
	ReadPlaylistFromFile(); // 파일로부터 읽어오기
}

// 파괴자
Player::~Player() {
	mPlaylist.MakeEmpty(); // 리스트 초기화
}

// 플레이리스트 항목 나열
void Player::ListPlaylist() {
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tNo item in playlist! Playlist is hungry!\n";
		return;
	}

	MusicItem music; // 마스터리스트에서 받아온 정보가 저장될 변수
	PlaylistItem item; // 플레이리스트에서 받아온 아이템이 저장될 변수
	int num = 1;

	cout << endl;

	// iterator
	SortedDoublyIterator<PlaylistItem> iter(mPlaylist);
	item = iter.Next();
	while (iter.NextNotNull()) {
		music.SetId(item.GetId()); // item의 아이디를 저장
		if (mMusicList.Retrieve(music) != -1) { // 저장된 아이디로 마스터리스트 검색
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

// 특정 곡 골라서 거기서부터 재생
void Player::ChooseAndPlay() {
	// 비어있나?
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tOnly when the playlist is not empty can you play anything!\n";
		return;
	}

	ListPlaylist(); // 리스트 표시

	// 리스트에서 하나 고르라고 물어봄
	int choice = -1;
	while (!(1 <= choice && choice <= mPlaylist.GetLength())) {
		cout << "\n\tSelect a (valid) number from the list: ";
		GetNum(choice);
	}
	// 해당 포지션부터 재생
	PlayFromPosition(choice);
}

// 특정 포지션부터 재생
void Player::PlayFromPosition(int position) {
	PlaylistItem item; // Variable to hold item info from playlist

	SortedDoublyIterator<PlaylistItem> iter(mPlaylist); // Initialize iterator
	for (int i = 0; i < position; ++i) {
		item = iter.Next(); // Get first item from list
	}
	bool keepPlaying = true; // 계속 재생할 지 여부
	while (keepPlaying) {
		if (!iter.PrevNotNull()) {
			// DoublyLinkedList의 시작일 경우.
			cout << "\n\n\tThis is the first item of playlist.\n";
			item = iter.Next(); // Set current pointer to first item
		} else if (!iter.NextNotNull()) {
			// DoublyLinkedList의 마지막. 재생 종료.
			cout << "\n\n\tThis is the end of playlist.\n";
			break;
		}

		Play(item); // 재생

		// 다음에 뭘 재생할 지 묻기
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
			item = iter.Prev(); break; // 이전 곡 재생
		case 2:
			break; // 다시재생
		case 3:
			item = iter.Next(); break; // 다음 곡 재생
		case 0:
		default:
			keepPlaying = false; break; // 재생 종료
		}
	}
}

// 곡 재생, 정보를 표시하는 걸로 대체
void Player::Play(PlaylistItem &item) {
	MusicItem music; // 마스터리스트 검색용
	music.SetId(item.GetId());
	// Search with id and check if music exists in music list
	if (mMusicList.Retrieve(music) != -1) {
		// Music found in list
		music.Play();

		item.IncreasePlayedTimes(); // Increase played count
		mPlaylist.Replace(item); // Apply change to list

		// Get lyrics and display if exists
		mLyricsManager.ShowLyrics(music);

		cout << "\n\n\t       ♬  End of " << music.GetName() << "  ♬\n\n";
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

	PlayFromPosition(1); // 맨 첫 곡부터 재생. 포지션은 인덱스와 다름.
}

// 곡 셔플.
// 기존 플레이리스트에서 앞에서부터 아이템을 하나씩 꺼내서
// primary key인 삽입시간을 랜덤하게 설정하고 새 리스트에 추가함으로써
// 랜덤한 새 리스트를 얻고 해당 리스트를 재생함.
void Player::Shuffle() {
	// 비어있나?
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tPlaylist is empty! Nothing to shuffle!\n";
		return;
	}

	// 기존 플레이리스트 백업용, 셔플리스트용 각각 하나씩 초기화
	SortedDoublyLinkedList<PlaylistItem> bak = mPlaylist, shuffled;
	SortedDoublyIterator<PlaylistItem> iter(mPlaylist); // Iterator
	PlaylistItem origItem; // 기존 마스터리스트에서 꺼내온 정보 저장
	srand(time(0)); // 시드 설정

	// 여태 뽑은 랜덤 숫자를 저장할 리스트.
	// 중복된 랜덤 숫자가 뽑히게 되면 DoublyLinkedList는 같은 아이템으로
	// 판단하여 삽입을 거부함. 따라서 그런 일이 없게 숫자를 뽑을 때마다
	// 해당 숫자가 이 리스트에 존재하는지 확인하여 기존에 뽑은 적 있는
	// 숫자인지를 확인.
	SortedList<int> randoms;

	origItem = iter.Next();
	while (iter.NextNotNull()) {
		// 아이템 갯수의 100배까지 숫자의 범위 안에서 하나 뽑기
		int random = rand() % (mPlaylist.GetLength() * 100);
		// 이미 뽑은적 있는 숫자인가 확인.
		if (randoms.Retrieve(random) != -1) {
			continue; // 다시 뽑자.
		}
		randoms.Add(random); // 뽑은 숫자를 기록하기 위해 리스트에 추가.
		// 새 아이템 생성
		PlaylistItem newItem(origItem.GetId(), 0, to_string(random));
		shuffled.Add(newItem); // 셔플 리스트에 추가
		origItem = iter.Next(); // iter 이동
	}

	mPlaylist = shuffled; // 현재 플레이리스트를 셔플된 걸로 잠시 대체
	PlayFromPosition(1); // 재생
	mPlaylist = bak; // 다시 원래 플레이리스트 복원
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
	string id = item.GetId(); // 삭제할 곡명

	// Iterator
	// 리스트의 Delete를 바로 쓰지 않는 이유는 primary 키가 ID가 아니기 때문.
	SortedDoublyIterator<PlaylistItem> iter(mPlaylist);
	item = iter.Next();
	bool found = false;
	while (iter.NextNotNull()) {
		if (item.GetId().compare(id) == 0) {
			// ID가 일치. 곡 발견.
			found = true;
			iter.Prev(); // 현재 노드는 삭제해야 하므로 포인터 뒤로 한칸 이동.
			mPlaylist.Delete(item); // 삭제
		}
		item = iter.Next();
	}
	if (found) {
		cout << "\n\n\tSuccessfully deleted from list.\n";
	} else {
		cout << "\n\n\tCouldn't find " << item.GetId() << " in list.\n";
	}
}

// 플레이리스트 파일로 저장
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

// 파일로부터 플레이리스트 읽기
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

// 리스트 초기화
void Player::MakeEmpty() {
	mPlaylist.MakeEmpty();
}
