#pragma once

#include "DoublyNodeType.h"
#include "DoublyIterator.h"

template<typename T>
class DoublyIterator;

/**
*	���ĵ� �����Ḯ��Ʈ Ŭ����
*/
template <typename T>
class DoublyLinkedList {
	friend class DoublyIterator<T>; // DoublyIterator�� ģ�� Ŭ����.
public:
	/**
	*	����Ʈ ������.
	*/
	DoublyLinkedList();

	/**
	*	Copy constructor.
	*/
	DoublyLinkedList<T>(const DoublyLinkedList<T> &that);

	/**
	*	�Ҹ���.
	*/
	~DoublyLinkedList();

	/**
	*	Assignment operator.
	*/
	DoublyLinkedList<T> &operator=(const DoublyLinkedList<T> &that);

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
DoublyLinkedList<T> ::DoublyLinkedList() {
	mFirst = new DoublyNodeType<T>;
	mLast = new DoublyNodeType<T>;

	mFirst->next = mLast; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.
	mFirst->prev = NULL; // ó��.

	mLast->next = NULL; // ��.
	mLast->prev = mFirst; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.

	mLength = 0; // ���̴� 0.
}

// Copy constructor
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(
	const DoublyLinkedList<T> &that) {
	mFirst = new DoublyNodeType<T>;
	mLast = new DoublyNodeType<T>;

	mFirst->next = mLast; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.
	mFirst->prev = NULL; // ó��.

	mLast->next = NULL; // ��.
	mLast->prev = mFirst; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.

	mLength = that.mLength;

	// Deep copy.
	T dataToCopy;
	// ���� ����Ʈ�� ���� ��� ����Ʈ�� iterator
	DoublyIterator<T> iterThis(*this), iterThat(that);
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
DoublyLinkedList<T>::~DoublyLinkedList() {
	delete mFirst;
	delete mLast;
}

// Assignment operator
template<typename T>
DoublyLinkedList<T>
&DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &that) {
	// self-assignment �˻�
	if (this == &that) {
		return *this;
	}

	MakeEmpty();

	mLength = that.mLength;

	// Deep copy
	T dataToCopy;
	// ���� ����Ʈ�� ���� ��� ����Ʈ�� iterator
	DoublyIterator<T> iterThis(*this), iterThat(that);
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
bool DoublyLinkedList<T>::IsEmpty() const {
	if (mLength == 0)
		return true;
	else
		return false;
}

// ����Ʈ�� �� ���ִ��� �˻��Ѵ�.
template <typename T>
bool DoublyLinkedList<T>::IsFull() const {
	return false;
}

// ����Ʈ�� ����.
template <typename T>
void DoublyLinkedList<T>::MakeEmpty() {
	DoublyNodeType<T> *pItem;
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.NextNotNull()) {
		pItem = itor.mCurPointer;
		itor.Next(); // ���� �����͸� �������� �̵�.
		delete pItem;
	}

	mFirst->next = mLast;
	mFirst->prev = NULL;
	mLast->prev = mFirst;
	mLast->next = NULL;

	mLength = 0;

	return;
}

// ����Ʈ�� ���̸� ��ȯ�Ѵ�.
template <typename T>
int DoublyLinkedList<T>::GetLength() const {
	return mLength;
}

// �������� �Է¹޾� ����Ʈ�� �´� �ڸ��� ã�� �����Ѵ�.
template <typename T>
int DoublyLinkedList<T>::Add(T item) {
	DoublyIterator<T> itor(*this);
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
		while (true) {
			if (!itor.NextNotNull()) // ������ �ڸ��� ã�´�.
			{
				DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
				pItem->data = item;
				pItem->prev = itor.mCurPointer->prev;
				pItem->next = itor.mCurPointer;
				itor.mCurPointer->prev->next = pItem;
				itor.mCurPointer->prev = pItem; // �������� ����.
				mLength++;
				return 1;
			}
			//else if (item == itor.mCurPointer->data) // ���� ������ �������� ������
			//	return 0; // 0�� ��ȯ.
			else
				itor.Next(); // �������� �̵�.
		}
	}
}

// �Է¹��� �������� �����Ϳ��� ã�Ƴ��� �����Ѵ�.
template <typename T>
int DoublyLinkedList<T>::Delete(T item) {
	if (IsEmpty()) {
		return 0;
	}

	DoublyIterator<T> itor(*this);
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
void DoublyLinkedList<T>::Replace(T item) {
	DoublyIterator<T> itor(*this);
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
int DoublyLinkedList<T>::Get(T &item) const {
	DoublyIterator<T> itor(*this);
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
