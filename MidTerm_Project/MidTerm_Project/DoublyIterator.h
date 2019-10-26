#ifndef _DOUBLYITERATOR_H
#define _DOUBLYITERATOR_H

#include "SortedDoublyLinkedList.h"

template<typename T>
struct DoublyNodeType;
template<typename T>
class SortedDoublyLinkedList;

/**
*	���Ḯ��Ʈ���� ���̴� Iterator�� Ŭ����.
*/
template <typename T>
class DoublyIterator {
	friend class SortedDoublyLinkedList<T>;
public:
	/**
	*	����Ʈ ������.
	*/
	DoublyIterator(const SortedDoublyLinkedList<T> &list) :
		mList(list), mCurPointer(list.mFirst) {}; ///< SortedDoublyLinkedList�� ģ�� Ŭ����.


	bool NotNull();
	bool NextNotNull();
	T First();
	T Next();
	DoublyNodeType<T> GetCurrentNode();
private:
	const SortedDoublyLinkedList<T> &mList;
	DoublyNodeType<T> *mCurPointer;
};

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
T DoublyIterator<T> ::First() {
	return mList.mFirst->data;
}

template <typename T>
T DoublyIterator<T> ::Next() {
	mCurPointer = mCurPointer->next;
	return mCurPointer->data;
}

template <typename T>
DoublyNodeType<T> DoublyIterator<T> ::GetCurrentNode() {
	return *mCurPointer;
}

#endif _DOUBLYITERATOR_H
