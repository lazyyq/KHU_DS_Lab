#include "Application.h"

// Program driver.
void Application::Run()
{
	while (1)
	{
		mCommand = GetCommand();

		switch (mCommand)
		{
		case 1:		// �� ������ �Է� �޾� ����Ʈ�� �߰�
			AddMusic();
			break;
		case 2:		// ���� ������ȣ�� �Է� �޾� ����Ʈ���� ����
			DeleteMusic();
			break;
		case 3:		// �� ������ �Է� �޾Ƽ� ����Ʈ���� �ش� �� ������ ����	
			ReplaceMusic();
			break;
		case 4:		// �Էµ� ID�� ����Ʈ���� ���� ã�Ƽ� ȭ�鿡 ���
			SearchById();
			break;
		case 5:		// �Էµ� ���� �̸����� ����Ʈ���� ���� ã�Ƽ� ȭ�鿡 ���
			SearchByName();
			break;
		case 6:		// ����Ʈ�� ����� ��� ���� ȭ�鿡 ���
			DisplayAllMusic();
			break;
		case 7: 		// ����Ʈ�� �Էµ� ��� ���� ����
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
	// �Է¹��� ���ڵ带 ����Ʈ�� add, ����Ʈ�� full�� ���� add���� �ʰ� 0�� ����
	if (mList.IsFull())
	{
		cout << "List is full" << endl;
		return 0;
	}

	ItemType item;

	item.SetRecordFromKB();
	mList.Add(item);

	// ���� list ���
	DisplayAllMusic();

	return 1;
}

// Display all records in the list on screen.
void Application::DisplayAllMusic()
{
	ItemType data;

	cout << "\n\tCurrent list\n";
	cout << "\n\t=======================================\n\n";

	// list�� ��� �����͸� ȭ�鿡 ���
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

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!mInFile)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char* fileName)
{
	mOutFile.open(fileName);	// file open for writing.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!mOutFile)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	ItemType data;	// �б�� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;
	cin.ignore();

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenInFile(filename))
		return 0;

	// ������ ��� ������ �о� list�� �߰�
	while (!mInFile.eof())
	{
		// array�� ���ǵ��� ������ ����ִ� structure ����
		data.ReadDataFromFile(mInFile);
		mList.Add(data);
	}

	mInFile.close();	// file close

	// ���� list ���
	DisplayAllMusic();

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType data;	// ����� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;
	cin.ignore();

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenOutFile(filename))
		return 0;

	// list �����͸� �ʱ�ȭ
	mList.ResetIterator();

	// list�� ��� �����͸� ���Ͽ� ����
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