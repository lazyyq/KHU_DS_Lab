#include "Application.h"

Application::Application() {
	mCommand = 0;
}

// Program driver.
void Application::Run() {
	while (1) {
		mCommand = GetCommand();

		switch (mCommand) {
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
		case 5:		// �Էµ� �� �̸����� ����Ʈ���� ���� ã�Ƽ� ȭ�鿡 ���
			SearchByName();
			break;
		case 6:		// �Էµ� ���� �̸����� ����Ʈ���� ���� ã�Ƽ� ȭ�鿡 ���
			SearchByArtist();
			break;
		case 7:		// �Էµ� �帣 �̸����� ����Ʈ���� ���� ã�Ƽ� ȭ�鿡 ���
			SearchByGenre();
			break;
		case 8:		// ����Ʈ�� ����� ��� ���� ȭ�鿡 ���
			DisplayAllMusic();
			break;
		case 9: 		// ����Ʈ�� �Էµ� ��� ���� ����
			MakeEmpty();
			break;
		case 10:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 11:		// save list data into a file.
			WriteDataToFile();
			break;
		case 0:
			return;
		default:
			cout << "\n\tIllegal selection. Please choose between 0-11!\n";
			break;
		}
	}
}

// Display command on screen and get a input from keyboard.
int Application::GetCommand() {
	int command;
	cout << endl << endl << endl;
	cout << "\t-- ID -- Command -------------\n\n";
	cout << "\t    1  : Add music\n";
	cout << "\t    2  : Delete music\n";
	cout << "\t    3  : Replace music\n";
	cout << "\t    4  : Find music by ID\n";
	cout << "\t    5  : Find music by name\n";
	cout << "\t    6  : Find music by artist\n";
	cout << "\t    7  : Find music by genre\n";
	cout << "\t    8  : Display all music\n";
	cout << "\t    9  : Empty list\n";
	cout << "\t    10 : Read list from file\n";
	cout << "\t    11 : Write list to file\n";
	cout << "\t    0  : Quit\n\n";
	cout << "\t------------------------------\n";

	cout << "\n\t    Choose a command : ";
	cin >> command;
	if (cin.fail() == 1) { // Input error, input is probably not int.
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

	cout << "\n\n\tEmptied list.\n";
}

// Add new record into list.
int Application::AddMusic() {
	// �Է¹��� ���ڵ带 ����Ʈ�� add, ����Ʈ�� full�� ���� add���� �ʰ� 0�� ����
	if (mList.IsFull()) {
		cout << "\n\n\tList is full.\n";
		return 0;
	}

	ItemType data; // Temporary variable to hold info

	cout << "\n\n\tPlease input new music data."
		<< " Duplicate data is not allowed.\n";
	// Get new music info from keyboard
	data.SetRecordFromKB();

	int result = mList.Add(data);
	if (result != 1) { // Add failed
		cout << "\n\tFailed to add data. Probably duplicate?\n";
		return 0;
	}

	cout << "\n\tSuccessfully added new data.\n";

	// ���� list ���
	DisplayAllMusic();

	return 1;
}

// Display all records in the list on screen.
void Application::DisplayAllMusic() {
	ItemType data; // Temporary variable to hold info

	// Display current list capacity
	cout << "\n\n\tCurrent list (" << mList.GetLength()
		<< "/" << MAXSIZE << ")\n";
	cout << "\n\t=======================================\n";

	// Print all data in list
	mList.ResetIterator(); // Reset pointer
	int curIndex = mList.GetNextItem(data);
	if (curIndex > -1) { // Print first item
		cout << "\n\tMusic #" << (curIndex + 1) << "\n\n";
		data.DisplayRecordOnScreen();
		curIndex = mList.GetNextItem(data);
	}
	while (curIndex > -1) { // Print rest
		cout << "\n\t---------------------------------------\n";
		cout << "\n\tMusic #" << (curIndex + 1) << "\n\n";
		data.DisplayRecordOnScreen();
		curIndex = mList.GetNextItem(data);
	}

	cout << "\n\t=======================================\n";
}

// Open a file by file descriptor as an input file.
int Application::OpenInFile(char* fileName) {
	mInFile.open(fileName);	// file open for reading.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!mInFile)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char* fileName) {
	mOutFile.open(fileName);	// file open for writing.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!mOutFile)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile() {
	int index = 0;
	ItemType data;	// �б�� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\n\tEnter Input file Name : ";
	cin >> filename;
	cin.ignore();

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenInFile(filename)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// ������ ��� ������ �о� list�� �߰�
	while (!mInFile.eof()) {
		// array�� ���ǵ��� ������ ����ִ� structure ����
		data.ReadDataFromFile(mInFile);
		mList.Add(data);
	}

	mInFile.close();	// file close

	// ���� list ���
	DisplayAllMusic();

	cout << "\n\tSuccessfully imported from file.\n";
	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile() {
	ItemType data;	// ����� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\n\tEnter Output file Name : ";
	cin >> filename;
	cin.ignore();

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenOutFile(filename)) {
		cout << "\n\tError while opening file.\n";
		return 0;
	}

	// list �����͸� �ʱ�ȭ
	mList.ResetIterator();

	// list�� ��� �����͸� ���Ͽ� ����
	int curIndex = mList.GetNextItem(data);
	while (curIndex > -1) {
		data.WriteDataToFile(mOutFile);
		curIndex = mList.GetNextItem(data);
	}

	mOutFile.close();	// file close

	cout << "\n\tSuccessfully exported to file.\n";
	return 1;
}

// Retrieve music information and display
void Application::SearchById() {
	ItemType data; // Temporary variable to hold info
	data.SetIdFromKB(); // Get id to search in list

	// Search in list
	int result = mList.Retrieve(data);
	if (result == 1) { // Found
		data.DisplayRecordOnScreen();
	}
	else {	// Not found
		cout << "\n\n\tFailed to find data\n";
	}
}

// Search music with name
void Application::SearchByName() {
	ItemType data;// Temporary variable to hold info
	data.SetNameFromKB(); // Get name to search

	bool found = false; // Remember whether we've found at least one

	// Object to hold data from list
	ItemType dataFromList;
	// Iterate through list
	mList.ResetIterator();
	int curIndex = mList.GetNextItem(dataFromList);
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
		curIndex = mList.GetNextItem(dataFromList);
	}

	if (!found) {
		cout << "\n\n\tFailed to find data.\n";
	}
}

// Search music with artist
void Application::SearchByArtist() {
	ItemType data; // Temporary varilable to hold info
	data.SetArtistFromKB(); // Get artist to search

	bool found = false; // Remember whether we've found at least one

	// Object to hold data from list
	ItemType dataFromList;
	// Iterate through list
	mList.ResetIterator();
	int curIndex = mList.GetNextItem(dataFromList);
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
		curIndex = mList.GetNextItem(dataFromList);
	}

	if (!found) {
		cout << "\n\n\tFailed to find data.\n";
	}
}

// Search music with name
void Application::SearchByGenre() {
	ItemType data; // Temporary varilable to hold info
	data.SetGenreFromKB(); // Get genre to search

	bool found = false; // Remember whether we've found at least one

	// Object to hold data from list
	ItemType dataFromList;
	// Iterate through list
	mList.ResetIterator();
	int curIndex = mList.GetNextItem(dataFromList);
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
		curIndex = mList.GetNextItem(dataFromList);
	}
}

// Delete music from list.
void Application::DeleteMusic() {
	ItemType data; // Temporary variable to hold info
	data.SetIdFromKB(); // Get id to delete

	if (mList.Delete(data) == 1) { // Success
		cout << "\n\n\tSuccessfully deleted data.\n";
	}
	else { // Failed
		cout << "\n\n\tFailed to delete data.\n";
	}
}

// Replace music with input.
void Application::ReplaceMusic() {
	ItemType data; // Temporary variable to hold info

	data.SetIdFromKB(); // Get id to search
	data.SetRecordFromKB(); // Get the rest info to search

	if (mList.Replace(data) == 1) { // Success
		cout << "\n\n\tSuccessfully replaced data.\n";
	}
	else { // Failed
		cout << "\n\n\tFailed to replace data.\n";
	}
}