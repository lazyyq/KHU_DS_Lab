#ifndef _DOUBLYITERATOR_H
#define _DOUBLYITERATOR_H

#include "SortedDoublyLinkedList.h"

template<typename T>
struct DoublyNodeType;
template<typename T>
class SortedDoublyLinkedList;

/**
*	연결리스트에서 쓰이는 Iterator의 클래스.
*/
template <typename T>
class DoublyIterator {
	friend class SortedDoublyLinkedList<T>;
public:
	/**
	*	디폴트 생성자.
	*/
	DoublyIterator(const SortedDoublyLinkedList<T> &list) :
		mList(list), mCurPointer(list.mFirst) {}; ///< SortedDoublyLinkedList와 친구 클래스.


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
