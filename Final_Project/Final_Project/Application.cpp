#include "Application.h"

// Constructor
Application::Application()
	: mPlayer(mMasterList) {
	InitDirectories(); // Create necessary directories
	ReadMusicListFromFile(); // Load music list
	ReadArtistListFromFile(); // Load artist list
	ReadGenreListFromFile(); // Load genre list
}

// Destructor
Application::~Application() {
	// Clean linked lists
	mSingerList.MakeEmpty();
	mGenreList.MakeEmpty();
}

// Create directories (if not exist) required for running program
void Application::InitDirectories() {
	// files: where music list, singer list, playlist... are stored.
	string directories[] = {"files"};
	for (string directory : directories) {
		filesystem::create_directory(directory);
	}
}

// Set cmd window color scheme
void Application::SetConsoleColor() {
	system("color " CONSOLE_COLOR);
}

// Program driver.
void Application::Run() {
	SetConsoleColor(); // Set color
	MenuMain(); // Show main menu
}

// Save music list, playlist, etc.
void Application::Save() {
	// Save lists
	SaveMusicListToFile();
	SaveArtistListToFile();
	SaveGenreListToFile();
	mPlayer.SavePlaylistToFile();
}

// Add new record into list.
int Application::AddMusic() {
	MusicItem data; // Temporary variable to hold info

	cout << "\n\tPlease input new music data."
		<< " Duplicate data is not allowed.\n\n";
	cin >> data; // 키보드로부터 곡정보 입력

	int result = mMasterList.Add(data);
	if (result != 1) { // Add failed
		cout << "\n\tFailed to add data. Probably duplicate?\n";
		return 0;
	}

	string id = data.GetId(), name = data.GetName(),
		artistName = data.GetArtist(), genreName = data.GetGenre();
	// 가수와 장르리스트에 추가할 아이템
	SimpleItem simple(id, name, artistName);

	// 가수가 이미 있는지 확인
	Singer singer; singer.SetName(artistName);
	if (mSingerList.Get(singer)) {
		// 이미 있으면 가수의 곡 리스트에 추가
		singer.AddSong(simple);
		mSingerList.Replace(singer);
	} else {
		// 없으면 새 가수 추가
		singer.AddSong(simple);
		mSingerList.Add(singer);
	}

	// 장르가 이미 있는지 확인
	Genre genre; genre.SetName(genreName);
	if (mGenreList.Get(genre)) {
		// 이미 있으면 장르의 곡 리스트에 추가
		genre.AddSong(simple);
		mGenreList.Replace(genre);
	} else {
		// 없으면 새 장르 추가
		genre.AddSong(simple);
		mGenreList.Add(genre);
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
		// 곡이 마스터리스트에 존재하면 삭제
		// 굳이 존재여부를 먼저 확인하는 이유는
		// Retrieve를 통해 곡의 완전한 정보를 받아와
		// 가수 리스트와 장르 리스트에서도 삭제하기 위한 것
		mMasterList.Delete(data);
	} else { // Failed
		cout << "\n\n\tNo such data in our list.\n";
		return;
	}

	SimpleItem simple; // 가수 리스트와 장르 리스트 검색용
	string id = data.GetId(), artistName = data.GetArtist(),
		genreName = data.GetGenre();;
	simple.SetId(id);

	// 삭제된 곡의 가수 이름 받아오기
	Singer singer;
	singer.SetName(artistName);

	// 해당 가수의 곡 리스트에서도 삭제
	if (mSingerList.Get(singer)) {
		singer.RemoveSong(simple);
		mSingerList.Replace(singer);
	}

	// 삭제된 곡의 장르 이름 받아오기
	Genre genre;
	genre.SetName(genreName);

	// 해당 가수의 장르 리스트에서도 삭제
	if (mGenreList.Get(genre)) {
		genre.RemoveSong(simple);
		mGenreList.Replace(genre);
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
	if (result != -1) { // Found
		cout << "\n\t---------------------------------------\n\n";
		cout << data;
		cout << "\n\t---------------------------------------\n";
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
	while (curIndex > -1) {
		// Check if input data's name property is
		// substring of retrieved item's.
		if (dataFromList.GetName().find(data.GetName())
			!= std::string::npos) {
			cout << "\n\t---------------------------------------\n\n";
			cout << dataFromList; // Display song info
			cout << "\n\t---------------------------------------\n";

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

	// Iterate through singer's song list
	DoublyIterator<SimpleItem> iter(singer.GetSongList());
	song = iter.Next();
	while (iter.NextNotNull()) {
		// Display info for each song in the singer's song list
		music.SetId(song.GetId());
		if (mMasterList.Retrieve(music) != -1) {
			// Music found in master list, display info on screen
			cout << "\n\t---------------------------------------\n\n";
			cout << music; // Display song info
			cout << "\n\t---------------------------------------\n";
		} else {
			// Music not found
			cout << "\n\n\tSong " << music.GetName() << " not found in music list.\n";
		}
		song = iter.Next();
	}
}

// Search music with genre name
void Application::SearchByGenre() {
	// Get genre name to search
	Genre genre;
	genre.SetNameFromKB();

	// Get genre from genre list
	if (!mGenreList.Get(genre)) {
		// Genre does not exist in genre list
		cout << "\n\n\tNo such genre in genre list.\n";
		return;
	}

	// Check if song list is empty
	if (genre.GetSongList().IsEmpty()) {
		// Empty
		cout << "\n\n\t" << genre.GetName() << " has no songs.\n";
		return;
	}

	SimpleItem song; // Temporary variable to hold info from song list
	MusicItem music; // Temporary variable to hold info from music master list

	// Iterate through song list
	DoublyIterator<SimpleItem> iter(genre.GetSongList());
	song = iter.Next();
	while (iter.NextNotNull()) {
		// Display info for each song in the genre's song list
		music.SetId(song.GetId());
		if (mMasterList.Retrieve(music) != -1) {
			// Music found in master list, display info on screen
			cout << "\n\t---------------------------------------\n\n";
			cout << music; // Display song info
			cout << "\n\t---------------------------------------\n";
		} else {
			// Music not found
			cout << "\n\n\tSong " << music.GetName() << " not found in music list.\n";
		}
		song = iter.Next();
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
	// linkedlist 초기화
	mMasterList.MakeEmpty();
	mSingerList.MakeEmpty();
	mGenreList.MakeEmpty();
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
		mOutFile << data;
		curIndex = mMasterList.GetNextItem(data);
	}

	mOutFile.close(); // Close file

	return 1;
}

// 파일에서 가수 정보를 읽어서 리스트에 저장
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

// 가수 리스트의 가수 아이템을 파일에 저장
int Application::SaveArtistListToFile() {
	Singer singer;	// Temporary variable to hold info from list

	// Open music list file
	if (!OpenOutFile(ARTIST_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// list 포인터를 초기화
	mMasterList.ResetIterator();

	cout << "\n\tSaving artist list..\n";
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

// 파일에서 장르 정보를 읽어서 리스트에 저장
int Application::ReadGenreListFromFile() {
	// Open music list file
	if (!OpenInFile(GENRE_LIST_FILENAME)) {
		cout << "\n\tNothing to read from file.\n";
		return 0;
	}

	// Read music data from file and add to list
	while (!mInFile.eof()) {
		Genre genre;
		mInFile >> genre; // Load music data from file
		mGenreList.Add(genre); // Add to list
	}

	mInFile.close(); // Close file

	return 1;
}

// 장르 리스트의 장르 정보들을 파일에 저장
int Application::SaveGenreListToFile() {
	Genre genre;	// Temporary variable to hold info from list

	// Open music list file
	if (!OpenOutFile(GENRE_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// list 포인터를 초기화
	mMasterList.ResetIterator();

	cout << "\n\tSaving genre list..\n";
	// list의 모든 데이터를 파일에 쓰기
	DoublyIterator<Genre> iter(mGenreList);
	genre = iter.Next();
	while (iter.NextNotNull()) {
		//data.WriteDataToFile(mOutFile);
		mOutFile << genre;
		genre = iter.Next();
	}

	mOutFile.close(); // Close file

	return 1;
}
