#include "Application.h"


// Program driver.
void Application::Run()
{
	while (1)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:		// read a record and add to list.
			AddItem();
			break;
		case 2:		// display all the records in list on screen.
			DisplayAllItem();
			break;
		case 3:		// make empty list.
			m_List.MakeEmpty();
			break;
		case 4:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 5:		// save list data into a file.
			WriteDataToFile();
			break;
		case 6:
			SearchById();
			break;
		case 7:
			SearchById_BS();
			break;
		case 8:
			SearchByName();
			break;
		case 9:
			DeleteItem();
			break;
		case 10:
			ReplaceItem();
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
	cout << "\t   ID   Command" << endl;
	cout << "\t---------------------------------------" << endl;
	cout << "\t   1  : Add item" << endl;
	cout << "\t   2  : Print all on screen" << endl;
	cout << "\t   3  : Make empty list" << endl;
	cout << "\t   4  : Get from file" << endl;
	cout << "\t   5  : Put to file " << endl;
	cout << "\t   6  : Find with id" << endl;
	cout << "\t   7  : Find with id using binary search" << endl;
	cout << "\t   8  : Find with name" << endl;
	cout << "\t   9  : Delete" << endl;
	cout << "\t   10 : Replace" << endl;
	cout << "\t   0  : Quit" << endl;

	cout << endl << "\t   Choose a Command: ";
	cin >> command;
	cout << endl;

	return command;
}


// Add new record into list.
int Application::AddItem()
{
	// �Է¹��� ���ڵ带 ����Ʈ�� add, ����Ʈ�� full�� ���� add���� �ʰ� 0�� ����
	if (m_List.IsFull())
	{
		cout << "\t\nList is full\n";
		return 0;
	}

	ItemType item;

	item.SetRecordFromKB();
	m_List.Add(item);

	// ���� list ���
	DisplayAllItem();

	return 1;
}


// Display all records in the list on screen.
void Application::DisplayAllItem()
{
	ItemType data;

	cout << "\n\tCurrent list\n";
	cout << "\n\t=======================================\n\n";

	// list�� ��� �����͸� ȭ�鿡 ���
	m_List.ResetIterator();
	int curIndex = m_List.GetNextItem(data);
	while (curIndex > -1)
	{
		data.DisplayRecordOnScreen();
		curIndex = m_List.GetNextItem(data);
	}
	
	cout << "\n\t=======================================\n";
}


// Open a file by file descriptor as an input file.
int Application::OpenInFile(char* fileName)
{
	m_InFile.open(fileName);	// file open for reading.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_InFile)	return 0;
	else	return 1;
}


// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char* fileName)
{
	m_OutFile.open(fileName);	// file open for writing.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_OutFile)	return 0;
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

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenInFile(filename))
		return 0;

	// ������ ��� ������ �о� list�� �߰�
	while (!m_InFile.eof())
	{
		// array�� �л����� ������ ����ִ� structure ����
		data.ReadDataFromFile(m_InFile);
		m_List.Add(data);
	}

	m_InFile.close();	// file close

	// ���� list ���
	DisplayAllItem();

	return 1;
}


// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType data;	// ����� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenOutFile(filename))
		return 0;

	// list �����͸� �ʱ�ȭ
	m_List.ResetIterator();

	// list�� ��� �����͸� ���Ͽ� ����
	int curIndex = m_List.GetNextItem(data);
	while (curIndex > -1)
	{
		data.WriteDataToFile(m_OutFile);
		curIndex = m_List.GetNextItem(data);
	}

	m_OutFile.close();	// file close

	return 1;
}


// Retrieve student information and display
void Application::SearchById(){
	// Object to temporarily hold id information
	ItemType data;
	// Get id to search in list
	data.SetIdFromKB();

	// Search in list
	int result = m_List.Retrieve_Seq(data);
	if (result == 1) {
		// Found
		data.DisplayRecordOnScreen();
	}
	else {
		// Not found
		cout << "\n\tFailed to find data\n";
	}
}


// Same as SearchByID(), but using binary search
void Application::SearchById_BS() {
	// Object to temporarily hold id information
	ItemType data;
	// Get id to search
	data.SetIdFromKB();
	// Get data from list using binary search

	int result = m_List.Retrieve_BS(data);
	if (result == 1) {
		data.DisplayRecordOnScreen();
	}
	else {
		cout << "\n\tFailed to find data\n";
	}
}


// DeleteItem student from list.
void Application::DeleteItem() {
	// Object to temporarily hold id information
	ItemType data;
	// Get id to delete
	data.SetIdFromKB();
	
	if (m_List.Delete(data) != 1) {
		cout << "\n\tFailed to replace data\n";
	}
}


// ReplaceItem student with input.
void Application::ReplaceItem(){
	// Object to temporarily hold record
	ItemType data;
	// Get record to replace
	data.SetRecordFromKB();
	
	if (m_List.Replace(data) != 1) {
		cout << "\n\tFailed to replace data\n";
	}
}


// Search data with name
void Application::SearchByName(){
	// Object to temporarily hold name information
	ItemType data;
	// Get name to search
	data.SetNameFromKB();

	// Object to hold data from list
	ItemType item;
	// Iterate through list
	m_List.ResetIterator();
	int curIndex = m_List.GetNextItem(item);
	while (curIndex > -1)
	{
		// Check if retrieved item's name is
		// substring of data's name
		if (item.GetName().find(data.GetName())
			!= std::string::npos) {
			item.DisplayRecordOnScreen();
		}
		curIndex = m_List.GetNextItem(item);
	}
}

