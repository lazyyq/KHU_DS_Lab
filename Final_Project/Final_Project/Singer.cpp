#include "Singer.h"

// Constructors
Singer::Singer() {
	mName = " ";
	mAge = -1;
	mSex = ' ';
}

Singer::Singer(const string &inName,
	const int inAge, const char &inSex) {
	mName = inName;
	mAge = inAge;
	mSex = inSex;
}

// Destructor
Singer::~Singer() {
	// Clean linked list
	mSongList.MakeEmpty();
}

// Get name
string Singer::GetName() {
	return mName;
}

// Get age
int Singer::GetAge() {
	return mAge;
}

// Get sex
char Singer::GetSex() {
	return mSex;
}

// Set name
void Singer::SetName(string &inName) {
	mName = inName;
}

// Set age
void Singer::SetAge(int inAge) {
	mAge = inAge;
}

// Set sex
void Singer::SetSex(char inSex) {
	mSex = inSex;
}

// Set info from keyboard input
void Singer::SetInfoFromKB() {
	SetNameFromKB();
	SetAgeFromKB();
	SetSexFromKB();
}

// Set name from keyboard input
void Singer::SetNameFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Singer name (String) : ";
	getline(cin, mName);
}

// Set age from keyboard input
void Singer::SetAgeFromKB() {
	while (true) {
		cout << "\t" << setw(attrIndentSize) << "Singer age (Int) : ";
		cin >> mAge;

		// Check if input is integer.
		int result = cin.fail();
		cin.clear();
		cin.ignore(100, '\n');

		if (result != 1) {
			// Success
			break;
		} else {
			cout << "Wrong input!\n";
		}
	}
}

// Set sex from keyboard input
void Singer::SetSexFromKB() {
	cout << "\t" << setw(attrIndentSize) << "Singer sex (Char) : ";
	cin >> mSex;
	cin.ignore(100, '\n');
}

// Add song to song list
int Singer::AddSong(const SimpleItem &song) {
	return this->mSongList.Add(song);
}

// Remove song from song list
int Singer::RemoveSong(const SimpleItem &song) {
	return mSongList.Delete(song);
}

const SortedDoublyLinkedList<SimpleItem> &Singer::GetSongList() {
	return mSongList;
}

// Compare operators
bool Singer::operator==(const Singer &that) const {
	return this->mName.compare(that.mName) == 0;
}

bool Singer::operator!=(const Singer &that) const {
	return !(*this == that);
}

bool Singer::operator<(const Singer &that) const {
	return this->mName.compare(that.mName) < 0;
}

bool Singer::operator<=(const Singer &that) const {
	return this->mName.compare(that.mName) <= 0;
}

bool Singer::operator>(const Singer &that) const {
	return this->mName.compare(that.mName) > 0;
}

bool Singer::operator>=(const Singer &that) const {
	return this->mName.compare(that.mName) >= 0;
}

// 파일로부터 읽어오기.
// 파일의 첫째줄은 가수이름, 둘째줄은 나이, 셋째줄은 성별,
// 그 다음줄부터 공백을 만날때까지는 가수가 취입한 곡 아이디.
ifstream &operator>>(ifstream &ifs, Singer &item) {
	string temp;

	getline(ifs, item.mName); // 이름
	while (item.mName.length() == 0) {
		// Skip empty lines.
		getline(ifs, item.mName);
	}
	getline(ifs, temp);
	item.mAge = stoi(temp); // 나이
	getline(ifs, temp);
	item.mSex = temp[0]; // 성별

	SimpleItem simple;
	getline(ifs, temp);
	while (temp.length() != 0) { // 빈줄 발견될때까지
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

// 파일에 저장
ofstream &operator<<(ofstream &ofs, const Singer &item) {
	ofs << endl << endl << endl;
	ofs << item.mName << endl;
	ofs << item.mAge << endl;
	ofs << item.mSex;

	// 곡 리스트 저장 시작
	SimpleItem simple;
	SortedDoublyIterator<SimpleItem> iter(item.mSongList); // Iterator
	simple = iter.Next();
	while (iter.NextNotNull()) {
		ofs << endl;
		ofs << simple.GetId() << endl;
		ofs << simple.GetName() << endl;
		ofs << simple.GetArtist();
		simple = iter.Next();
	}
	ofs << endl;

	return ofs;
}
