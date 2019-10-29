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

// Add music to playlist.
void Player::AddToPlaylist() {
	MusicItem music; // Temporary variable to hold info

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
	PlaylistItem playItem; // Variable to hold item info from playlist
	MusicItem musicItem; // Variable to hold info from music list

	// Check if playlist is empty
	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tList is empty.\n";
		return;
	}

	bool keepPlaying = true;
	while (keepPlaying) { // Loop until user wants to stop repeating playlist
		// Play all items from playlist
		DoublyIterator<PlaylistItem> iter(mPlaylist); // Initialize iterator
		playItem = iter.Next(); // Get first item from list
		while (iter.NextNotNull()) {
			musicItem.SetId(playItem.GetId());
			// Search with id and check if music exists in music list
			if (mMusicList.Retrieve(musicItem) != -1) {
				// Music found in list, play
				cout << musicItem;
				playItem.IncreasePlayedTimes(); // Increase played count
				mPlaylist.Replace(playItem); // Apply change to list

				// Get lyrics and display if exists
				mLyricsManager.ShowLyrics(musicItem);
			} else {
				// Music not found
				cout << "\n\n\tMusic \"" << musicItem.GetName()
					<< "\" does not exist. Skipping.\n";
			}
			playItem = iter.Next();
		}

		// Check whether to repeat or not
		int playAgain = -1;
		while (!((playAgain == 0) || (playAgain == 1))) {
			cout << "\n\n\tEnd of playlist. Play again? (1: yes / 0: no): ";
			// If input is not integer, ask again.
			if (!GetNum(playAgain)) {
				continue;
			}
		}
		if (playAgain == 0) { // Stop playing
			keepPlaying = false;
		}
	}
}

// Delete music from playlist
void Player::DeleteFromPlaylist() {
	PlaylistItem playItem; // Temporary variable to hold id info

	playItem.SetIdFromKB(); // Get id to search from playlist

	mPlaylist.Delete(playItem);
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
