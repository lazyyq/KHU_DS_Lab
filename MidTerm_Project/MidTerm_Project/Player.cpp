#include "Player.h"

Player::Player() {
	mMusicList = nullptr;
	mInsertOrder = 0;
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

void Player::SetMusicList(SortedList<MusicItem> *inMusicList) {
	mMusicList = inMusicList;
}

// Add music to playlist.
void Player::AddToPlaylist() {
	MusicItem music; // Temporary variable to hold info

	music.SetIdFromKB(); // Get id to search
	if (mMusicList->Retrieve(music) != -1) { // Check if music exists in list
		// Music exists
		// Create a music item to put in playlist
		PlaylistItem playItem(music.GetId(), 0, mInsertOrder++);
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
			if (mMusicList->Retrieve(musicItem) != -1) {
				// Music found in list, play
				musicItem.DisplayRecordOnScreen();
				playItem.IncreaseNumPlay(); // Increase played count
				mPlaylist.Replace(playItem); // Apply change to list

				// Get lyrics and display if exists
				string lyrics;
				if (mLyricsManager.GetLyrics(musicItem.GetName(),
					musicItem.GetArtist(), lyrics)) {
					// We have lyrics for that music, show on console
					cout << "\n\t-------- Lyrics ------------------\n\n";
					cout << lyrics << endl;
				} else {
					// We don't have lyrics for that music, get from genius.com
					int fetchFromWeb = -1;
					while (!((fetchFromWeb == 0) || (fetchFromWeb == 1))) {
						cout << "\n\tWe don't have lyrics for \"" << musicItem.GetName()
							<< "\", shall we look for it on the web? (1: yes / 0: no): ";
						if (!GetNum(fetchFromWeb)) {
							continue;
						}
					}
					if (fetchFromWeb == 1) {
						if (GeniusLyricsFetcher::GetLyricsFromGenius(
							musicItem.GetName(), musicItem.GetArtist(), lyrics)) {
							string indentedLyrics = lyrics;
							for (auto pos = indentedLyrics.find('\n'); pos != string::npos;
								pos = indentedLyrics.find('\n', pos + 1)) {
								indentedLyrics.replace(pos, 1, "\n\t");
							}
							cout << "\n\t-------- Lyrics ------------------\n\n";
							cout << '\t' << indentedLyrics << endl;


							int save = -1;
							while (!((save == 0) || (save == 1))) {
								cout << "\n\tIs this the right lyrics for your song?\n"
									<< "\tIf yes, we'll save it for you so we can load it faster next time."
									<< " (1: yes / 0: no): ";
								if (!GetNum(save)) {
									continue;
								}
							}
							if (save == 1) {
								mLyricsManager.SaveLyrics(musicItem.GetName(),
									musicItem.GetArtist(), lyrics);
							}
						}
					}
				}
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
