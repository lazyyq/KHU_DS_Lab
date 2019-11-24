#pragma once

#include "CHeapBase.h"

/**
*	CMinHeap Ŭ����.
*/
template <typename T>
class CMinHeap : public CHeapBase<T> {
public:
	/**
	*	������.
	*/
	CMinHeap();

	/**
	*	������ - �迭�� �ִ� ����.
	*/
	CMinHeap(int size);

	// Destructor
	~CMinHeap();

protected:
	/**
	*	@brief	������ �Ʒ��� �������鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� ���Ͽ� �����Ѵ�.
	*	@param	iparent	�������� ������.
	*	@param	ibottom	������ ������.
	*/
	virtual void ReheapDown(int iparent, int ibottom);

	/**
	*	@brief	�Ʒ����� ���� �ö󰡸鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� ���Ͽ� �����Ѵ�.
	*	@param	iroot	ù��° ������.
	*	@param	ibottom	�ö󰡴� ������.
	*/
	virtual void ReheapUp(int iroot, int ibottom);

	/**
	*	@brief	Heap�� �����͸� �����ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �����Ѵ�.
	*	@param	item	ItemType���� ���� �� ������.
	*	@param	found	������ �����͸� ã�Ҵ��� �ƴ��� Ȯ��.
	*	@param	ibottom	�˻� ���� �迭 ��ġ.
	*/
	virtual void Delete(T item, bool &found, int iparent);

	/**
	*	@brief	Heap�� �����͸� ��ü�ϴ� �����Լ�.
	*	@param	item	ItemType���� ���� �� ������.
	*	@param	found	������ �����͸� ã�Ҵ��� �ƴ��� Ȯ��.
	*	@param	ibottom	�˻� ���� �迭 ��ġ.
	*/
	virtual void Replace(T item, bool &found, int iparent);

	/**
	*	@brief	Heap�� �����͸� �˻��ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �˻��Ѵ�.
	*	@param	item	ItemType���� �˻� �� ������.
	*	@param	found	�˻��� �����͸� ã�Ҵ��� �ƴ��� Ȯ��.
	*	@param	ibottom	�˻� ���� �迭 ��ġ.
	*/
	virtual void Retrieve(T &item, bool &found, int iparent);
};


// ������
template <typename T>
CMinHeap<T>::CMinHeap() {}


// ������ - �迭�� �ִ� ����.
template <typename T>
CMinHeap<T>::CMinHeap(int size) {
	this->mMaxSize = size;
	this->mHeap = new T[this->mMaxSize];
}

template<typename T>
CMinHeap<T>::~CMinHeap() {
	delete[] this->mHeap;
}


// ������ �Ʒ��� �������鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� �����Լ�.
template <typename T>
void CMinHeap<T>::ReheapDown(int iparent, int ibottom) {
	int minChild; // �迭�� ���� ��ġ �ε���
	int leftChild; // ���� �ڽĵ����� �ε���
	int rightChild; // ������ �ڽĵ����� �ε���

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
			this->Swap(iparent, minChild); // �� �������� ��ġ�� �ٲ۴�
			ReheapDown(minChild, ibottom); // �Ʒ��� ������ �ٽ� ����
		}
	}
}


// �Ʒ����� ���� �ö󰡸鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� �����Լ�.
template <typename T>
void CMinHeap<T>::ReheapUp(int iroot, int ibottom) {
	int iparent; // �θ�����
	if (ibottom > iroot) {
		iparent = this->GetParentIndex(ibottom);
		if (this->mHeap[iparent] > this->mHeap[ibottom]) {
			this->Swap(iparent, ibottom); // �� �������� ��ġ�� �ٲ۴�
			ReheapUp(iroot, iparent); // ���� �ö� �ٽ� ����
		}
	}
}


// Heap�� �����͸� �����ϴ� �����Լ�.
template <typename T>
void CMinHeap<T>::Delete(T item, bool &found, int iparent) {
	int leftChild; // ���� �ڽĵ����� �ε���
	int rightChild; // ������ �ڽĵ����� �ε���

	leftChild = this->GetLeftChildIndex(iparent);
	rightChild = this->GetRightChildIndex(iparent);

	if (this->mHeap[iparent] == item) // �����Ϸ��� ������ �߰�
	{
		this->mHeap[iparent] = this->mHeap[this->mLastNode - 1];
		ReheapDown(iparent, this->mLastNode - 2); // ������ ����
		found = true;
	}
	if (leftChild < this->mLastNode && !found)
		Delete(item, found, leftChild); // �������� �˻�
	if (rightChild < this->mLastNode && !found)
		Delete(item, found, rightChild); // ���������� �˻�
}

template<typename T>
void CMinHeap<T>::Replace(T item, bool &found, int iparent) {
	int leftChild; // ���� �ڽĵ����� �ε���
	int rightChild; // ������ �ڽĵ����� �ε���

	leftChild = this->GetLeftChildIndex(iparent);
	rightChild = this->GetRightChildIndex(iparent);

	if (this->mHeap[iparent] == item) // ��ü�Ϸ��� ������ �߰�
	{
		this->mHeap[iparent] = item; // ������ ��ü
		found = true;
	}
	if (leftChild < this->mLastNode && !found)
		Replace(item, found, leftChild); // �������� �˻�
	if (rightChild < this->mLastNode && !found)
		Replace(item, found, rightChild); // ���������� �˻�
}


// Heap�� �����͸� �˻��ϴ� �����Լ�.
template <typename T>
void CMinHeap<T>::Retrieve(T &item, bool &found, int iparent) {
	int leftChild; // ���� �ڽĵ����� �ε���
	int rightChild; // ������ �ڽĵ����� �ε���

	leftChild = this->GetLeftChildIndex(iparent);
	rightChild = this->GetRightChildIndex(iparent);

	if (this->mHeap[iparent] == item) // �˻��Ϸ��� ������ �߰�
	{
		item = this->mHeap[iparent];
		found = true;
	}
	if (leftChild < this->mLastNode && !found)
		Retrieve(item, found, leftChild); // �������� �˻�
	if (rightChild < this->mLastNode && !found)
		Retrieve(item, found, rightChild); // �������� �˻�
}
