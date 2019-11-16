#pragma once

#include "SortedDoublyLinkedList.h"

template<typename T>
struct DoublyNodeType;
template<typename T>
class SortedDoublyLinkedList;

/**
*	DoublyLinkedList�� Iterator
*/
template <typename T>
class SortedDoublyIterator {
	friend class SortedDoublyLinkedList<T>;
public:
	/**
	*	����Ʈ ������.
	*/
	SortedDoublyIterator(const SortedDoublyLinkedList<T> &list) :
		mList(list), mCurPointer(list.mFirst) {}; //SortedDoublyLinkedList�� ģ�� Ŭ����.

	/**
	*	@brief	���� �����͸� �� ó�� ���������� ����
	*/
	void ResetPointer();

	/**
	*	@brief	���� �����Ͱ� ������ �ƴ��� Ȯ��
	*	@return	���̸� true �ƴϸ� false
	*/
	bool NotNull();

	/**
	*	@brief	���� �������� ������ �ƴ��� Ȯ��, mLast�� �����ߴ��� Ȯ�ο����� ����
	*	@return	���� �������� ���̸�, �� ���� �����Ͱ� mLast�̸� true, �ƴϸ� false
	*/
	bool NextNotNull();

	/**
	*	@brief	���� �������� ������ �ƴ��� Ȯ��, mFirst���� Ȯ�ο����� ����
	*	@return	���� �������� ���̸�, �� ���� �����Ͱ� mFirst�̸� true, �ƴϸ� false
	*/
	bool PrevNotNull();

	/**
	*	@brief	ó�� �������� ������.
	*	@return	ù ����� ������.
	*/
	T First();

	/**
	*	@brief	�����͸� ���� ���� �̵���Ű�� �������� ������.
	*	@pre	���� ��尡 ������.
	*	@post	�����Ͱ� ���� ���� �̵���.
	*	@return	���� ����� ������.
	*/
	T Next();

	/**
	*	@brief	�����͸� ���� ���� �̵���Ű�� �������� ������.
	*	@pre	���� ��尡 ������.
	*	@post	�����Ͱ� ���� ���� �̵���.
	*	@return	���� ����� ������.
	*/
	T Prev();

	/**
	*	@brief	���� ����� �����Ͱ� ��ȯ��.
	*	@pre	���� ��尡 ������.
	*	@return	���� ���.
	*/
	DoublyNodeType<T> GetCurrentNode();

private:
	const SortedDoublyLinkedList<T> &mList; // Iterate�� ����� �� ����Ʈ
	DoublyNodeType<T> *mCurPointer; // ���� ������
};

template<typename T>
void SortedDoublyIterator<T>::ResetPointer() {
	// �����͸� ù ���������� �̵���Ŵ.
	// �ʱ�ȭ ���Ŀ� ���� ���°� ��.
	mCurPointer = mList.mFirst;
}

template <typename T>
bool SortedDoublyIterator<T> ::NotNull() {
	if (mCurPointer == nullptr)
		return false;
	else
		return true;
}

template <typename T>
bool SortedDoublyIterator<T> ::NextNotNull() {
	if (mCurPointer->next == nullptr)
		return false;
	else
		return true;
}

template <typename T>
bool SortedDoublyIterator<T> ::PrevNotNull() {
	if (mCurPointer->prev == nullptr)
		return false;
	else
		return true;
}

template <typename T>
T SortedDoublyIterator<T> ::First() {
	return mList.mFirst->data;
}

template <typename T>
T SortedDoublyIterator<T> ::Next() {
	mCurPointer = mCurPointer->next; // �����͸� �������� �̵�
	return mCurPointer->data;
}

template <typename T>
T SortedDoublyIterator<T> ::Prev() {
	mCurPointer = mCurPointer->prev; // �����͸� �������� �̵�
	return mCurPointer->data;
}

template <typename T>
DoublyNodeType<T> SortedDoublyIterator<T> ::GetCurrentNode() {
	return *mCurPointer;
}
