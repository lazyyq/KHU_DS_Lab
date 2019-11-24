#pragma once

/**
*	CHeapBase 클래스.
*/
template <typename T>
class CHeapBase {
public:
	/**
	*	생성자.
	*/
	CHeapBase();

	/**
	*	소멸자.
	*/
	virtual ~CHeapBase();

	/**
	*	@brief	Heap가 Empty인지 아닌지 확인하는 함수.
	*	@pre	none.
	*	@post	none.
	*	@return	Heap가 Empty이면 true를 반환, 아니면 false를 반환한다.
	*/
	bool IsEmpty();

	/**
	*	@brief	Heap가 Full인지 아닌지 확인하는 함수.
	*	@pre	none.
	*	@post	none.
	*	@return	Heap가 Full이면 true를 반환, 아니면 false를 반환한다.
	*/
	bool IsFull();

	/**
	*	@brief	Heap의 데이터 수를 반환하는 함수.
	*	@pre	none.
	*	@post	Heap의 데이터 개수를 반환한다.
	*	@return	Heap의 데이터 수
	*/
	int GetLength() const;

	/**
	*	@brief	Heap를 초기화 하는 함수.
	*	@pre	none.
	*	@post	Heap가 초기화된다.
	*/
	void MakeEmpty();

	/**
	*	@brief	Heap에 새로운 데이터를 추가하는 가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap에 새로운 데이터를 추가한다.
	*	@param	item	ItemType형의 새로운 데이터.
	*	@return	잘 작동하면 1을 반환
	*/
	virtual int Add(T item);

	/**
	*	@brief	Heap의 데이터를 삭제하는 가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 삭제한다.
	*	@param	item	ItemType형의 삭제 할 데이터.
	*	@return	잘 작동하면 1을 반환
	*/
	virtual int Delete(T item);

	/**
	*	@brief	Heap의 데이터를 교체하는 가상 함수.
	*	@param	item	교체할 데이터
	*	@return	1 on success, 0 on failure.
	*/
	virtual int ReplaceItem(T item);

	/**
	*	@brief	Heap의 첫번째 데이터를 삭제하는 가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 첫번째 데이터를 삭제한다.
	*	@return	삭제한 데이터 반환
	*/
	virtual T Dequeue();

	/**
	*	@brief	Heap의 데이터를 검색하는 가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 검색한다.
	*	@param	item	ItemType형의 검색 할 데이터.
	*	@param	found	찾았는지 못찾았는지 판단.
	*/
	virtual void RetrieveItem(T &item, bool &found);

	/**
	*	@brief	Heap의 데이터를 출력하는 가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 출력한다.
	*/
	virtual void PrintHeap();

protected:
	/**
	*	@brief	위에서 아래로 내려오면서 Heap 크기를 비교하여 정렬하는 순수가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 비교하여 정렬한다.
	*	@param	iparent	내려가는 데이터.
	*	@param	ibottom	마지막 데이터.
	*/
	virtual void ReheapDown(int iparent, int ibottom) = 0;

	/**
	*	@brief	아래에서 위로 올라가면서 Heap 크기를 비교하여 정렬하는 순수가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 비교하여 정렬한다.
	*	@param	iroot	첫번째 데이터.
	*	@param	ibottom	올라가는 데이터.
	*/
	virtual void ReheapUp(int iroot, int ibottom) = 0;

	/**
	*	@brief	Heap의 데이터를 삭제하는 순수가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 삭제한다.
	*	@param	item	ItemType형의 삭제 할 데이터.
	*	@param	found	삭제할 데이터를 찾았는지 아닌지 확인.
	*	@param	ibottom	검색 중인 배열 위치.
	*/
	virtual void Delete(T item, bool &found, int iparent) = 0;

	/**
	*	@brief	Heap의 데이터를 교체하는 순수가상함수.
	*	@param	item	ItemType형의 검색 할 데이터.
	*	@param	found	검색할 데이터를 찾았는지 아닌지 확인.
	*	@param	ibottom	검색 중인 배열 위치.
	*/
	virtual void Replace(T item, bool &found, int iparent) = 0;

	/**
	*	@brief	Heap의 데이터를 검색하는 순수가상함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap의 데이터를 검색한다.
	*	@param	item	ItemType형의 검색 할 데이터.
	*	@param	found	검색할 데이터를 찾았는지 아닌지 확인.
	*	@param	ibottom	검색 중인 배열 위치.
	*/
	virtual void Retrieve(T &item, bool &found, int iparent) = 0;

	/**
	*	@brief	Heap의 두개의 데이터를 바꾸는 함수.
	*	@pre	두개의 데이터가 존재한다.
	*	@post	두 데이터의 위치가 바뀐다.
	*	@param	iparent	바꿀 위 데이터.
	*	@param	ibottom	바꿀 아래 데이터.
	*/
	virtual void Swap(int iparent, int ibottom);

	T *mHeap;			// 배열
	int mLastNode;	// 배열의 끝
	int mMaxSize;		// 배열의 최대길이

	// Get index of left child
	virtual int GetLeftChildIndex(int parent);

	// Get index of right child
	virtual int GetRightChildIndex(int parent);

	// Get index of parent
	virtual int GetParentIndex(int child);
};


// 생성자
template <typename T>
CHeapBase<T>::CHeapBase() {
	mLastNode = 0;
}


// 소멸자
template <typename T>
CHeapBase<T>::~CHeapBase() {
	MakeEmpty();
}


// Heap가 Empty인지 아닌지 확인하는 함수.
template <typename T>
bool CHeapBase<T>::IsEmpty() {
	if (mLastNode == 0)
		return 1;
	else
		return 0;
}


template <typename T>
bool CHeapBase<T>::IsFull() {
	if (mLastNode == mMaxSize)
		return 1;
	else
		return 0;
}


// Heap가 Full인지 아닌지 확인하는 함수.
template <typename T>
int CHeapBase<T>::GetLength() const {
	return mLastNode;
}


// Heap를 초기화 하는 함수.
template <typename T>
void CHeapBase<T>::MakeEmpty() {
	delete[] mHeap;
	mHeap = new T[mMaxSize];
	mLastNode = 0;
}


// Heap에 새로운 데이터를 추가하는 가상함수
template <typename T>
int CHeapBase<T>::Add(T item) {
	mHeap[mLastNode] = item; // 새 데이터 추가

	ReheapUp(0, mLastNode); // 데이터 정렬

	mLastNode++; // 데이터 수 증가

	return 1;
}


// Heap의 데이터를 삭제하는 가상함수.
template <typename T>
int CHeapBase<T>::Delete(T item) {
	bool found = false;

	Delete(item, found, 0); // 데이터 삭제

	if (found)
		mLastNode--; // 데이터 수 감소
	else
		return 0;

	return 1;
}

// 아이템 교체
template<typename T>
int CHeapBase<T>::ReplaceItem(T item) {
	bool found = false;
	Replace(item, found, 0);
	if (found)
		return 1;
	else
		return 0;
}


// Heap의 첫번째 데이터를 삭제하는 가상함수.
template <typename T>
T CHeapBase<T>::Dequeue() {
	T item = mHeap[0];

	Delete(item); // 첫번째 데이터 삭제

	return item;
}


// Heap의 데이터를 검색하는 가상함수.
template <typename T>
void CHeapBase<T>::RetrieveItem(T &item, bool &found) {
	Retrieve(item, found, 0); // 데이터 검색
}


// Heap의 데이터를 출력하는 가상함수.
template <typename T>
void CHeapBase<T>::PrintHeap() {
	for (int i = 0; i < mLastNode; i++) {
		std::cout << mHeap[i];
	}
}


// Heap의 두개의 데이터를 바꾸는 함수.
template <typename T>
void CHeapBase<T>::Swap(int iparent, int ibottom) {
	T temp = mHeap[iparent];
	mHeap[iparent] = mHeap[ibottom];
	mHeap[ibottom] = temp;
}

// 왼쪽 child의 인덱스 구하기
template<typename T>
int CHeapBase<T>::GetLeftChildIndex(int parent) {
	return parent * 2 + 1;
}

// 오른쪽 child의 인덱스 구하기
template<typename T>
int CHeapBase<T>::GetRightChildIndex(int parent) {
	return parent * 2 + 2;
}

// 부모 노드의 인덱스 구하기
template<typename T>
int CHeapBase<T>::GetParentIndex(int child) {
	return (child - 1) / 2;
}
