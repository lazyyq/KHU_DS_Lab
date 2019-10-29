#include "Player.h"

Player::Player(SortedList<MusicItem> &inList) :
	mInsertOrder(0), mMusicList(inList) {
	ReadPlaylistFromFile();
}

Player::~Player() {
	mPlaylist.MakeEmpty();
}

int Player::GetNum(int &n) {
	int result = 1, input;

	cin >> input;
	if (cin.fail() == 1) { // Error, input is probably not int
		cin.clear(); // Clear fail flags
		result = 0; // We return 0 on failure
	} else {
		// We should not cin directly to n because
		// bad input such as char is recognized as 0,
		// which might be considered a valid number
		// by the function that called GetNum(n).
		n = input;
	}
	cin.ignore(100, '\n');

	return result;
}

void Player::Play(PlaylistItem &item) {
	MusicItem music;
	music.SetId(item.GetId());
	// Search with id and check if music exists in music list
	if (mMusicList.Retrieve(music) != -1) {
		// Music found in list
		music.Play();

		item.IncreasePlayedTimes(); // Increase played count
		mPlaylist.Replace(item); // Apply change to list

		// Get lyrics and display if exists
		mLyricsManager.ShowLyrics(music);
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
	PlaylistItem item; // Variable to hold item info from playlist

	// Check if playlist is empty
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tList is empty.\n";
		return;
	}

	DoublyIterator<PlaylistItem> iter(mPlaylist); // Initialize iterator
	item = iter.Next(); // Get first item from list
	bool keepPlaying = true;
	while (keepPlaying) {
		if (!iter.PrevNotNull()) {
			cout << "\n\n\tThis is the first item of playlist.\n";
			item = iter.Next(); // Set current pointer to first item
		} else if (!iter.NextNotNull()) {
			cout << "\n\n\tThis is the end of playlist.\n";
			break;
		}

		Play(item);

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
			item = iter.Prev(); break;
		case 2:
			break;
		case 3:
			item = iter.Next(); break;
		case 0:
		default:
			keepPlaying = false; break;
		}
	}
}

// Delete music from playlist
void Player::DeleteFromPlaylist() {
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tPlaylist is empty!\n"
			<< "\tMaybe you should add anything before deleting.\n";
		return;
	}
	PlaylistItem playItem; // Temporary variable to hold id info

	cout << endl;
	playItem.SetIdFromKB(); // Get id to search from playlist

	if (mPlaylist.Delete(playItem)) {
		cout << "\n\n\tSuccessfully deleted from list.\n";
	} else {
		cout << "\n\n\tCouldn't find "<<playItem.GetId()<<" in list.\n";
	}
}

int Player::SavePlaylistToFile() {
	PlaylistItem data; // Temporary variable to hold info from list

	ofstream ofs(PLAYLIST_FILENAME); //Open file
	if (!ofs) { //Open failed
		return 0;
	}

	cout << "\n\tSaving playlist..\n";

	DoublyIterator<PlaylistItem> iter(mPlaylist);
	data = iter.Next();
	while (iter.NextNotNull()) {
		ofs << data;
		data = iter.Next();
	}
	ofs.close();

	return 1;
}

int Player::ReadPlaylistFromFile() {
	PlaylistItem data; // Temporary variable to hold info from file

	ifstream ifs(PLAYLIST_FILENAME); // Open file
	if (!ifs || ifs.peek() == EOF) { // Failed to open or file is empty
		return 0;
	}

	while (!ifs.eof()) {
		ifs >> data; // Load data from file
		mPlaylist.Add(data); // Add to list
	}
	ifs.close(); // Close file

	return 1;
}

void Player::MakeEmpty() {
	mPlaylist.MakeEmpty();
}
