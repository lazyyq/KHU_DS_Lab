#include "Application.h"

// Constructor
Application::Application() {
	mCommand = 0;
	mInsertOrder = 0;
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
	system("pause >nul");
}

// Get number from keyboard input
int Application::GetNum(int &n) {
	int result = 1;

	cin >> n;
	if (cin.fail() == 1) { // Error, input is probably not int
		cin.clear(); // Clear fail flags
		result = 0; // We return 0 on failure
	}
	cin.ignore(100, '\n');

	return result;
}

// Program driver.
void Application::Run() {
	MenuMain();
}

// Add new record into list.
int Application::AddMusic() {
	// 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
	if (mMasterList.IsFull()) {
		cout << "\n\tList is full.\n";
		return 0;
	}

	MusicType data; // Temporary variable to hold info

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
	MusicType data; // Temporary variable to hold info
	data.SetIdFromKB(); // Get id to delete

	if (mMasterList.Delete(data) == 1) { // Success
		cout << "\n\n\tSuccessfully deleted data.\n";
	} else { // Failed
		cout << "\n\n\tFailed to delete data.\n";
	}
}

// Replace music with input.
void Application::ReplaceMusic() {
	MusicType data; // Temporary variable to hold info

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
	MusicType data; // Temporary variable to hold info
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
	MusicType data;// Temporary variable to hold info
	data.SetNameFromKB(); // Get name to search

	bool found = false; // Remember whether we've found at least one

	// Object to hold data from list
	MusicType dataFromList;
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
	MusicType data; // Temporary varilable to hold info
	data.SetArtistFromKB(); // Get artist to search

	bool found = false; // Remember whether we've found at least one

	// Object to hold data from list
	MusicType dataFromList;
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
	MusicType data; // Temporary varilable to hold info
	data.SetGenreFromKB(); // Get genre to search

	bool found = false; // Remember whether we've found at least one

	// Object to hold data from list
	MusicType dataFromList;
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
	MusicType data; // Temporary variable to hold info

	// Display current list capacity
	cout << "\n\n\tCurrent list (" << mMasterList.GetLength()
		<< "/" << SORTEDLIST_MAXSIZE << ")\n";
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

// Add music to playlist.
void Application::AddToPlaylist() {
	MusicType music; // Temporary variable to hold info

	music.SetIdFromKB(); // Get id to search
	if (mMasterList.Retrieve(music) != -1) { // Check if music exists in list
		// Music exists
		// Create a music item to put in playlist
		PlayItem playItem(music.GetId(), 0, mInsertOrder++);

		if (mPlaylist.IsFull()) { // Check if playlist is full
			cout << "\n\n\tPlaylist is full, deleting oldest item.\n";
			// Playlist is full, delete oldest item to make space
			mPlaylist.DeQueue();
		}
		mPlaylist.EnQueue(playItem); // Add to playlist
		cout << "\n\n\tAdded music \"" << playItem.GetId() << "\" to playlist.\n";
	} else {
		cout << "\n\n\tMusic does not exist in list, aborting.\n";
	}
}

// Play music from playlist in order.
void Application::PlayInsertOrder() {
	PlayItem playItem; // Variable to hold item info from playlist
	MusicType musicItem; // Variable to hold info from music list

	if (mPlaylist.IsEmpty()) {
		cout << "\n\n\tList is empty.\n";
		return;
	}

	bool done = false;
	while (true) { // Loop until user wants to break
		mPlaylist.ResetPointer(); // Reset pointer

		int curIndex = mPlaylist.GetNextItem(playItem); // Get item from playlist
		while (curIndex > -1) {
			musicItem.SetId(playItem.GetId());
			// Search with id and check if music exists in music list
			if (mMasterList.Retrieve(musicItem) != -1) {
				// Music exists
				musicItem.DisplayRecordOnScreen();
				playItem.IncreaseNumPlay(); // Increased played count
			} else {
				// Music not found
				cout << "\n\n\tMusic \"" << musicItem.GetId() << "\" does not exist. Skipping.\n";
			}
			curIndex = mPlaylist.GetNextItem(playItem);
		}

		// Check whether to repeat or not
		while (true) {
			cout << "\n\n\tEnd of playlist. Play again? (1: yes / 0: no): ";
			int command;
			cin >> command;
			if (cin.fail() == 1) { // Input error, input is probably not int.
				cin.clear();
				command = -1;
			}
			cin.ignore();
			cout << endl;

			if (command == 0) {
				done = true; // Break outer loop
				break;
			} else if (command == 1) { // Continue outer loop
				break;
			} // else : continue loop
		}

		if (done) { // Break loop
			break;
		}
	}
}

// Delete music from playlist
void Application::DeleteFromPlaylist() {
	PlayItem playItem; // Temporary variable to hold id info

	playItem.SetIdFromKB(); // Get id to search from playlist

	mPlaylist.Delete(playItem);
}

// Make list empty
void Application::MakeEmpty() {
	mMasterList.MakeEmpty();

	cout << "\n\n\tEmptied list.\n";
}

// Open a file by file descriptor as an input file.
int Application::OpenInFile(char *fileName) {
	mInFile.open(fileName);	// file open for reading.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!mInFile)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName) {
	mOutFile.open(fileName);	// file open for writing.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!mOutFile)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile() {
	int index = 0;
	MusicType data;	// 읽기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\n\tEnter Input file Name : ";
	cin >> filename;
	cin.ignore();

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// 파일의 모든 내용을 읽어 list에 추가
	while (!mInFile.eof()) {
		// array에 음악들의 정보가 들어있는 structure 저장
		data.ReadDataFromFile(mInFile);
		mMasterList.Add(data);
	}

	mInFile.close();	// file close

	// 현재 list 출력
	DisplayAllMusic();

	cout << "\n\tSuccessfully imported from file.\n";
	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile() {
	MusicType data;	// 쓰기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\n\tEnter Output file Name : ";
	cin >> filename;
	cin.ignore();

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// list 포인터를 초기화
	mMasterList.ResetIterator();

	// list의 모든 데이터를 파일에 쓰기
	int curIndex = mMasterList.GetNextItem(data);
	while (curIndex > -1) {
		data.WriteDataToFile(mOutFile);
		curIndex = mMasterList.GetNextItem(data);
	}

	mOutFile.close();	// file close

	cout << "\n\tSuccessfully exported to file.\n";
	return 1;
}

// Add a new singer
void Application::AddSinger() {
	SingerType singer;
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
	SingerType singer;
	singer.SetNameFromKB();

	// Get song id, name from keyboard
	SongType song;
	song.SetInfoFromKB();

	// Check if song exists in master list
	MusicType tempMusic; // Temporary variable to hold info from list
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
	SingerType singer;
	singer.SetNameFromKB();

	// Get singer from singer list
	if (mSingerList.Get(singer) == 1) {
		// Singer exists in singer list
		SongType song; // Temporary variable to hold info from song list
		MusicType music; // Temporary variable to hold info from music master list

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
