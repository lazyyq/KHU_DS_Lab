#ifndef _SORTEDDOUBLYLINKEDLIST_H
#define _SORTEDDOUBLYLINKEDLIST_H

#include "DoublyIterator.h"

template<typename T>
class DoublyIterator;

/**
*	���Ḯ��Ʈ���� ���̴� NodeType�� ����ü
*/
template <typename T>
struct DoublyNodeType {
	T data; ///< �� ����� ������.
	DoublyNodeType *prev = NULL; ///< ����� ���� ����Ű�� ������.
	DoublyNodeType *next = NULL; ///< ����� ������ ����Ű�� ������.
};

/**
*	���ĵ� �������Ḯ��Ʈ Ŭ����
*/
template <typename T>
class SortedDoublyLinkedList {
	friend class DoublyIterator<T>; ///< DoublyIterator�� ģ�� Ŭ����.
public:
	/**
	*	����Ʈ ������.
	*/
	SortedDoublyLinkedList();

	/**
	*	�Ҹ���.
	*/
	~SortedDoublyLinkedList();

	/**
	*	@brief	����Ʈ�� ������� �ƴ��� �˻��Ѵ�.
	*	@pre	m_nLength�� ���� ������ �־�� �Ѵ�.
	*	@post	������� �ƴ����� �˷��ش�.
	*	@return	��������� true, �ƴϸ� false�� ��ȯ.
	*/
	bool IsEmpty();

	/**
	*	@brief	����Ʈ�� ���� á���� �ƴ��� �˻��Ѵ�.
	*	@pre	m_nLength�� ���� ������ �־�� �Ѵ�.
	*	@post	���� á���� �ƴ����� �˷��ش�.
	*	@return	���� �������� true, �ƴϸ� false�� ��ȯ.
	*/
	bool IsFull();

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
	void Delete(T item);

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
	int Get(T &item);

private:
	DoublyNodeType<T> *mFirst; ///< �ּҰ��� ������ ����Ʈ�� �� ó��.
	DoublyNodeType<T> *mLast; ///< �ִ��� ������ ����Ʈ�� �� ��.
	int mLength; ///< ����Ʈ�� ����.
};

// ����Ʈ�� �� ó���� ���� ���θ� ����Ű�� �����ϰ� ����Ʈ�� ���̸� 0���� �ʱ�ȭ���ѳ��´�.
template <typename T>
SortedDoublyLinkedList<T> ::SortedDoublyLinkedList() {
	mFirst = new DoublyNodeType<T>;
	mLast = new DoublyNodeType<T>;

	mFirst->next = mLast; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.
	mFirst->prev = NULL; // ó��.

	mLast->next = NULL; // ��.
	mLast->prev = mFirst; // ���� ó���� ���θ� ����Ű�� �ʱ�ȭ.

	mLength = 0; // ���̴� 0.
}

// �Ҹ���.
template <typename T>
SortedDoublyLinkedList<T>::~SortedDoublyLinkedList() {
	delete mFirst;
	delete mLast;
}

// ����Ʈ�� ������� �˻��Ѵ�.
template <typename T>
bool SortedDoublyLinkedList<T>::IsEmpty() {
	if (mLength == 0)
		return true;
	else
		return false;
}

// ����Ʈ�� �� ���ִ��� �˻��Ѵ�.
template <typename T>
bool SortedDoublyLinkedList<T>::IsFull() {
	if (mLength == 10)
		return true;
	else
		return false;
}

// ����Ʈ�� ����.
template <typename T>
void SortedDoublyLinkedList<T>::MakeEmpty() {
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
int SortedDoublyLinkedList<T>::GetLength() const {
	return mLength;
}

// �������� �Է¹޾� ����Ʈ�� �´� �ڸ��� ã�� �����Ѵ�.
template <typename T>
int SortedDoublyLinkedList<T>::Add(T item) {
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
void SortedDoublyLinkedList<T>::Delete(T item) {
	DoublyIterator<T> itor(*this);
	itor.Next(); // �������� �̵�.

	while (itor.mCurPointer != mLast) {
		if (itor.mCurPointer->data == item) // ��ġ�ϴ� �����͸� ã�´�.
		{
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
	mLength--; // ���� ����.
	return;
}

// �Է¹��� �������� ������ ��ü�Ѵ�.
template <typename T>
void SortedDoublyLinkedList<T>::Replace(T item) {
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
int SortedDoublyLinkedList<T>::Get(T &item) {
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

#endif _SORTEDDOUBLYLINKEDLIST_H