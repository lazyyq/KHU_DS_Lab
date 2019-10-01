#include "Application.h"

// Program driver.
void Application::Run()
{
	while (1)
	{
		mCommand = GetCommand();

		switch (mCommand)
		{
		case 1:		// 곡 정보를 입력 받아 리스트에 추가
			AddMusic();
			break;
		case 2:		// 곡의 고유번호를 입력 받아 리스트에서 삭제
			DeleteMusic();
			break;
		case 3:		// 곡 정보를 입력 받아서 리스트에서 해당 곡 정보를 갱신	
			ReplaceMusic();
			break;
		case 4:		// 입력된 ID로 리스트에서 곡을 찾아서 화면에 출력
			SearchById();
			break;
		case 5:		// 입력된 가수 이름으로 리스트에서 곡을 찾아서 화면에 출력
			SearchByName();
			break;
		case 6:		// 리스트에 저장된 모든 곡을 화면에 출력
			DisplayAllMusic();
			break;
		case 7: 		// 리스트에 입력된 모든 곡을 삭제
			MakeEmpty();
			break;
		case 8:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 9:		// save list data into a file.
			WriteDataToFile();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add music" << endl;
	cout << "\t   2 : Delete music" << endl;
	cout << "\t   3 : Replace music" << endl;
	cout << "\t   4 : Find music by ID" << endl;
	cout << "\t   5 : Find music by Artist" << endl;
	cout << "\t   6 : Display all music" << endl;
	cout << "\t   7 : Empty list" << endl;
	cout << "\t   8 : Read list from file" << endl;
	cout << "\t   9 : Write list to file" << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	if (cin.fail() == 1) {
		// Input error
		cin.clear();
		command = -1;
	}
	cin.ignore();
	cout << endl;

	return command;
}

// Make list empty
void Application::MakeEmpty() {
	mList.MakeEmpty();
}

// Add new record into list.
int Application::AddMusic()
{
	// 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
	if (mList.IsFull())
	{
		cout << "List is full" << endl;
		return 0;
	}

	ItemType item;

	item.SetRecordFromKB();
	mList.Add(item);

	// 현재 list 출력
	DisplayAllMusic();

	return 1;
}

// Display all records in the list on screen.
void Application::DisplayAllMusic()
{
	ItemType data;

	cout << "\n\tCurrent list\n";
	cout << "\n\t=======================================\n\n";

	// list의 모든 데이터를 화면에 출력
	mList.ResetIterator();
	int curIndex = mList.GetNextItem(data);
	while (curIndex > -1)
	{
		data.DisplayRecordOnScreen();
		curIndex = mList.GetNextItem(data);
		cout << endl;
	}

	cout << "\n\t=======================================\n";
}

// Open a file by file descriptor as an input file.
int Application::OpenInFile(char* fileName)
{
	mInFile.open(fileName);	// file open for reading.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!mInFile)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char* fileName)
{
	mOutFile.open(fileName);	// file open for writing.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!mOutFile)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	ItemType data;	// 읽기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;
	cin.ignore();

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename))
		return 0;

	// 파일의 모든 내용을 읽어 list에 추가
	while (!mInFile.eof())
	{
		// array에 음악들의 정보가 들어있는 structure 저장
		data.ReadDataFromFile(mInFile);
		mList.Add(data);
	}

	mInFile.close();	// file close

	// 현재 list 출력
	DisplayAllMusic();

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType data;	// 쓰기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;
	cin.ignore();

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename))
		return 0;

	// list 포인터를 초기화
	mList.ResetIterator();

	// list의 모든 데이터를 파일에 쓰기
	int curIndex = mList.GetNextItem(data);
	while (curIndex > -1)
	{
		data.WriteDataToFile(mOutFile);
		curIndex = mList.GetNextItem(data);
	}

	mOutFile.close();	// file close

	return 1;
}

// Retrieve music information and display
void Application::SearchById() {
	// Object to temporarily hold id information
	ItemType data;
	// Get id to search in list
	data.SetIdFromKB();

	// Search in list
	int result = mList.Retrieve(data);
	if (result == 1) {
		// Found
		data.DisplayRecordOnScreen();
	}
	else {
		// Not found
		cout << "\n\tFailed to find data\n";
	}
}

// Search music with name
void Application::SearchByName() {
	// Object to temporarily hold name information
	ItemType data;
	// Get name to search
	data.SetNameFromKB();

	// Object to hold data from list
	ItemType item;
	// Iterate through list
	mList.ResetIterator();
	int curIndex = mList.GetNextItem(item);
	while (curIndex > -1)
	{
		// Check if retrieved item's artist is
		// substring of data's artist
		if (item.GetArtist().find(data.GetName())
			!= std::string::npos) {
			item.DisplayRecordOnScreen();
		}
		curIndex = mList.GetNextItem(item);
	}
}

// Search music with name
void Application::SearchByGenre() {
	// Object to temporarily hold name information
	ItemType data;
	// Get genre to search
	data.SetGenreFromKB();

	// Object to hold data from list
	ItemType item;
	// Iterate through list
	mList.ResetIterator();
	int curIndex = mList.GetNextItem(item);
	while (curIndex > -1){
		if (item.GetGenre() == data.GetGenre()) {
			item.DisplayRecordOnScreen();
		}
		curIndex = mList.GetNextItem(item);
	}
}

// Delete music from list.
void Application::DeleteMusic() {
	// Object to temporarily hold id information
	ItemType data;
	// Get id to delete
	data.SetIdFromKB();

	if (mList.Delete(data) != 1) {
		cout << "\n\tFailed to replace data\n";
	}
}

// Replace music with input.
void Application::ReplaceMusic() {
	// Object to temporarily hold record
	ItemType data;

	data.SetIdFromKB();
	data.SetRecordFromKB();

	if (mList.Replace(data) != 1) {
		cout << "\n\tFailed to replace data\n";
	}
}