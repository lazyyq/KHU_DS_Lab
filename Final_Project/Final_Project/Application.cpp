#include "Application.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <json/json.h>

#include "PlaylistItem.h"
#include "SimpleItem.h"
#include "utils/Utils.h"
#include "dialog/DialogUtils.h"
#include "id3/ID3Tag.h"

#define CONSOLE_COLOR			"70"
#define MUSIC_LIST_FILENAME		"files/list_music.json"
#define ARTIST_LIST_FILENAME	"files/list_artist.json"
#define GENRE_LIST_FILENAME		"files/list_genre.json"

using namespace std;
using namespace utils;
namespace ID3 = MetadataInfo::ID3;

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
	string directories[] = { "files" };
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
	setlocale(LC_ALL, "");
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
int Application::AddMusic(const MusicItem &data) {
	int result = mMasterList.Add(data);
	if (result != 1) { // Add failed
		cout << "\n\tFailed to add " << data.GetName() << ". Probably duplicate?\n";
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

	cout << "\n\tSuccessfully added " << data.GetName() << ".\n";

	return 1;
}

// Get record from keyboard and add to list.
int Application::AddMusicManually() {
	MusicItem data; // Temporary variable to hold info

	cout << "\n\tPlease input new music data."
		<< " Duplicate data is not allowed.\n\n";
	cin >> data; // 키보드로부터 곡정보 입력

	int result = AddMusic(data);
	DisplayAllMusic(); // list 출력

	return result;
}

// Add record from an mp3 file
int Application::AddMusicFromFile() {
	// 파일 선택 창 띄우기
	wstring filename;
	const wchar_t *filter = L"MP3 File (*.mp3)\0*.mp3\0"; // MP3 파일 필터
	if (!DialogUtils::GetFile(filename, filter)) {
		return 0;
	}

	// 파일에서 태그 정보 읽어오기
	namespace ID3 = MetadataInfo::ID3;
	ID3::ID3Tag tag;
	if (!tag.Open(filename.c_str())) {
		return 0;
	}

	// 읽어온 정보를 MusicItem으로 만들어 리스트에 추가
	MusicItem item(tag);

	tag.Close(); // 태그 닫기

	int result = AddMusic(item); // 리스트에 추가
	if (result) {
		DisplayAllMusic();
	}

	return result;
}

// Add record from mp3 files inside a folder
int Application::AddMusicFromFolder() {
	// 폴더 선택 창 띄우기
	wstring path = L"."; // 기본 폴더는 현재 폴더
	if (!DialogUtils::GetFolder(path)) {
		return 0;
	}

	ID3::ID3Tag tag;
	int result = 0;

	for (const auto &entry : filesystem::recursive_directory_iterator(path)) {
		if (!entry.is_directory()) {
			if (!ToLowerCase(entry.path().extension().string()).compare(".mp3")) {
				// 파일에서 태그 정보 읽어오기
				if (tag.Open(entry.path().c_str())) {
					// 읽어온 정보를 MusicItem으로 만들어 리스트에 추가
					MusicItem item(tag);
					if (AddMusic(item)) {
						result = 1; // 리스트에 하나라도 추가 성공 시 함수 성공으로 간주
					}
				}
			}
		}
	}
	tag.Close();

	if (result) {
		cout << "\n\tFinished adding music.\n";
		DisplayAllMusic();
	} else {
		cout << "\n\tFailed to add music.\n"
			<< "\tPlease make sure you chose the right folder with mp3 files inside.\n";
	}
	return result;
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
	SortedDoublyIterator<SimpleItem> iter(singer.GetSongList());
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
	SortedDoublyIterator<SimpleItem> iter(genre.GetSongList());
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
	// Open music list file
	if (!OpenInFile(MUSIC_LIST_FILENAME)) {
		cout << "\n\tNothing to read from file.\n";
		return 0;
	}

	Json::Value root; // Root of json to store music info
	MusicItem data; // Store item from list

	// Convert each json value to music data
	mInFile >> root; // Read json data from file
	for (auto &value : root) {
		value >> data;
		mMasterList.Add(data);
	}

	mInFile.close();

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::SaveMusicListToFile() {
	// Open music list file
	if (!OpenOutFile(MUSIC_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	cout << "\n\tSaving music list..\n";

	Json::Value root; // Root of json to store music info
	MusicItem data; // Store item from list

	// Add each music data to json
	mMasterList.ResetIterator();
	int curIndex = mMasterList.GetNextItem(data);
	while (curIndex > -1) {
		root << data;
		curIndex = mMasterList.GetNextItem(data);
	}
	mOutFile << root; // Write to file

	mOutFile.close();

	return 1;
}

// 파일에서 가수 정보를 읽어서 리스트에 저장
int Application::ReadArtistListFromFile() {
	// Open artist list file
	if (!OpenInFile(ARTIST_LIST_FILENAME)) {
		cout << "\n\tNothing to read from file.\n";
		return 0;
	}

	Json::Value root; // Root of json to store artist info
	Singer singer; // Store item from list

	// Convert each json value to artist data
	mInFile >> root; // Read json data from file
	for (auto &value : root) {
		value >> singer;
		mSingerList.Add(singer);
	}

	mInFile.close(); // Close file

	return 1;
}

// 가수 리스트의 가수 아이템을 파일에 저장
int Application::SaveArtistListToFile() {
	// Open artist list file
	if (!OpenOutFile(ARTIST_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	cout << "\n\tSaving artist list..\n";

	Json::Value root; // Root of json to store singer info

	// Add each singer data to json
	SortedDoublyIterator<Singer> iter(mSingerList);
	for (Singer singer = iter.Next();
		iter.NextNotNull(); singer = iter.Next()) {
		root << singer;
	}
	mOutFile << root; // Write to file

	mOutFile.close();

	return 1;
}

// 파일에서 장르 정보를 읽어서 리스트에 저장
int Application::ReadGenreListFromFile() {
	// Open genre list file
	if (!OpenInFile(GENRE_LIST_FILENAME)) {
		cout << "\n\tNothing to read from file.\n";
		return 0;
	}

	Json::Value root; // Root of json to store genre info
	Genre genre; // Store item from list

	// Convert each json value to genre data
	mInFile >> root; // Read json data from file
	for (auto &value : root) {
		value >> genre;
		mGenreList.Add(genre);
	}

	mInFile.close(); // Close file

	return 1;
}

// 장르 리스트의 장르 정보들을 파일에 저장
int Application::SaveGenreListToFile() {
	// Open genre list file
	if (!OpenOutFile(GENRE_LIST_FILENAME)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	cout << "\n\tSaving genre list..\n";

	Json::Value root; // Root of json to store genre info

	// Add each genre data to json
	SortedDoublyIterator<Genre> iter(mGenreList);
	for (Genre genre = iter.Next();
		iter.NextNotNull(); genre = iter.Next()) {
		root << genre;
	}
	mOutFile << root; // Write to file

	mOutFile.close();

	return 1;
}
