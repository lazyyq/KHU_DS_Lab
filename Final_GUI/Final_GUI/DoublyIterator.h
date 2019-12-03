#pragma once

#include "DoublyLinkedList.h"

template<typename T>
struct DoublyNodeType;
template<typename T>
class DoublyLinkedList;

/**
*	DoublyLinkedList�� Iterator
*/
template <typename T>
class DoublyIterator {
	friend class DoublyLinkedList<T>;
public:
	/**
	*	����Ʈ ������.
	*/
	DoublyIterator(const DoublyLinkedList<T> &list) :
		mList(list), mCurPointer(list.mFirst) {}; //DoublyLinkedList�� ģ�� Ŭ����.

	/**
	*	@brief	���� �����͸� �� ó�� ���������� ����
	*/
	void ResetPointer();

	/**
	*	@brief	���� �����͸� �� ������ ���������� ����
	*/
	void PointerToLast();

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
	const DoublyLinkedList<T> &mList; // Iterate�� ����� �� ����Ʈ
	DoublyNodeType<T> *mCurPointer; // ���� ������
};

template<typename T>
void DoublyIterator<T>::ResetPointer() {
	// �����͸� ù ���������� �̵���Ŵ.
	// �ʱ�ȭ ���Ŀ� ���� ���°� ��.
	mCurPointer = mList.mFirst;
}

template<typename T>
void DoublyIterator<T>::PointerToLast() {
	mCurPointer = mList.mLast;
}

template <typename T>
bool DoublyIterator<T> ::NotNull() {
	if (mCurPointer == NULL)
		return false;
	else
		return true;
}

template <typename T>
bool DoublyIterator<T> ::NextNotNull() {
	if (mCurPointer->next == NULL)
		return false;
	else
		return true;
}

template <typename T>
bool DoublyIterator<T> ::PrevNotNull() {
	if (mCurPointer->prev == NULL)
		return false;
	else
		return true;
}

template <typename T>
T DoublyIterator<T> ::First() {
	return mList.mFirst->data;
}

template <typename T>
T DoublyIterator<T> ::Next() {
	mCurPointer = mCurPointer->next; // �����͸� �������� �̵�
	return mCurPointer->data;
}

template <typename T>
T DoublyIterator<T> ::Prev() {
	mCurPointer = mCurPointer->prev; // �����͸� �������� �̵�
	return mCurPointer->data;
}

template <typename T>
DoublyNodeType<T> DoublyIterator<T> ::GetCurrentNode() {
	return *mCurPointer;
}
