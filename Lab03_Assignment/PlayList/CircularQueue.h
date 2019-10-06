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

template <typename T>	//generic data을 위해 template 선언
class CircularQueue {
public:
	/**
	*	@brief	size에 해당하는 크기의 배열을 동적할당
	*	@post	size의 값에 해당되는 크기의 배열이 만들어짐,각 멤버변수들이 초기화됨
	*/
	CircularQueue(int size);
	/**
	*	@brief	최대크기로 생성
	*	@pre	최대크기가 정해져야함
	*	@post	최대크기의 배열이 만들어지고, 각 멤버변수들이 초기화됨
	*/
	CircularQueue(void);

	~CircularQueue(void);


	/**
	*	@brief	queue가 가득차있는지 확인.
	*	@pre	queue가 초기화 되어야함.
	*	@post	차있으면 ture 아니면 false
	*/
	bool IsFull() const;

	/**
	*	@brief	queue가 비어있는지 확인
	*	@pre	queue가 초기화 되어야함.
	*	@post	비어있으면 ture 아니면 false
	*/
	bool IsEmpty() const;

	/**
	*	@brief	queue에 회전하면서 값을 채움.
	*	@pre	queue가 초기화 되어야함
	*	@post	가득차있으면 FullQueue Exception을 throw함, 아니면 새로운 값을 추가함,rear값 증가
	*/
	void EnQueue(T item);

	/**
	*	@brief	queue에 회전하면서 값을 삭제(=front값이 하나 증가), 그러나 값을 리턴하지 않음
	*	@pre	Queue has been initialized.
	*	@post	비어있으면 empty Exception을 throw;아니면 맨위의 값을 삭제
	*/
	void DeQueue();

	/**
	*	@brief	queue에 회전하면서 값을 삭제(=front값이 하나 증가)
	*	@pre	Queue has been initialized.
	*	@post	비어있으면 empty Exception을 throw;아니면 맨위의 값을 삭제
	*/
	void DeQueue(T& item);

	/**
	*	@brief	큐의 아이템을 하나 삭제. 뒤에 있는 아이템들은 전부 하나씩 앞으로 밀림.
	*	@pre	Queue has been initialized.
	*	@post	아이템을 삭제하고 뒤의 아이템들이 하나씩 앞으로 밀림.
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
	mQueue = new T[size];	//T의 자료형으로 동적할당
	mFront = size - 1;
	mRear = size - 1;
	mMaxQueueSize = size;
	mTop = -1;
	ResetPointer();
}

template <typename T>
CircularQueue<T>::CircularQueue() {
	mQueue = new T[QUEUE_MAXSIZE];	//T의 자료형으로 동적할당
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
	if (IsEmpty()) {			//비어있는지 검사
		throw EmptyQueue();
	}
	else {
		mFront = (mFront + 1) % mMaxQueueSize; //front를 앞으로 한칸 이동
		item = mQueue[mFront];	//지워지는, 접근되지 않을 값을 알기위해서 item에 해당 값을 전달
		mTop--;
	}
}

// 아이템을 삭제하고 뒤의 아이템들을 하나씩 앞으로 밀어줌.
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
				// 현재 인덱스부터 마지막에서 첫번째 인덱스의 아이템에 대하여
				// 아이템을 각각 한칸씩 앞으로 복사
				mQueue[i] = mQueue[(i + 1) % mMaxQueueSize];
			}
			--mRear;
			if (mRear < 0) {
				// mRear가 음수가 돼버렸을 경우 보정
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
	if (IsEmpty()) {				//비었으면 it is empty출력. Empty Queue을 throw하면 프로그램이 종료되어서 다시 Enqueue할수없으므로
		cout << "It is empty!" << endl;	//부득이하게 새로운 예외처리
	}
	else {
		cout << "CircularQueue: ";
		// CircularQueue 내의모든element 출력.
		int first = mFront;
		int last = mRear;
		while (first != last) {				//Rear값과 front가 같지 않을동안만. front로 시작해서 값을 하나씩 출력.Enqueue하면 rear가 front에 비해 앞서있으므로
			cout << mQueue[(first + 1) % mMaxQueueSize] << " - ";
			first = (first + 1) % mMaxQueueSize;
		}
		cout << endl;
	}
}

template <typename T>
void CircularQueue<T>::MakeEmpty() {
	mFront = mRear; //Front랑 rear랑 값이 같으면 isEmpty에서 텅빈것으로 연산됨
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

	mCurPointer = (mCurPointer + 1) % mMaxQueueSize;	// list pointer 증가
	if (mCurPointer == (mRear + 1) % mMaxQueueSize) {
		// 포인터가 rear 다음 인덱스에 도착하면 큐가 끝난 것
		return -1;
	}
	item = mQueue[mCurPointer];	// 현재 list pointer의 레코드를 복사

	return mCurPointer;
}

#endif // _CIRCULARQUEUE_H
