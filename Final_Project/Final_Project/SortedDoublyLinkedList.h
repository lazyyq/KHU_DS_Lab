#pragma once

#include "DoublyNodeType.h"
#include "SortedDoublyIterator.h"

template<typename T>
class SortedDoublyIterator;

/**
*	���ĵ� �����Ḯ��Ʈ Ŭ����
*/
template <typename T>
class SortedDoublyLinkedList {
	friend class SortedDoublyIterator<T>; // SortedDoublyIterator�� ģ�� Ŭ����.
public:
	/**
	*	����Ʈ ������.
	*/
	SortedDoublyLinkedList();

	/**
	*	Copy constructor.
	*/
	SortedDoublyLinkedList<T>(const SortedDoublyLinkedList<T> &that);

	/**
	*	�Ҹ���.
	*/
	~SortedDoublyLinkedList();

	/**
	*	Assignment operator.
	*/
	SortedDoublyLinkedList<T> &operator=(const SortedDoublyLinkedList<T> &that);

	/**
	*	@brief	����Ʈ�� ������� �ƴ��� �˻��Ѵ�.
	*	@pre	m_nLength�� ���� ������ �־�� �Ѵ�.
	*	@post	������� �ƴ����� �˷��ش�.
	*	@return	��������� true, �ƴϸ� false�� ��ȯ.
	*/
	bool IsEmpty() const;

	/**
	*	@brief	����Ʈ�� ���� á���� �ƴ��� �˻��Ѵ�.
	*	@pre	m_nLength�� ���� ������ �־�� �Ѵ�.
	*	@post	���� á���� �ƴ����� �˷��ش�.
	*	@return	���� �������� true, �ƴϸ� false�� ��ȯ.
	*/
	bool IsFull() const;

	/**
	*	@brief	����Ʈ�� ����.
	*	@pre	����.
	*	@post	m_pFirst�� m_pLast�� ������ ��� �����͸� �����.
	*/
	void MakeEmpty();

	/**
	*	@brief	����Ʈ�� ���̸� ��ȯ�Ѵ�.
	*	@pre	����.
	*	@post	����Ʈ�� ���̸� ��ȯ.
	*	@return	mLength ����Ʈ�� ���� ��ȯ.
	*/
	int GetLength() const;

	/**
	*	@brief	���ο� �������� ����Ʈ�� �߰��Ѵ�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	�������� ����Ʈ�� �߰��Ѵ�.
	*	@return	���� �������� ������ 0�� ��ȯ�ϰ�, �Է¿� �����ϸ� 1�� ��ȯ.
	*/
	int Add(T item);

	/**
	*	@brief	�Է¹��� �������� ����Ʈ���� �����Ѵ�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	�Է¹��� �������� ����Ʈ���� ã�� �����Ѵ�.
	*/
	int Delete(T item);

	/**
	*	@brief	�Է¹��� ���������� ������ �ٲ۴�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	���ο� ������ ��ü�ȴ�.
	*/
	void Replace(T item);

	/**
	*	@brief	�Է¹��� �������� ������ ���Ͽ� ���� ����Ʈ�� �������� �����´�.
	*	@pre	item�� �Է¹޴´�.
	*	@post	�˻��� �����͸� �����ۿ� �ִ´�.
	*	@return	��ġ�ϴ� �����͸� ã���� 1, �׷��� ������ 0�� ��ȯ.
	*/
	int Get(T &item) const;

private:
	DoublyNodeType<T> *mFirst; // ����Ʈ�� �� ó��.
	DoublyNodeType<T> *mLast; // ����Ʈ�� �� ��.
	int mLength; // ����Ʈ�� ����.
};

// ����Ʈ�� �� ó���� ���� ���θ� ����Ű�� �����ϰ� ����Ʈ�� ���̸� 0���� �ʱ�ȭ���ѳ��´�.
template <typename T>
SortedDoublyLinkedList<T> ::SortedDoublyLinkedList() {
	mFirst = new DoublyNodeType<T>;
	mLast = new DoublyNodeType<T>;

	mFirst->next = mLast; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.
	mFirst->prev = nullptr; // ó��.

	mLast->next = nullptr; // ��.
	mLast->prev = mFirst; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.

	mLength = 0; // ���̴� 0.
}

// Copy constructor
template<typename T>
SortedDoublyLinkedList<T>::SortedDoublyLinkedList(
	const SortedDoublyLinkedList<T> &that) {
	mFirst = new DoublyNodeType<T>;
	mLast = new DoublyNodeType<T>;

	mFirst->next = mLast; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.
	mFirst->prev = nullptr; // ó��.

	mLast->next = nullptr; // ��.
	mLast->prev = mFirst; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.

	mLength = that.mLength;

	// Deep copy.
	T dataToCopy;
	// ���� ����Ʈ�� ���� ��� ����Ʈ�� iterator
	SortedDoublyIterator<T> iterThis(*this), iterThat(that);
	iterThis.Next(); dataToCopy = iterThat.Next();
	while (iterThat.NextNotNull()) {
		// �� ��带 ����� ������ �����ؿ�
		DoublyNodeType<T> *newNode = new DoublyNodeType<T>;
		newNode->data = dataToCopy;
		// �� ��带 ���� ���� ����
		iterThis.mCurPointer->prev->next = newNode;
		newNode->prev = iterThis.mCurPointer->prev;
		// �� ��带 ���� ���� ����
		newNode->next = iterThis.mCurPointer;
		iterThis.mCurPointer->prev = newNode;

		dataToCopy = iterThat.Next();
	}
}

// �Ҹ���.
template <typename T>
SortedDoublyLinkedList<T>::~SortedDoublyLinkedList() {
	delete mFirst;
	delete mLast;
}

// Assignment operator
template<typename T>
SortedDoublyLinkedList<T>
&SortedDoublyLinkedList<T>::operator=(const SortedDoublyLinkedList<T> &that) {
	// self-assignment �˻�
	if (this == &that) {
		return *this;
	}

	MakeEmpty();

	mLength = that.mLength;

	// Deep copy
	T dataToCopy;
	// ���� ����Ʈ�� ���� ��� ����Ʈ�� iterator
	SortedDoublyIterator<T> iterThis(*this), iterThat(that);
	iterThis.Next(); dataToCopy = iterThat.Next();
	while (iterThat.NextNotNull()) {
		// �� ��带 ����� ������ �����ؿ�
		DoublyNodeType<T> *newNode = new DoublyNodeType<T>;
		newNode->data = dataToCopy;
		// �� ��带 ���� ���� ����
		iterThis.mCurPointer->prev->next = newNode;
		newNode->prev = iterThis.mCurPointer->prev;
		// �� ��带 ���� ���� ����
		newNode->next = iterThis.mCurPointer;
		iterThis.mCurPointer->prev = newNode;

		dataToCopy = iterThat.Next();
	}

	return *this;
}

// ����Ʈ�� ������� �˻��Ѵ�.
template <typename T>
bool SortedDoublyLinkedList<T>::IsEmpty() const {
	if (mLength == 0)
		return true;
	else
		return false;
}

// ����Ʈ�� �� ���ִ��� �˻��Ѵ�.
template <typename T>
bool SortedDoublyLinkedList<T>::IsFull() const {
	return false;
}

// ����Ʈ�� ����.
template <typename T>
void SortedDoublyLinkedList<T>::MakeEmpty() {
	DoublyNodeType<T> *pItem;
	SortedDoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.NextNotNull()) {
		pItem = itor.mCurPointer;
		itor.Next(); // ���� �����͸� �������� �̵�.
		delete pItem;
	}

	mFirst->next = mLast;
	mFirst->prev = nullptr;
	mLast->prev = mFirst;
	mLast->next = nullptr;

	mLength = 0;

	return;
}

// ����Ʈ�� ���̸� ��ȯ�Ѵ�.
template <typename T>
int SortedDoublyLinkedList<T>::GetLength() const {
	return mLength;
}

// �������� �Է¹޾� ����Ʈ�� �´� �ڸ��� ã�� �����Ѵ�.
template <typename T>
int SortedDoublyLinkedList<T>::Add(T item) {
	SortedDoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	if (IsEmpty()) // ó�� ������ ��
	{
		DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
		pItem->data = item;
		mFirst->next = pItem;
		pItem->prev = mFirst;
		pItem->next = mLast;
		mLast->prev = pItem; // ó���� �� ���̿� ����.
		mLength++;
		return 1;
	} else // ó���� �ƴ� ��
	{
		while (1) {
			if (item < itor.mCurPointer->data || !itor.NextNotNull()) // �´� �ڸ��� ã�´�.
			{
				DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
				pItem->data = item;
				pItem->prev = itor.mCurPointer->prev;
				pItem->next = itor.mCurPointer;
				itor.mCurPointer->prev->next = pItem;
				itor.mCurPointer->prev = pItem; // �������� ����.
				mLength++;
				return 1;
			} else if (item == itor.mCurPointer->data) // ���� ������ �������� ������
				return 0; // 0�� ��ȯ.
			else
				itor.Next(); // �������� �̵�.
		}
	}
}

// �Է¹��� �������� �����Ϳ��� ã�Ƴ��� �����Ѵ�.
template <typename T>
int SortedDoublyLinkedList<T>::Delete(T item) {
	if (IsEmpty()) {
		return 0;
	}

	SortedDoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	bool found = false;
	while (itor.mCurPointer != mLast) {
		if (itor.mCurPointer->data == item) // ��ġ�ϴ� �����͸� ã�´�.
		{
			found = true;
			DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
			pItem = itor.mCurPointer;
			itor.Next();
			pItem->prev->next = itor.mCurPointer;
			itor.mCurPointer->prev = pItem->prev; // �����ϴ� ����� �հ� �ڸ� ���� �̾��ش�.
			delete pItem; // ����.
			break;
		} else
			itor.Next();
	}
	if (found) {
		mLength--; // ���� ����.
		return 1;
	}
	return 0;
}

// �Է¹��� �������� ������ ��ü�Ѵ�.
template <typename T>
void SortedDoublyLinkedList<T>::Replace(T item) {
	SortedDoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.mCurPointer != mLast) {
		if (itor.mCurPointer->data == item) {
			itor.mCurPointer->data = item; // ������ ��ü.
			return;
		} else
			itor.Next();
	}

	return;
}

// �Է¹��� �����۰� ��ġ�ϴ� �������� ����Ʈ���� ã�� �����´�.
template <typename T>
int SortedDoublyLinkedList<T>::Get(T &item) const {
	SortedDoublyIterator<T> itor(*this);
	itor.Next();

	while (itor.mCurPointer != mLast) {
		if (itor.mCurPointer->data == item) {
			item = itor.mCurPointer->data;
			return 1; // ��ġ�ϸ� 1�� ��ȯ.
		} else
			itor.Next(); // �������� �̵�.
	}

	return 0; // ��ġ���� ������ 0�� ��ȯ.
}
