#pragma once

#include "DoublyLinkedList.h"

template<typename T>
struct DoublyNodeType;
template<typename T>
class DoublyLinkedList;

/**
*	DoublyLinkedList의 Iterator
*/
template <typename T>
class DoublyIterator {
	friend class DoublyLinkedList<T>;
public:
	/**
	*	디폴트 생성자.
	*/
	DoublyIterator(const DoublyLinkedList<T> &list) :
		mList(list), mCurPointer(list.mFirst) {}; //DoublyLinkedList와 친구 클래스.

	/**
	*	@brief	현재 포인터를 맨 처음 아이템으로 리셋
	*/
	void ResetPointer();

	/**
	*	@brief	현재 포인터를 맨 마지막 아이템으로 리셋
	*/
	void PointerToLast();

	/**
	*	@brief	현재 포인터가 널인지 아닌지 확인
	*	@return	널이면 true 아니면 false
	*/
	bool NotNull();

	/**
	*	@brief	다음 아이템이 널인지 아닌지 확인, mLast에 도달했는지 확인용으로 쓰임
	*	@return	다음 아이템이 널이면, 즉 현재 포인터가 mLast이면 true, 아니면 false
	*/
	bool NextNotNull();

	/**
	*	@brief	이전 아이템이 널인지 아닌지 확인, mFirst인지 확인용으로 쓰임
	*	@return	이전 아이템이 널이면, 즉 현재 포인터가 mFirst이면 true, 아니면 false
	*/
	bool PrevNotNull();

	/**
	*	@brief	처음 아이템을 가져옴.
	*	@return	첫 노드의 아이템.
	*/
	T First();

	/**
	*	@brief	포인터를 다음 노드로 이동시키고 아이템을 가져옴.
	*	@pre	다음 노드가 존재함.
	*	@post	포인터가 다음 노드로 이동됨.
	*	@return	다음 노드의 아이템.
	*/
	T Next();

	/**
	*	@brief	포인터를 이전 노드로 이동시키고 아이템을 가져옴.
	*	@pre	이전 노드가 존재함.
	*	@post	포인터가 이전 노드로 이동됨.
	*	@return	이전 노드의 아이템.
	*/
	T Prev();

	/**
	*	@brief	현재 노드의 데이터가 반환됨.
	*	@pre	현재 노드가 존재함.
	*	@return	현재 노드.
	*/
	DoublyNodeType<T> GetCurrentNode();

private:
	const DoublyLinkedList<T> &mList; // Iterate의 대상이 될 리스트
	DoublyNodeType<T> *mCurPointer; // 현재 포인터
};

template<typename T>
void DoublyIterator<T>::ResetPointer() {
	// 포인터를 첫 아이템으로 이동시킴.
	// 초기화 직후와 같은 상태가 됨.
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
	mCurPointer = mCurPointer->next; // 포인터를 다음으로 이동
	return mCurPointer->data;
}

template <typename T>
T DoublyIterator<T> ::Prev() {
	mCurPointer = mCurPointer->prev; // 포인터를 이전으로 이동
	return mCurPointer->data;
}

template <typename T>
DoublyNodeType<T> DoublyIterator<T> ::GetCurrentNode() {
	return *mCurPointer;
}
