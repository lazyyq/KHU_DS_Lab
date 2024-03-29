#pragma once

#include <fstream>
#include <json/json.h>

#include "DoublyNodeType.h"
#include "DoublyIterator.h"

template<typename T>
class DoublyIterator;

template <typename T>
class DoublyLinkedList;

template<typename T>
std::ifstream &operator>>(std::ifstream &ifs, DoublyLinkedList<T> &list);
template<typename T>
std::ofstream &operator<<(std::ofstream &ofs, const DoublyLinkedList<T> &list);
template<typename T>
Json::Value &operator>>(Json::Value &out, DoublyLinkedList<T> &list);
template<typename T>
Json::Value &operator<<(Json::Value &out, const DoublyLinkedList<T> &list);

/**
*	정렬된 더블연결리스트 클래스
*/
template <typename T>
class DoublyLinkedList {
	friend class DoublyIterator<T>; // DoublyIterator와 친구 클래스.
public:
	/**
	*	디폴트 생성자.
	*/
	DoublyLinkedList();

	/**
	*	Copy constructor.
	*/
	DoublyLinkedList<T>(const DoublyLinkedList<T> &that);

	/**
	*	소멸자.
	*/
	~DoublyLinkedList();

	/**
	*	Assignment operator.
	*/
	DoublyLinkedList<T> &operator=(const DoublyLinkedList<T> &that);

	/**
	*	@brief	리스트가 비었는지 아닌지 검사한다.
	*	@pre	m_nLength가 값을 가지고 있어야 한다.
	*	@post	비었는지 아닌지를 알려준다.
	*	@return	비어있으면 true, 아니면 false를 반환.
	*/
	bool IsEmpty() const;

	/**
	*	@brief	리스트가 가득 찼는지 아닌지 검사한다.
	*	@pre	m_nLength가 값을 가지고 있어야 한다.
	*	@post	가득 찼는지 아닌지를 알려준다.
	*	@return	가득 차있으면 true, 아니면 false를 반환.
	*/
	bool IsFull() const;

	/**
	*	@brief	리스트를 비운다.
	*	@pre	없음.
	*	@post	m_pFirst와 m_pLast를 제외한 모든 데이터를 지운다.
	*/
	void MakeEmpty();

	/**
	*	@brief	리스트의 길이를 반환한다.
	*	@pre	없음.
	*	@post	리스트의 길이를 반환.
	*	@return	mLength 리스트의 길이 반환.
	*/
	int GetLength() const;

	/**
	*	@brief	새로운 아이템을 리스트에 추가한다.
	*	@pre	item을 입력받는다.
	*	@post	아이템을 리스트에 추가한다.
	*	@return	같은 아이템이 있으면 0을 반환하고, 입력에 성공하면 1을 반환.
	*/
	int Add(T item);

	/**
	*	@brief	입력받은 아이템을 리스트에서 삭제한다.
	*	@pre	item을 입력받는다.
	*	@post	입력받은 아이템을 리스트에서 찾아 삭제한다.
	*/
	int Delete(T item);

	/**
	*	@brief	입력받은 아이템으로 정보를 바꾼다.
	*	@pre	item을 입력받는다.
	*	@post	새로운 정보로 교체된다.
	*/
	void Replace(T item);

	/**
	*	@brief	입력받은 아이템의 정보와 비교하여 같은 리스트의 아이템을 가져온다.
	*	@pre	item을 입력받는다.
	*	@post	검색된 데이터를 아이템에 넣는다.
	*	@return	일치하는 데이터를 찾으면 1, 그렇지 않으면 0을 반환.
	*/
	int Get(T &item) const;

	/**
	*	@brief	Read record from file written in JSON format.
	*/
	friend std::ifstream &operator>> <>(std::ifstream &ifs,
		DoublyLinkedList<T> &list);

	/**
	*	@brief	Write record to file in JSON format.
	*/
	friend std::ofstream &operator<< <>(std::ofstream &ofs,
		const DoublyLinkedList<T> &list);

	/**
	*	@brief	Read record from JSON.
	*/
	friend Json::Value &operator>> <>(Json::Value &root,
		DoublyLinkedList<T> &list);

	/**
	*	@brief	Write record to JSON.
	*/
	friend Json::Value &operator<< <>(Json::Value &root,
		const DoublyLinkedList<T> &list);

private:
	DoublyNodeType<T> *mFirst; // 리스트의 맨 처음.
	DoublyNodeType<T> *mLast; // 리스트의 맨 끝.
	int mLength; // 리스트의 길이.
};

// 리스트의 맨 처음과 끝이 서로를 가리키게 설정하고 리스트의 길이를 0으로 초기화시켜놓는다.
template <typename T>
DoublyLinkedList<T> ::DoublyLinkedList() {
	mFirst = new DoublyNodeType<T>;
	mLast = new DoublyNodeType<T>;

	mFirst->next = mLast; // 끝과 처음이 서로를 가리키게 초기화.
	mFirst->prev = NULL; // 처음.

	mLast->next = NULL; // 끝.
	mLast->prev = mFirst; // 끝과 처음이 서로를 가리키게 초기화.

	mLength = 0; // 길이는 0.
}

// Copy constructor
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(
	const DoublyLinkedList<T> &that) {
	mFirst = new DoublyNodeType<T>;
	mLast = new DoublyNodeType<T>;

	mFirst->next = mLast; // 끝과 처음이 서로를 가리키게 초기화.
	mFirst->prev = NULL; // 처음.

	mLast->next = NULL; // 끝.
	mLast->prev = mFirst; // 끝과 처음이 서로를 가리키게 초기화.

	mLength = that.mLength;

	// Deep copy.
	T dataToCopy;
	// 현재 리스트와 복사 대상 리스트의 iterator
	DoublyIterator<T> iterThis(*this), iterThat(that);
	iterThis.Next(); dataToCopy = iterThat.Next();
	while (iterThat.NextNotNull()) {
		// 새 노드를 만들고 데이터 복사해옴
		DoublyNodeType<T> *newNode = new DoublyNodeType<T>;
		newNode->data = dataToCopy;
		// 새 노드를 이전 노드와 연결
		iterThis.mCurPointer->prev->next = newNode;
		newNode->prev = iterThis.mCurPointer->prev;
		// 새 노드를 다음 노드와 연결
		newNode->next = iterThis.mCurPointer;
		iterThis.mCurPointer->prev = newNode;

		dataToCopy = iterThat.Next();
	}
}

// 소멸자.
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	delete mFirst;
	delete mLast;
}

// Assignment operator
template<typename T>
DoublyLinkedList<T>
&DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &that) {
	// self-assignment 검사
	if (this == &that) {
		return *this;
	}

	MakeEmpty();

	mLength = that.mLength;

	// Deep copy
	T dataToCopy;
	// 현재 리스트와 복사 대상 리스트의 iterator
	DoublyIterator<T> iterThis(*this), iterThat(that);
	iterThis.Next(); dataToCopy = iterThat.Next();
	while (iterThat.NextNotNull()) {
		// 새 노드를 만들고 데이터 복사해옴
		DoublyNodeType<T> *newNode = new DoublyNodeType<T>;
		newNode->data = dataToCopy;
		// 새 노드를 이전 노드와 연결
		iterThis.mCurPointer->prev->next = newNode;
		newNode->prev = iterThis.mCurPointer->prev;
		// 새 노드를 다음 노드와 연결
		newNode->next = iterThis.mCurPointer;
		iterThis.mCurPointer->prev = newNode;

		dataToCopy = iterThat.Next();
	}

	return *this;
}

// 리스트가 비었는지 검사한다.
template <typename T>
bool DoublyLinkedList<T>::IsEmpty() const {
	if (mLength == 0)
		return true;
	else
		return false;
}

// 리스트가 꽉 차있는지 검사한다.
template <typename T>
bool DoublyLinkedList<T>::IsFull() const {
	return false;
}

// 리스트를 비운다.
template <typename T>
void DoublyLinkedList<T>::MakeEmpty() {
	DoublyNodeType<T> *pItem;
	DoublyIterator<T> itor(*this);
	itor.Next(); // 다음으로 이동.

	while (itor.NextNotNull()) {
		pItem = itor.mCurPointer;
		itor.Next(); // 현재 포인터를 다음으로 이동.
		delete pItem;
	}

	mFirst->next = mLast;
	mFirst->prev = NULL;
	mLast->prev = mFirst;
	mLast->next = NULL;

	mLength = 0;

	return;
}

// 리스트의 길이를 반환한다.
template <typename T>
int DoublyLinkedList<T>::GetLength() const {
	return mLength;
}

// 아이템을 입력받아 리스트의 맞는 자리를 찾아 삽입한다.
template <typename T>
int DoublyLinkedList<T>::Add(T item) {
	DoublyIterator<T> itor(*this);
	itor.Next(); // 다음으로 이동.

	if (IsEmpty()) // 처음 삽입할 때
	{
		DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
		pItem->data = item;
		mFirst->next = pItem;
		pItem->prev = mFirst;
		pItem->next = mLast;
		mLast->prev = pItem; // 처음과 끝 사이에 삽입.
		mLength++;
		return 1;
	} else // 처음이 아닐 때
	{
		while (true) {
			if (!itor.NextNotNull()) // 마지막 자리를 찾는다.
			{
				DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
				pItem->data = item;
				pItem->prev = itor.mCurPointer->prev;
				pItem->next = itor.mCurPointer;
				itor.mCurPointer->prev->next = pItem;
				itor.mCurPointer->prev = pItem; // 아이템을 삽입.
				mLength++;
				return 1;
			}
			//else if (item == itor.mCurPointer->data) // 같은 정보의 아이템이 있으면
			//	return 0; // 0을 반환.
			else
				itor.Next(); // 다음으로 이동.
		}
	}
}

// 입력받은 아이템을 데이터에서 찾아내어 삭제한다.
template <typename T>
int DoublyLinkedList<T>::Delete(T item) {
	if (IsEmpty()) {
		return 0;
	}

	DoublyIterator<T> itor(*this);
	itor.Next(); // 다음으로 이동.

	bool found = false;
	while (itor.mCurPointer != mLast) {
		if (itor.mCurPointer->data == item) // 일치하는 데이터를 찾는다.
		{
			found = true;
			DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
			pItem = itor.mCurPointer;
			itor.Next();
			pItem->prev->next = itor.mCurPointer;
			itor.mCurPointer->prev = pItem->prev; // 삭제하는 노드의 앞과 뒤를 서로 이어준다.
			delete pItem; // 삭제.
			break;
		} else
			itor.Next();
	}
	if (found) {
		mLength--; // 길이 감소.
		return 1;
	}
	return 0;
}

// 입력받은 아이템의 정보를 교체한다.
template <typename T>
void DoublyLinkedList<T>::Replace(T item) {
	DoublyIterator<T> itor(*this);
	itor.Next(); // 다음으로 이동.

	while (itor.mCurPointer != mLast) {
		if (itor.mCurPointer->data == item) {
			itor.mCurPointer->data = item; // 정보를 교체.
			return;
		} else
			itor.Next();
	}

	return;
}

// 입력받은 아이템과 일치하는 아이템을 리스트에서 찾아 가져온다.
template <typename T>
int DoublyLinkedList<T>::Get(T &item) const {
	DoublyIterator<T> itor(*this);
	itor.Next();

	while (itor.mCurPointer != mLast) {
		if (itor.mCurPointer->data == item) {
			item = itor.mCurPointer->data;
			return 1; // 일치하면 1을 반환.
		} else
			itor.Next(); // 다음으로 이동.
	}

	return 0; // 일치하지 않으면 0을 반환.
}

// JSON 형식의 파일로부터 아이템들을 읽어들임
template <typename T>
std::ifstream &operator>>(std::ifstream &ifs,
	DoublyLinkedList<T> &list) {
	Json::Value root;
	ifs >> root;
	root >> list;

	return ifs;
}

// 파일에 JSON 형식으로 아이템들을 기록함
template <typename T>
std::ofstream &operator<<(std::ofstream &ofs,
	const DoublyLinkedList<T> &list) {
	Json::Value root;
	root << list;
	ofs << root;

	return ofs;
}

// JSON으로부터 아이템들을 읽어들임
template <typename T>
Json::Value &operator>>(Json::Value &root,
	DoublyLinkedList<T> &list) {
	// JSON root의 각 아이템을 리스트에 추가
	for (auto &e : root) {
		T item;
		e >> item;
		list.Add(item);
	}

	return root;
}

// JSON에 아이템들을 기록함
template <typename T>
Json::Value &operator<<(Json::Value &root,
	const DoublyLinkedList<T> &list) {
	// 새 JSON value를 만들어 리스트의 아이템을 추가한 뒤 root에 추가
	DoublyIterator<T> iter(list);
	for (T item = iter.Next(); iter.NextNotNull(); item = iter.Next()) {
		Json::Value value;
		value << item;
		root.append(value);
	}

	return root;
}
