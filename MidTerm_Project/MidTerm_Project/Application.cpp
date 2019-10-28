#include "Application.h"

// Constructor
Application::Application() {
	mCommand = 0;
}

// Destructor
Application::~Application() {
	// Clean linked lists
	mSingerList.MakeEmpty();
}

// Clear console.
void Application::Clear() {
	system("cls");
}

// Pause console.
void Application::Pause() {
	Pause("\n\tPress any key to continue.\n");
}

void Application::Pause(const string &message) {
	cout << message;
	system("pause >nul");
}

// Get number from keyboard input
int Application::GetNum(int &n) {
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

void Application::InitDirectories() {
	string directories[] = {"files"};
	for (string directory : directories) {
		filesystem::create_directory(directory);
	}
}

// Program driver.
void Application::Run() {
	InitDirectories(); // Create necessary directories
	ReadMusicListFromFile(); // Load music list
	mPlayer.SetMusicList(&mMasterList); // Pass music list to playlist manager
	MenuMain();
}

// Finish program
void Application::Finish() {
	SaveMusicListToFile(); // Save music list to file on program finish
}

// Add new record into list.
int Application::AddMusic() {
	MusicItem data; // Temporary variable to hold info

	cout << "\n\tPlease input new music data."
		<< " Duplicate data is not allowed.\n";
	// Get new music info from keyboard
	data.SetRecordFromKB();

	int result = mMasterList.Add(data);
	if (result != 1) { // Add failed
		cout << "\n\tFailed to add data. Probably duplicate?\n";
		return 0;
	}

	cout << "\n\tSuccessfully added new data.\n";

	// 현재 list 출력
	DisplayAllMusic();

	return 1;
}

// Delete music from list.
void Application::DeleteMusic() {
	MusicItem data; // Temporary variable to hold info
	data.SetIdFromKB(); // Get id to delete

	if (mMasterList.Delete(data) == 1) { // Success
		cout << "\n\n\tSuccessfully deleted data.\n";
	} else { // Failed
		cout << "\n\n\tFailed to delete data.\n";
	}
}

// Replace music with input.
void Application::ReplaceMusic() {
	MusicItem data; // Temporary variable to hold info

	data.SetIdFromKB(); // Get id to search
	data.SetRecordFromKB(); // Get the rest info to search

	if (mMasterList.Replace(data) == 1) { // Success
		cout << "\n\n\tSuccessfully replaced data.\n";
	} else { // Failed
		cout << "\n\n\tFailed to replace data.\n";
	}
}

// Retrieve music information and display
void Application::SearchById() {
	MusicItem data; // Temporary variable to hold info
	data.SetIdFromKB(); // Get id to search in list

	// Search in list
	int result = mMasterList.Retrieve(data);
	if (result == 1) { // Found
		data.DisplayRecordOnScreen();
	} else {	// Not found
		cout << "\n\n\tFailed to find data\n";
	}
}

// Search music with name
void Application::SearchByName() {
	MusicItem data;// Temporary variable to hold info
	data.SetNameFromKB(); // Get name to search

	bool found = false; // Remember whether we've found at least one

	// Object to hold data from list
	MusicItem dataFromList;
	// Iterate through list
	mMasterList.ResetIterator();
	int curIndex = mMasterList.GetNextItem(dataFromList);
	if (curIndex > -1) {
		cout << "\n\n\t---------------------------------------\n\n";
	}
	while (curIndex > -1) {
		// Check if input data's name property is
		// substring of retrieved item's.
		if (dataFromList.GetName().find(data.GetName())
			!= std::string::npos) {
			dataFromList.DisplayRecordOnScreen();
			cout << "\n\t---------------------------------------\n\n";

			found = true;
		}
		curIndex = mMasterList.GetNextItem(dataFromList);
	}

	if (!found) {
		cout << "\n\n\tFailed to find data.\n";
	}
}

// Search music with artist
void Application::SearchByArtist() {
	MusicItem data; // Temporary varilable to hold info
	data.SetArtistFromKB(); // Get artist to search

	bool found = false; // Remember whether we've found at least one

	// Object to hold data from list
	MusicItem dataFromList;
	// Iterate through list
	mMasterList.ResetIterator();
	int curIndex = mMasterList.GetNextItem(dataFromList);
	if (curIndex > -1) {
		cout << "\n\n\t---------------------------------------\n\n";
	}
	while (curIndex > -1) {
		// Check if input data's artist property is
		// substring of retrieved item's.
		if (dataFromList.GetArtist().find(data.GetArtist())
			!= std::string::npos) {
			dataFromList.DisplayRecordOnScreen();
			cout << "\n\t---------------------------------------\n\n";

			found = true;
		}
		curIndex = mMasterList.GetNextItem(dataFromList);
	}

	if (!found) {
		cout << "\n\n\tFailed to find data.\n";
	}
}

// Search music with name
void Application::SearchByGenre() {
	MusicItem data; // Temporary varilable to hold info
	data.SetGenreFromKB(); // Get genre to search

	bool found = false; // Remember whether we've found at least one

	// Object to hold data from list
	MusicItem dataFromList;
	// Iterate through list
	mMasterList.ResetIterator();
	int curIndex = mMasterList.GetNextItem(dataFromList);
	if (curIndex > -1) {
		cout << "\n\n\t---------------------------------------\n\n";
	}
	while (curIndex > -1) {
		// Check if retrieved item's genre matches that of input data's
		if (dataFromList.GetGenre().compare(data.GetGenre()) == 0) {
			dataFromList.DisplayRecordOnScreen();
			cout << "\n\t---------------------------------------\n\n";

			found = true;
		}
		curIndex = mMasterList.GetNextItem(dataFromList);
	}
}

// Display all records in the list on screen.
void Application::DisplayAllMusic() {
	MusicItem data; // Temporary variable to hold info

	// Display current list capacity
	cout << "\n\n\tTotal items: " << mMasterList.GetLength() << endl;
	cout << "\n\t=======================================\n";

	// Print all data in list
	mMasterList.ResetIterator(); // Reset pointer
	int curIndex = mMasterList.GetNextItem(data);
	if (curIndex > -1) { // Print first item
		cout << "\n\tMusic #" << (curIndex + 1) << "\n\n";
		data.DisplayRecordOnScreen();
		curIndex = mMasterList.GetNextItem(data);
	}
	while (curIndex > -1) { // Print rest
		cout << "\n\t---------------------------------------\n";
		cout << "\n\tMusic #" << (curIndex + 1) << "\n\n";
		data.DisplayRecordOnScreen();
		curIndex = mMasterList.GetNextItem(data);
	}

	cout << "\n\t=======================================\n";
}

// Make list empty
void Application::MakeEmpty() {
	mMasterList.MakeEmpty();

	cout << "\n\n\tEmptied list.\n";
}

// Open a file by file descriptor as an input file.
int Application::OpenInFile(string fileName) {
	mInFile.open(fileName); // Open file for reading

	// Return 1 on success
	if (mInFile) {
		return 1;
	} else {
		return 0;
	}
}

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(string fileName) {
	mOutFile.open(fileName); // Open file for writing

	// Return 1 on success
	if (mOutFile) {
		return 1;
	} else {
		return 0;
	}
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadMusicListFromFile() {
	MusicItem data;	// Temporary variable to hold info from file

	// Open music list file
	if (!OpenInFile(MUSIC_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// Read music data from file and add to list
	while (!mInFile.eof()) {
		data.ReadDataFromFile(mInFile); // Load music data from file
		mMasterList.Add(data); // Add to list
	}

	mInFile.close(); // Close file

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::SaveMusicListToFile() {
	MusicItem data;	// Temporary variable to hold info from list

	// Open music list file
	if (!OpenOutFile(MUSIC_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// list 포인터를 초기화
	mMasterList.ResetIterator();

	cout << "\n\tSaving music list..\n";
	// list의 모든 데이터를 파일에 쓰기
	int curIndex = mMasterList.GetNextItem(data);
	while (curIndex > -1) {
		data.WriteDataToFile(mOutFile);
		curIndex = mMasterList.GetNextItem(data);
	}

	mOutFile.close(); // Close file

	return 1;
}

// Add a new singer
void Application::AddSinger() {
	Singer singer;
	singer.SetInfoFromKB(); // Get name, age, sex from keyboard

	// Add singer to list
	int result = mSingerList.Add(singer);
	if (result == 1) {
		// Successfully added
		cout << "\n\n\tSuccessfully added singer to list.\n";
	} else {
		// Failed
		cout << "\n\n\tError while adding singer to list. Probably duplicate?\n";
	}
}

// Add a new song to singer's song list
void Application::AddSong() {
	// Get singer name from keyboard
	Singer singer;
	singer.SetNameFromKB();

	// Get song id, name from keyboard
	SongItem song;
	song.SetInfoFromKB();

	// Check if song exists in master list
	MusicItem tempMusic; // Temporary variable to hold info from list
	tempMusic.SetId(song.GetId());
	if (mMasterList.Retrieve(tempMusic) == -1) {
		// Song does not exist in master list, abort
		cout << "\n\n\tSong does not exist in music list, aborting\n";
		return;
	}

	// Check if singer exists in singer list
	if (mSingerList.Get(singer) != 1) {
		// Singer does not exist in our singer list
		// Ask user if he wants to add a new singer first
		char c;
		bool done = false;
		while (!done) {
			cout << "\n\n\tSinger does not exist in our singer list, add now? (y/n): ";
			cin >> c;
			cin.ignore(100, '\n');
			switch (c) {
			case 'Y':
			case 'y':
				// Get rest info for singer and add to list
				cout << "\n\tPlease input rest of the info for singer.\n";
				singer.SetAgeFromKB();
				singer.SetSexFromKB();
				mSingerList.Add(singer);
				done = true;
				break;
			case 'N':
			case 'n':
				// Abort
				cout << "\n\n\tAborting...\n";
				return;
			}
		}
	}
	// Finally add song to the singer's song list
	if (singer.AddSong(song) == 1) {
		// Add successful
		// Replace singer in singer list with new one
		cout << "replace start\n";
		mSingerList.Replace(singer);
		cout << "replace end\n";
		cout << "\n\n\tSuccessfully added song to "
			<< singer.GetName() << "'s song list.\n";
	} else {
		cout << "\n\n\tFailed to add song to the list. Probably duplicate?\n";
	}
}

// Search songs by singer whose name exactly matches user's input.
void Application::SearchBySinger() {
	// Get singer name to search
	Singer singer;
	singer.SetNameFromKB();

	// Get singer from singer list
	if (mSingerList.Get(singer) == 1) {
		// Singer exists in singer list
		SongItem song; // Temporary variable to hold info from song list
		MusicItem music; // Temporary variable to hold info from music master list

		// Check if song list is empty
		if (singer.GetSongList().GetLength() == 0) {
			// Empty
			cout << "\n\n\tSong list is empty.\n";
		} else {
			// Display info for each song in the singer's song list
			for (int i = 0, len = singer.GetSongList().GetLength(); i < len; i++) {
				// Get song from song list
				singer.GetSongList().GetNextItem(song);
				// Get music from master list based on song info
				music.SetId(song.GetId());

				if (mMasterList.Retrieve(music) != -1) {
					// Music found in master list, display info on screen
					music.DisplayRecordOnScreen();
				} else {
					// Music not found
					cout << "\n\n\tSong " << music.GetName() << " not found in music list.\n";
				}
			}
		}
	} else {
		// Singer does not exist in singer list
		cout << "\n\n\tNo such singer in singer list.\n";
	}
}
