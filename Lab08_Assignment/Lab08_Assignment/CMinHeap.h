#pragma once

#include "CHeapBase.h"

/**
*	CMinHeap 클래스.
*/
template <typename T>
class CMinHeap : public CHeapBase<T> {
public:
	/**
	*	생성자.
	*/
	CMinHeap();

	/**
	*	생성자 - 배열의 최대 길이.
	*/
	CMinHeap(int size);

	// Destructor
	~CMinHeap();

protected:
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
	*	@brief	Heap의 데이터를 교체하는 가상함수.
	*	@param	item	ItemType형의 삭제 할 데이터.
	*	@param	found	삭제할 데이터를 찾았는지 아닌지 확인.
	*	@param	ibottom	검색 중인 배열 위치.
	*/
	virtual void Replace(T item, bool &found, int iparent);

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
CMinHeap<T>::CMinHeap() {}


// 생성자 - 배열의 최대 길이.
template <typename T>
CMinHeap<T>::CMinHeap(int size) {
	this->mMaxSize = size;
	this->mHeap = new T[this->mMaxSize];
}

template<typename T>
CMinHeap<T>::~CMinHeap() {
	delete[] this->mHeap;
}


// 위에서 아래로 내려오면서 Heap 크기를 비교하여 정렬하는 가상함수.
template <typename T>
void CMinHeap<T>::ReheapDown(int iparent, int ibottom) {
	int minChild; // 배열의 현재 위치 인덱스
	int leftChild; // 왼쪽 자식데이터 인덱스
	int rightChild; // 오른족 자식데이터 인덱스

	leftChild = this->GetLeftChildIndex(iparent);
	rightChild = this->GetRightChildIndex(iparent);

	if (leftChild <= ibottom) {
		if (leftChild == ibottom)
			minChild = leftChild;
		else {
			if (this->mHeap[leftChild] < this->mHeap[rightChild])
				minChild = leftChild;
			else
				minChild = rightChild;
		}
		if (this->mHeap[iparent] > this->mHeap[minChild]) {
			this->Swap(iparent, minChild); // 두 데이터의 위치를 바꾼다
			ReheapDown(minChild, ibottom); // 아래로 내려가 다시 정렬
		}
	}
}


// 아래에서 위로 올라가면서 Heap 크기를 비교하여 정렬하는 가상함수.
template <typename T>
void CMinHeap<T>::ReheapUp(int iroot, int ibottom) {
	int iparent; // 부모데이터
	if (ibottom > iroot) {
		iparent = this->GetParentIndex(ibottom);
		if (this->mHeap[iparent] > this->mHeap[ibottom]) {
			this->Swap(iparent, ibottom); // 두 데이터의 위치를 바꾼다
			ReheapUp(iroot, iparent); // 위로 올라가 다시 정렬
		}
	}
}


// Heap의 데이터를 삭제하는 가상함수.
template <typename T>
void CMinHeap<T>::Delete(T item, bool &found, int iparent) {
	int leftChild; // 왼쪽 자식데이터 인덱스
	int rightChild; // 오른쪽 자식데이터 인덱스

	leftChild = this->GetLeftChildIndex(iparent);
	rightChild = this->GetRightChildIndex(iparent);

	if (this->mHeap[iparent] == item) // 삭제하려는 데이터 발견
	{
		this->mHeap[iparent] = this->mHeap[this->mLastNode - 1];
		ReheapDown(iparent, this->mLastNode - 2); // 데이터 정렬
		found = true;
	}
	if (leftChild < this->mLastNode && !found)
		Delete(item, found, leftChild); // 왼쪽으로 검색
	if (rightChild < this->mLastNode && !found)
		Delete(item, found, rightChild); // 오른쪽으로 검색
}

template<typename T>
void CMinHeap<T>::Replace(T item, bool &found, int iparent) {
	int leftChild; // 왼쪽 자식데이터 인덱스
	int rightChild; // 오른쪽 자식데이터 인덱스

	leftChild = this->GetLeftChildIndex(iparent);
	rightChild = this->GetRightChildIndex(iparent);

	if (this->mHeap[iparent] == item) // 교체하려는 데이터 발견
	{
		this->mHeap[iparent] = item; // 데이터 교체
		found = true;
	}
	if (leftChild < this->mLastNode && !found)
		Replace(item, found, leftChild); // 왼쪽으로 검색
	if (rightChild < this->mLastNode && !found)
		Replace(item, found, rightChild); // 오른쪽으로 검색
}


// Heap의 데이터를 검색하는 가상함수.
template <typename T>
void CMinHeap<T>::Retrieve(T &item, bool &found, int iparent) {
	int leftChild; // 왼쪽 자식데이터 인덱스
	int rightChild; // 오른쪽 자식데이터 인덱스

	leftChild = this->GetLeftChildIndex(iparent);
	rightChild = this->GetRightChildIndex(iparent);

	if (this->mHeap[iparent] == item) // 검색하려는 데이터 발견
	{
		item = this->mHeap[iparent];
		found = true;
	}
	if (leftChild < this->mLastNode && !found)
		Retrieve(item, found, leftChild); // 왼쪽으로 검색
	if (rightChild < this->mLastNode && !found)
		Retrieve(item, found, rightChild); // 왼쪽으로 검색
}
