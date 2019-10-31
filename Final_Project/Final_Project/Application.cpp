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
	cin >> data; // Ű����κ��� ������ �Է�

	int result = mMasterList.Add(data);
	if (result != 1) { // Add failed
		cout << "\n\tFailed to add data. Probably duplicate?\n";
		return 0;
	}

	string id = data.GetId(), name = data.GetName(),
		artistName = data.GetArtist(), genreName = data.GetGenre();
	// ������ �帣����Ʈ�� �߰��� ������
	SimpleItem simple(id, name, artistName);

	// ������ �̹� �ִ��� Ȯ��
	Singer singer; singer.SetName(artistName);
	if (mSingerList.Get(singer)) {
		// �̹� ������ ������ �� ����Ʈ�� �߰�
		singer.AddSong(simple);
		mSingerList.Replace(singer);
	} else {
		// ������ �� ���� �߰�
		singer.AddSong(simple);
		mSingerList.Add(singer);
	}

	// �帣�� �̹� �ִ��� Ȯ��
	Genre genre; genre.SetName(genreName);
	if (mGenreList.Get(genre)) {
		// �̹� ������ �帣�� �� ����Ʈ�� �߰�
		genre.AddSong(simple);
		mGenreList.Replace(genre);
	} else {
		// ������ �� �帣 �߰�
		genre.AddSong(simple);
		mGenreList.Add(genre);
	}

	cout << "\n\tSuccessfully added new data.\n";

	// ���� list ���
	DisplayAllMusic();

	return 1;
}

// Delete music from list.
void Application::DeleteMusic() {
	MusicItem data; // Temporary variable to hold info
	data.SetIdFromKB(); // Get id to delete

	if (mMasterList.Retrieve(data) != -1) {
		// ���� �����͸���Ʈ�� �����ϸ� ����
		// ���� ���翩�θ� ���� Ȯ���ϴ� ������
		// Retrieve�� ���� ���� ������ ������ �޾ƿ�
		// ���� ����Ʈ�� �帣 ����Ʈ������ �����ϱ� ���� ��
		mMasterList.Delete(data);
	} else { // Failed
		cout << "\n\n\tNo such data in our list.\n";
		return;
	}

	SimpleItem simple; // ���� ����Ʈ�� �帣 ����Ʈ �˻���
	string id = data.GetId(), artistName = data.GetArtist(),
		genreName = data.GetGenre();;
	simple.SetId(id);

	// ������ ���� ���� �̸� �޾ƿ���
	Singer singer;
	singer.SetName(artistName);

	// �ش� ������ �� ����Ʈ������ ����
	if (mSingerList.Get(singer)) {
		singer.RemoveSong(simple);
		mSingerList.Replace(singer);
	}

	// ������ ���� �帣 �̸� �޾ƿ���
	Genre genre;
	genre.SetName(genreName);

	// �ش� ������ �帣 ����Ʈ������ ����
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
	// linkedlist �ʱ�ȭ
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

	// list �����͸� �ʱ�ȭ
	mMasterList.ResetIterator();

	cout << "\n\tSaving music list..\n";
	// list�� ��� �����͸� ���Ͽ� ����
	int curIndex = mMasterList.GetNextItem(data);
	while (curIndex > -1) {
		mOutFile << data;
		curIndex = mMasterList.GetNextItem(data);
	}

	mOutFile.close(); // Close file

	return 1;
}

// ���Ͽ��� ���� ������ �о ����Ʈ�� ����
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

// ���� ����Ʈ�� ���� �������� ���Ͽ� ����
int Application::SaveArtistListToFile() {
	Singer singer;	// Temporary variable to hold info from list

	// Open music list file
	if (!OpenOutFile(ARTIST_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// list �����͸� �ʱ�ȭ
	mMasterList.ResetIterator();

	cout << "\n\tSaving artist list..\n";
	// list�� ��� �����͸� ���Ͽ� ����
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

// ���Ͽ��� �帣 ������ �о ����Ʈ�� ����
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

// �帣 ����Ʈ�� �帣 �������� ���Ͽ� ����
int Application::SaveGenreListToFile() {
	Genre genre;	// Temporary variable to hold info from list

	// Open music list file
	if (!OpenOutFile(GENRE_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// list �����͸� �ʱ�ȭ
	mMasterList.ResetIterator();

	cout << "\n\tSaving genre list..\n";
	// list�� ��� �����͸� ���Ͽ� ����
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
