#include "Application.h"

// Constructor
Application::Application()
	: mPlayer(mMasterList) {
	InitDirectories(); // Create necessary directories
	ReadMusicListFromFile(); // Load music list
	ReadArtistListFromFile(); // Load artist list
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

void Application::SetConsoleColor() {
	system("color " CONSOLE_COLOR);
}

// Program driver.
void Application::Run() {
	SetConsoleColor();
	MenuMain();
}

// Save music list, playlist, etc.
void Application::Save() {
	SaveMusicListToFile(); // Save music list
	SaveArtistListToFile();
	mPlayer.SavePlaylistToFile(); // Save playlist
}

// Add new record into list.
int Application::AddMusic() {
	MusicItem data; // Temporary variable to hold info

	cout << "\n\tPlease input new music data."
		<< " Duplicate data is not allowed.\n\n";
	// Get new music info from keyboard
	cin >> data;

	int result = mMasterList.Add(data);
	if (result != 1) { // Add failed
		cout << "\n\tFailed to add data. Probably duplicate?\n";
		return 0;
	}

	string id = data.GetId(), name = data.GetName(),
		artist = data.GetArtist();
	SimpleItem simple(id, name, artist);

	// Check if singer exists in our list
	Singer singer; singer.SetName(artist);
	if (mSingerList.Get(singer)) {
		singer.AddSong(simple);
		mSingerList.Replace(singer);
	} else {
		singer.AddSong(simple);
		mSingerList.Add(singer);
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

	if (mMasterList.Retrieve(data) != -1) {
		mMasterList.Delete(data);
	} else { // Failed
		cout << "\n\n\tNo such data in our list.\n";
		return;
	}

	SimpleItem simple;
	Singer singer;
	string id = data.GetId(), artist = data.GetArtist();
	simple.SetId(id);
	singer.SetName(artist);

	if (mSingerList.Get(singer)) {
		singer.RemoveSong(simple);
		mSingerList.Replace(singer);
	}

	cout << "\n\n\tSuccessfully deleted data.\n";
}

// Replace music with input.
void Application::ReplaceMusic() {
	MusicItem data; // Temporary variable to hold info

	data.SetIdFromKB(); // Get id to search
	cin >> data; // Get the rest info to search

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
		cout << data;
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
			cout << dataFromList;
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
	// Get singer name to search
	Singer singer;
	singer.SetNameFromKB();

	// Get singer from singer list
	if (!mSingerList.Get(singer)) {
		// Singer does not exist in singer list
		cout << "\n\n\tNo such singer in singer list.\n";
		return;
	}

	// Check if song list is empty
	if (singer.GetSongList().IsEmpty()) {
		// Empty
		cout << "\n\n\t" << singer.GetName() << " has no songs.\n";
		return;
	}

	SimpleItem song; // Temporary variable to hold info from song list
	MusicItem music; // Temporary variable to hold info from music master list

	DoublyIterator<SimpleItem> iter(singer.GetSongList());
	song = iter.Next();
	while (iter.NextNotNull()) {
		// Display info for each song in the singer's song list
		music.SetId(song.GetId());
		if (mMasterList.Retrieve(music) != -1) {
			// Music found in master list, display info on screen
			cout << music;
		} else {
			// Music not found
			cout << "\n\n\tSong " << music.GetName() << " not found in music list.\n";
		}
		song = iter.Next();
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
			cout << dataFromList;
			cout << "\n\t---------------------------------------\n\n";

			found = true;
		}
		curIndex = mMasterList.GetNextItem(dataFromList);
	}
}

// Display all records in the list on screen.
void Application::DisplayAllMusic() {
	MusicItem data; // Temporary variable to hold info

	if (mMasterList.IsEmpty()) {
		cout << "\n\n\tThere's nothing in the list!\n";
		return;
	}

	// Display current list capacity
	cout << "\n\n\tTotal items: " << mMasterList.GetLength() << endl;
	cout << "\n\t=======================================\n";

	// Print all data in list
	mMasterList.ResetIterator(); // Reset pointer
	int curIndex = mMasterList.GetNextItem(data);
	if (curIndex > -1) { // Print first item
		cout << "\n\tMusic #" << (curIndex + 1) << "\n\n";
		cout << data;
		curIndex = mMasterList.GetNextItem(data);
	}
	while (curIndex > -1) { // Print rest
		cout << "\n\t---------------------------------------\n";
		cout << "\n\tMusic #" << (curIndex + 1) << "\n\n";
		cout << data;
		curIndex = mMasterList.GetNextItem(data);
	}

	cout << "\n\t=======================================\n";
}

// Make list empty
void Application::MakeEmpty() {
	mMasterList.MakeEmpty();
	mPlayer.MakeEmpty();

	cout << "\n\n\tEmptied list.\n";
}

// Open a file by file descriptor as an input file.
int Application::OpenInFile(string fileName) {
	mInFile.open(fileName); // Open file for reading

	// Return 1 on success
	if (mInFile && mInFile.peek() != EOF) {
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
		cout << "\n\tNothing to read from file.\n";
		return 0;
	}

	// Read music data from file and add to list
	while (!mInFile.eof()) {
		mInFile >> data; // Load music data from file
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
		//data.WriteDataToFile(mOutFile);
		mOutFile << data;
		curIndex = mMasterList.GetNextItem(data);
	}

	mOutFile.close(); // Close file

	return 1;
}

int Application::ReadArtistListFromFile() {
	// Open music list file
	if (!OpenInFile(ARTIST_LIST_FILENAME)) {
		cout << "\n\tNothing to read from file.\n";
		return 0;
	}

	// Read music data from file and add to list
	while (!mInFile.eof()) {
		Singer singer;
		mInFile >> singer; // Load music data from file
		mSingerList.Add(singer); // Add to list
	}

	mInFile.close(); // Close file

	return 1;
}

int Application::SaveArtistListToFile() {
	Singer singer;	// Temporary variable to hold info from list

	// Open music list file
	if (!OpenOutFile(ARTIST_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// list 포인터를 초기화
	mMasterList.ResetIterator();

	cout << "\n\tSaving music list..\n";
	// list의 모든 데이터를 파일에 쓰기
	DoublyIterator<Singer> iter(mSingerList);
	singer = iter.Next();
	while (iter.NextNotNull()) {
		//data.WriteDataToFile(mOutFile);
		mOutFile << singer;
		singer = iter.Next();
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
