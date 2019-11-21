#ifndef _MINHEAP_H
#define _MINHEAP_H

#include "CHeapBase.h"


/**
*	CMinHeap 클래스.
*/
template <typename T>
class CMinHeap : public CHeapBase<T>
{
public :
	/**
	*	생성자.
	*/
	CMinHeap();

	/**
	*	생성자 - 배열의 최대 길이.
	*/
	CMinHeap(int size);

	/**
	*	@brief	위에서 아래로 내려오면서 Heap 크기를 비교하여 정렬하는 가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 비교하여 정렬한다.
	*	@param	iparent	내려가는 데이터.
	*	@param	ibottom	마지막 데이터.
	*/
	virtual void ReheapDown(int iparent, int ibottom);

	/**
	*	@brief	아래에서 위로 올라가면서 Heap 크기를 비교하여 정렬하는 가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 비교하여 정렬한다.
	*	@param	iroot	첫번째 데이터.
	*	@param	ibottom	올라가는 데이터.
	*/
	virtual void ReheapUp(int iroot, int ibottom);

	/**
	*	@brief	Heap의 데이터를 삭제하는 가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 삭제한다.
	*	@param	item	ItemType형의 삭제 할 데이터.
	*	@param	found	삭제할 데이터를 찾았는지 아닌지 확인.
	*	@param	ibottom	검색 중인 배열 위치.
	*/
	virtual void Delete(T item, bool &found, int iparent);

	/**
	*	@brief	Heap의 데이터를 검색하는 가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 검색한다.
	*	@param	item	ItemType형의 검색 할 데이터.
	*	@param	found	검색할 데이터를 찾았는지 아닌지 확인.
	*	@param	ibottom	검색 중인 배열 위치.
	*/
	virtual void Retrieve(T &item, bool &found, int iparent);
};


// 생성자
template <typename T>
CMinHeap<T>::CMinHeap()
{
}


// 생성자 - 배열의 최대 길이.
template <typename T>
CMinHeap<T>::CMinHeap(int size)
{
}


// 위에서 아래로 내려오면서 Heap 크기를 비교하여 정렬하는 가상함수
template <typename T>
void CMinHeap<T>::ReheapDown(int iparent, int ibottom)
{
}


// 아래에서 위로 올라가면서 Heap 크기를 비교하여 정렬하는 가상함수.
template <typename T>
void CMinHeap<T>::ReheapUp(int iroot, int ibottom)
{
}


// Heap의 데이터를 삭제하는 가상함수.
template <typename T>
void CMinHeap<T>::Delete(T item, bool &found, int iparent)
{
}


// Heap의 데이터를 검색하는 가상함수.
template <typename T>
void CMinHeap<T>::Retrieve(T &item, bool &found, int iparent)
{
}


#endif	// _MINHEAP_H