#ifndef _CIRCULARQUEUE_H
#define _CIRCULARQUEUE_H

#include <iostream>
using namespace std;

#define QUEUE_MAXSIZE 8

/**
*	@brief	Exception class thrown by Push when queue is full.
*/
class FullQueue {
public:
	/**
	*	@brief	Display a message for full queue on screen.
	*/
	void print() {
		cout << "FullQueue exception thrown." << endl;
	}
};

/**
*	@brief	Exception class thrown by Pop and Top when queue is empty.
*/
class EmptyQueue {
public:
	/**
	*	@brief	Display a message for full queue on screen.
	*/
	void print() {
		cout << "EmtpyQueue exception thrown." << endl;
	}
};

template <typename T>	//generic data�� ���� template ����
class CircularQueue {
public:
	/**
	*	@brief	size�� �ش��ϴ� ũ���� �迭�� �����Ҵ�
	*	@post	size�� ���� �ش�Ǵ� ũ���� �迭�� �������,�� ����������� �ʱ�ȭ��
	*/
	CircularQueue(int size);
	/**
	*	@brief	�ִ�ũ��� ����
	*	@pre	�ִ�ũ�Ⱑ ����������
	*	@post	�ִ�ũ���� �迭�� ���������, �� ����������� �ʱ�ȭ��
	*/
	CircularQueue(void);

	~CircularQueue(void);


	/**
	*	@brief	queue�� �������ִ��� Ȯ��.
	*	@pre	queue�� �ʱ�ȭ �Ǿ����.
	*	@post	�������� ture �ƴϸ� false
	*/
	bool IsFull() const;

	/**
	*	@brief	queue�� ����ִ��� Ȯ��
	*	@pre	queue�� �ʱ�ȭ �Ǿ����.
	*	@post	��������� ture �ƴϸ� false
	*/
	bool IsEmpty() const;

	/**
	*	@brief	queue�� ȸ���ϸ鼭 ���� ä��.
	*	@pre	queue�� �ʱ�ȭ �Ǿ����
	*	@post	������������ FullQueue Exception�� throw��, �ƴϸ� ���ο� ���� �߰���,rear�� ����
	*/
	void EnQueue(T item);

	/**
	*	@brief	queue�� ȸ���ϸ鼭 ���� ����(=front���� �ϳ� ����), �׷��� ���� �������� ����
	*	@pre	Queue has been initialized.
	*	@post	��������� empty Exception�� throw;�ƴϸ� ������ ���� ����
	*/
	void DeQueue();

	/**
	*	@brief	queue�� ȸ���ϸ鼭 ���� ����(=front���� �ϳ� ����)
	*	@pre	Queue has been initialized.
	*	@post	��������� empty Exception�� throw;�ƴϸ� ������ ���� ����
	*/
	void DeQueue(T& item);

	/**
	*	@brief	ť�� �������� �ϳ� ����. �ڿ� �ִ� �����۵��� ���� �ϳ��� ������ �и�.
	*	@pre	Queue has been initialized.
	*	@post	�������� �����ϰ� ���� �����۵��� �ϳ��� ������ �и�.
	*/
	void Delete(T& item);

	/**
	*	@brief	Returns a copy of top item on the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is empty), EmptyQueue exception is thrown; otherwise, top element has been removed from stack.
	*/
	T Top();

	/**
	*	@brief	Print all the items in the queue on screen
	*	@pre	Queue has been initialized.
	*	@post	None.
	*/
	void Print();
	void MakeEmpty();

	void ResetPointer();

	int GetNextItem(T& item);

private:
	int mFront;
	int mRear;
	int mMaxQueueSize;
	int mTop;			// Number of elements.
	T* mQueue;			// Pointer for a queue.
	int mCurPointer;	// Iterator pointer.
};


/* Begin implementation */


template <typename T>
CircularQueue<T>::CircularQueue(int size) {
	mQueue = new T[size];	//T�� �ڷ������� �����Ҵ�
	mFront = size - 1;
	mRear = size - 1;
	mMaxQueueSize = size;
	mTop = -1;
	ResetPointer();
}

template <typename T>
CircularQueue<T>::CircularQueue() {
	mQueue = new T[QUEUE_MAXSIZE];	//T�� �ڷ������� �����Ҵ�
	mFront = QUEUE_MAXSIZE - 1;
	mRear = QUEUE_MAXSIZE - 1;
	mMaxQueueSize = QUEUE_MAXSIZE;
	mTop = -1;
	ResetPointer();
}

// Destruct the object. Free the array dynamically allocated.
template <typename T>
CircularQueue<T>::~CircularQueue() {
	delete[] mQueue;
}

// Determines whether the CircularQueue is full.
template <typename T>
bool CircularQueue<T>::IsEmpty() const {
	return mRear == mFront;
}

// Determines whether the CircularQueue is empty.
template <typename T>
bool CircularQueue<T>::IsFull() const {
	return (mRear + 1) % mMaxQueueSize == mFront;
}

// Adds newItem to the top of the CircularQueue.
template <typename T>
void CircularQueue<T>::EnQueue(T newItem) {
	if (IsFull()) {
		throw FullQueue();
	}
	else {
		mRear = (mRear + 1) % mMaxQueueSize;
		mQueue[mRear % mMaxQueueSize] = newItem;
		mTop++;
	}
}

// Remove top item from the CircularQueue without returning.
template <typename T>
void CircularQueue<T>::DeQueue() {
	// Dummy item to store data from DeQueue(T& item).
	// This won't be used anywhere.
	T dummyItem;
	DeQueue(dummyItem);
}

// Remove and return top item from the CircularQueue.
template <typename T>
void CircularQueue<T>::DeQueue(T& item) {
	if (IsEmpty()) {			//����ִ��� �˻�
		throw EmptyQueue();
	}
	else {
		mFront = (mFront + 1) % mMaxQueueSize; //front�� ������ ��ĭ �̵�
		item = mQueue[mFront];	//��������, ���ٵ��� ���� ���� �˱����ؼ� item�� �ش� ���� ����
		mTop--;
	}
}

// �������� �����ϰ� ���� �����۵��� �ϳ��� ������ �о���.
template<typename T>
void CircularQueue<T>::Delete(T& item) {
	if (IsEmpty()) { // Empty
		cout << "Queue is empty!\n";
		return;
	}

	T itemInQueue; // Temporary variable to hold info from list
	ResetPointer(); // Reset pointer
	int curIndex = GetNextItem(itemInQueue);
	while (curIndex > -1) {
		if (item == itemInQueue) { // Found item to delete
			for (int i = curIndex; i != mRear; i = (i + 1) % mMaxQueueSize) {
				// ���� �ε������� ���������� ù��° �ε����� �����ۿ� ���Ͽ�
				// �������� ���� ��ĭ�� ������ ����
				mQueue[i] = mQueue[(i + 1) % mMaxQueueSize];
			}
			--mRear;
			if (mRear < 0) {
				// mRear�� ������ �Ź����� ��� ����
				mRear = mMaxQueueSize - 1;
			}
			cout << "Successfully deleted from playlist.\n";
			return;
		}
		curIndex = GetNextItem(itemInQueue);
	}
	cout << "Failed to delete from playlist.\n";
}

// Returns top item from the CircularQueue.
template <typename T>
T CircularQueue<T>::Top() {
	if (IsEmpty()) {
		throw EmptyQueue();
	}
	else {
		return mQueue[mTop];
	}
}

// Print all the items in the CircularQueue on screen
template <typename T>
void CircularQueue<T>::Print() {
	if (IsEmpty()) {				//������� it is empty���. Empty Queue�� throw�ϸ� ���α׷��� ����Ǿ �ٽ� Enqueue�Ҽ������Ƿ�
		cout << "It is empty!" << endl;	//�ε����ϰ� ���ο� ����ó��
	}
	else {
		cout << "CircularQueue: ";
		// CircularQueue ���Ǹ��element ���.
		int first = mFront;
		int last = mRear;
		while (first != last) {				//Rear���� front�� ���� �������ȸ�. front�� �����ؼ� ���� �ϳ��� ���.Enqueue�ϸ� rear�� front�� ���� �ռ������Ƿ�
			cout << mQueue[(first + 1) % mMaxQueueSize] << " - ";
			first = (first + 1) % mMaxQueueSize;
		}
		cout << endl;
	}
}

template <typename T>
void CircularQueue<T>::MakeEmpty() {
	mFront = mRear; //Front�� rear�� ���� ������ isEmpty���� �ֺ������ �����
}

template <typename T>
void CircularQueue<T>::ResetPointer() {
	// First item in queue is in index [mFront + 1],
	// so set pointer to mFront.
	mCurPointer = mFront;
}

template <typename T>
int CircularQueue<T>::GetNextItem(T& item) {
	// Check if list is emtpy.
	if (IsEmpty()) {
		cout << "List is empty.\n";
		return -1;
	}

	mCurPointer = (mCurPointer + 1) % mMaxQueueSize;	// list pointer ����
	if (mCurPointer == (mRear + 1) % mMaxQueueSize) {
		// �����Ͱ� rear ���� �ε����� �����ϸ� ť�� ���� ��
		return -1;
	}
	item = mQueue[mCurPointer];	// ���� list pointer�� ���ڵ带 ����

	return mCurPointer;
}

#endif // _CIRCULARQUEUE_H
