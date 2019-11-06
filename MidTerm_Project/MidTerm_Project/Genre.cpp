#include "Genre.h"

// Constructors
Genre::Genre() {
	mName = " ";
}

Genre::Genre(const string &inName) {
	mName = inName;
}

// Destructor
Genre::~Genre() {
	// Clean linked list
	mSongList.MakeEmpty();
}

// Get name
string Genre::GetName() {
	return mName;
}

// Set name
void Genre::SetName(string &inName) {
	mName = inName;
}

// Set name from keyboard input
void Genre::SetNameFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Genre name (String) : ";
	getline(cin, mName);
}

// Add song to song list
int Genre::AddSong(const SimpleItem &song) {
	return this->mSongList.Add(song);
}

// Remove song from song list
int Genre::RemoveSong(const SimpleItem &song) {
	return mSongList.Delete(song);
}

const SortedDoublyLinkedList<SimpleItem> &Genre::GetSongList() {
	return mSongList;
}

// Compare operators
bool Genre::operator==(const Genre &that) const {
	return this->mName.compare(that.mName) == 0;
}

bool Genre::operator!=(const Genre &that) const {
	return !(*this == that);
}

bool Genre::operator<(const Genre &that) const {
	return this->mName.compare(that.mName) < 0;
}

bool Genre::operator<=(const Genre &that) const {
	return this->mName.compare(that.mName) <= 0;
}

bool Genre::operator>(const Genre &that) const {
	return this->mName.compare(that.mName) > 0;
}

bool Genre::operator>=(const Genre &that) const {
	return this->mName.compare(that.mName) >= 0;
}

// ���Ϸκ��� �б�
ifstream &operator>>(ifstream &ifs, Genre &item) {
	string temp;

	// ������ ù���� Name
	getline(ifs, item.mName);
	while (item.mName.length() == 0) {
		// Skip empty lines.
		getline(ifs, item.mName);
	}

	// �� ���� �ٺ��ʹ� ���� ���� ���̵�, �̸�, �������� ����������.
	// ������ ������ �� ���� ����.
	SimpleItem simple; // ����Ʈ�� �߰��� ����
	getline(ifs, temp);
	while (temp.length() != 0) { // ������ �߰ߵɶ�����, �� ����������
		simple.SetId(temp);
		getline(ifs, temp);
		simple.SetName(temp);
		getline(ifs, temp);
		simple.SetArtist(temp);
		item.AddSong(simple);

		getline(ifs, temp);
	}

	return ifs;
}

// ���Ͽ� ����
ofstream &operator<<(ofstream &ofs, const Genre &item) {
	ofs << endl << endl << endl;
	ofs << item.mName.c_str();

	// �� ����Ʈ ���� ����
	SimpleItem simple;
	DoublyIterator<SimpleItem> iter(item.mSongList); // Iterator
	simple = iter.Next();
	while (iter.NextNotNull()) {
		ofs << endl;
		ofs << simple.GetId().c_str() << endl;
		ofs << simple.GetName().c_str() << endl;
		ofs << simple.GetArtist().c_str();
		simple = iter.Next();
	}
	ofs << endl;

	return ofs;
}