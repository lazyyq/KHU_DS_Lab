#pragma once

#include "CHeapBase.h"

/**
*	CMaxHeap Ŭ����.
*/
template <typename T>
class CMaxHeap : public CHeapBase<T> {
public:
	/**
	*	������.
	*/
	CMaxHeap();

	/**
	*	������ - �迭�� �ִ� ����.
	*/
	CMaxHeap(int size);

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
CMaxHeap<T>::CMaxHeap() {}


// ������ - �迭�� �ִ� ����.
template <typename T>
CMaxHeap<T>::CMaxHeap(int size) {
	this->mMaxSize = size;
	this->mHeap = new T[this->mMaxSize];
}


// ������ �Ʒ��� �������鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� �����Լ�.
template <typename T>
void CMaxHeap<T>::ReheapDown(int iparent, int ibottom) {
	int maxChild; // �迭�� ���� ��ġ �ε���
	int leftChild; // ���� �ڽĵ����� �ε���
	int rightChild; // ������ �ڽĵ����� �ε���

	leftChild = this->GetLeftChildIndex(iparent);
	rightChild = this->GetRightChildIndex(iparent);

	if (leftChild <= ibottom) {
		if (leftChild == ibottom)
			maxChild = leftChild;
		else {
			if (this->mHeap[leftChild] < this->mHeap[rightChild])
				maxChild = rightChild;
			else
				maxChild = leftChild;
		}
		if (this->mHeap[iparent] < this->mHeap[maxChild]) {
			this->Swap(iparent, maxChild); // �� �������� ��ġ�� �ٲ۴�
			ReheapDown(maxChild, ibottom); // �Ʒ��� ������ �ٽ� ����
		}
	}
}


// �Ʒ����� ���� �ö󰡸鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� �����Լ�.
template <typename T>
void CMaxHeap<T>::ReheapUp(int iroot, int ibottom) {
	int iparent; // �θ�����
	if (ibottom > iroot) {
		iparent = this->GetParentIndex(ibottom);
		if (this->mHeap[iparent] < this->mHeap[ibottom]) {
			this->Swap(iparent, ibottom); // �� �������� ��ġ�� �ٲ۴�
			ReheapUp(iroot, iparent); // ���� �ö� �ٽ� ����
		}
	}
}


// Heap�� �����͸� �����ϴ� �����Լ�.
template <typename T>
void CMaxHeap<T>::Delete(T item, bool &found, int iparent) {
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


// Heap�� �����͸� �˻��ϴ� �����Լ�.
template <typename T>
void CMaxHeap<T>::Retrieve(T &item, bool &found, int iparent) {
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
