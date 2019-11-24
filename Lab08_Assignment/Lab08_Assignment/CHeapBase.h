#pragma once

/**
*	CHeapBase Ŭ����.
*/
template <typename T>
class CHeapBase {
public:
	/**
	*	������.
	*/
	CHeapBase();

	/**
	*	�Ҹ���.
	*/
	virtual ~CHeapBase();

	/**
	*	@brief	Heap�� Empty���� �ƴ��� Ȯ���ϴ� �Լ�.
	*	@pre	none.
	*	@post	none.
	*	@return	Heap�� Empty�̸� true�� ��ȯ, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsEmpty();

	/**
	*	@brief	Heap�� Full���� �ƴ��� Ȯ���ϴ� �Լ�.
	*	@pre	none.
	*	@post	none.
	*	@return	Heap�� Full�̸� true�� ��ȯ, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsFull();

	/**
	*	@brief	Heap�� ������ ���� ��ȯ�ϴ� �Լ�.
	*	@pre	none.
	*	@post	Heap�� ������ ������ ��ȯ�Ѵ�.
	*	@return	Heap�� ������ ��
	*/
	int GetLength() const;

	/**
	*	@brief	Heap�� �ʱ�ȭ �ϴ� �Լ�.
	*	@pre	none.
	*	@post	Heap�� �ʱ�ȭ�ȴ�.
	*/
	void MakeEmpty();

	/**
	*	@brief	Heap�� ���ο� �����͸� �߰��ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� ���ο� �����͸� �߰��Ѵ�.
	*	@param	item	ItemType���� ���ο� ������.
	*	@return	�� �۵��ϸ� 1�� ��ȯ
	*/
	virtual int Add(T item);

	/**
	*	@brief	Heap�� �����͸� �����ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �����Ѵ�.
	*	@param	item	ItemType���� ���� �� ������.
	*	@return	�� �۵��ϸ� 1�� ��ȯ
	*/
	virtual int Delete(T item);

	/**
	*	@brief	Heap�� �����͸� ��ü�ϴ� ���� �Լ�.
	*	@param	item	��ü�� ������
	*	@return	1 on success, 0 on failure.
	*/
	virtual int ReplaceItem(T item);

	/**
	*	@brief	Heap�� ù��° �����͸� �����ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� ù��° �����͸� �����Ѵ�.
	*	@return	������ ������ ��ȯ
	*/
	virtual T Dequeue();

	/**
	*	@brief	Heap�� �����͸� �˻��ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �˻��Ѵ�.
	*	@param	item	ItemType���� �˻� �� ������.
	*	@param	found	ã�Ҵ��� ��ã�Ҵ��� �Ǵ�.
	*/
	virtual void RetrieveItem(T &item, bool &found);

	/**
	*	@brief	Heap�� �����͸� ����ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� ����Ѵ�.
	*/
	virtual void PrintHeap();

protected:
	/**
	*	@brief	������ �Ʒ��� �������鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� ���������Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� ���Ͽ� �����Ѵ�.
	*	@param	iparent	�������� ������.
	*	@param	ibottom	������ ������.
	*/
	virtual void ReheapDown(int iparent, int ibottom) = 0;

	/**
	*	@brief	�Ʒ����� ���� �ö󰡸鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� ���������Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� ���Ͽ� �����Ѵ�.
	*	@param	iroot	ù��° ������.
	*	@param	ibottom	�ö󰡴� ������.
	*/
	virtual void ReheapUp(int iroot, int ibottom) = 0;

	/**
	*	@brief	Heap�� �����͸� �����ϴ� ���������Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �����Ѵ�.
	*	@param	item	ItemType���� ���� �� ������.
	*	@param	found	������ �����͸� ã�Ҵ��� �ƴ��� Ȯ��.
	*	@param	ibottom	�˻� ���� �迭 ��ġ.
	*/
	virtual void Delete(T item, bool &found, int iparent) = 0;

	/**
	*	@brief	Heap�� �����͸� ��ü�ϴ� ���������Լ�.
	*	@param	item	ItemType���� �˻� �� ������.
	*	@param	found	�˻��� �����͸� ã�Ҵ��� �ƴ��� Ȯ��.
	*	@param	ibottom	�˻� ���� �迭 ��ġ.
	*/
	virtual void Replace(T item, bool &found, int iparent) = 0;

	/**
	*	@brief	Heap�� �����͸� �˻��ϴ� ���������Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �˻��Ѵ�.
	*	@param	item	ItemType���� �˻� �� ������.
	*	@param	found	�˻��� �����͸� ã�Ҵ��� �ƴ��� Ȯ��.
	*	@param	ibottom	�˻� ���� �迭 ��ġ.
	*/
	virtual void Retrieve(T &item, bool &found, int iparent) = 0;

	/**
	*	@brief	Heap�� �ΰ��� �����͸� �ٲٴ� �Լ�.
	*	@pre	�ΰ��� �����Ͱ� �����Ѵ�.
	*	@post	�� �������� ��ġ�� �ٲ��.
	*	@param	iparent	�ٲ� �� ������.
	*	@param	ibottom	�ٲ� �Ʒ� ������.
	*/
	virtual void Swap(int iparent, int ibottom);

	T *mHeap;			// �迭
	int mLastNode;	// �迭�� ��
	int mMaxSize;		// �迭�� �ִ����

	// Get index of left child
	virtual int GetLeftChildIndex(int parent);

	// Get index of right child
	virtual int GetRightChildIndex(int parent);

	// Get index of parent
	virtual int GetParentIndex(int child);
};


// ������
template <typename T>
CHeapBase<T>::CHeapBase() {
	mLastNode = 0;
}


// �Ҹ���
template <typename T>
CHeapBase<T>::~CHeapBase() {
	MakeEmpty();
}


// Heap�� Empty���� �ƴ��� Ȯ���ϴ� �Լ�.
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


// Heap�� Full���� �ƴ��� Ȯ���ϴ� �Լ�.
template <typename T>
int CHeapBase<T>::GetLength() const {
	return mLastNode;
}


// Heap�� �ʱ�ȭ �ϴ� �Լ�.
template <typename T>
void CHeapBase<T>::MakeEmpty() {
	delete[] mHeap;
	mHeap = new T[mMaxSize];
	mLastNode = 0;
}


// Heap�� ���ο� �����͸� �߰��ϴ� �����Լ�
template <typename T>
int CHeapBase<T>::Add(T item) {
	mHeap[mLastNode] = item; // �� ������ �߰�

	ReheapUp(0, mLastNode); // ������ ����

	mLastNode++; // ������ �� ����

	return 1;
}


// Heap�� �����͸� �����ϴ� �����Լ�.
template <typename T>
int CHeapBase<T>::Delete(T item) {
	bool found = false;

	Delete(item, found, 0); // ������ ����

	if (found)
		mLastNode--; // ������ �� ����
	else
		return 0;

	return 1;
}

// ������ ��ü
template<typename T>
int CHeapBase<T>::ReplaceItem(T item) {
	bool found = false;
	Replace(item, found, 0);
	if (found)
		return 1;
	else
		return 0;
}


// Heap�� ù��° �����͸� �����ϴ� �����Լ�.
template <typename T>
T CHeapBase<T>::Dequeue() {
	T item = mHeap[0];

	Delete(item); // ù��° ������ ����

	return item;
}


// Heap�� �����͸� �˻��ϴ� �����Լ�.
template <typename T>
void CHeapBase<T>::RetrieveItem(T &item, bool &found) {
	Retrieve(item, found, 0); // ������ �˻�
}


// Heap�� �����͸� ����ϴ� �����Լ�.
template <typename T>
void CHeapBase<T>::PrintHeap() {
	for (int i = 0; i < mLastNode; i++) {
		std::cout << mHeap[i];
	}
}


// Heap�� �ΰ��� �����͸� �ٲٴ� �Լ�.
template <typename T>
void CHeapBase<T>::Swap(int iparent, int ibottom) {
	T temp = mHeap[iparent];
	mHeap[iparent] = mHeap[ibottom];
	mHeap[ibottom] = temp;
}

// ���� child�� �ε��� ���ϱ�
template<typename T>
int CHeapBase<T>::GetLeftChildIndex(int parent) {
	return parent * 2 + 1;
}

// ������ child�� �ε��� ���ϱ�
template<typename T>
int CHeapBase<T>::GetRightChildIndex(int parent) {
	return parent * 2 + 2;
}

// �θ� ����� �ε��� ���ϱ�
template<typename T>
int CHeapBase<T>::GetParentIndex(int child) {
	return (child - 1) / 2;
}
