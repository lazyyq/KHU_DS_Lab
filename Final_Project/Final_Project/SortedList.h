#ifndef _SORTEDLIST_H
#define _SORTEDLIST_H

#include <iostream>
#include <fstream>	
#include <string>
using namespace std;

#define SORTEDLIST_INIT_SIZE	20
#define SORTEDLIST_EXPAND_SIZE	20

/**
*	Array 기반의 SortedList.
*	그러나 리스트가 꽉 차면 자동으로 확장하고
*	공간이 많이 남으면 자동으로 축소함.
*/
template <typename T>
class SortedList {
public:
	/**
	*	default constructor.
	*/
	SortedList();

	/**
	*	destructor.
	*/
	~SortedList();

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull();

	/**
	*	@brief	Check if list is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list size is zero, false otherwise.
	*/
	bool IsEmpty();

	/**
	*	@brief	add a new data into list.
	*	@pre	list should be initialized.
	*	@post	added the new record into the list.
	*	@param	inData	new data.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Add(T inData);

	/**
	*	@brief	Get data from list.
	*	@pre	List should be initialized.
	*	@post	Parameter data contains data retrieved from list.
	*	@param	inData	object to contain data retrieved from list.
	*	@return	Return index of the item on success, -1 on failure.
	*/
	int Retrieve(T &inData);

	/**
	*	@brief	Delete data from list.
	*	@pre	List should be initialized.
	*	@post	Data is deleted from list.
	*	@param	inData	Object containing data to remove.
	*	@return	return 1 on success, 0 on failure.
	*/
	int Delete(T &inData);

	/**
	*	@brief	Replace data in list.
	*	@pre	List should be initialized.
	*	@post	Selected data is replaced with provided one.
	*	@param	inData	Object containing data to replace.
	*	@return	return 1 on success, 0 on failure.
	*/
	int Replace(T inData);

	/**
	*	@brief	Initialize list iterator.
	*	@pre	list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetIterator();

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized.
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	index of current iterator's item if is not end of list, oterwise return -1.
	*/
	int GetNextItem(T &data);

private:
	T *mArray;			///< Pointer for list array.
	int mLength;		///< number of elements in list.
	int mCurPointer;	///< iterator pointer.
	int mCurMaxSize;	///< Current max size

	/**
	*	@brief	리스트의 크기를 늘림. 현재 리스트보다 단위크기만큼 큰 리스트를 새로 만들고
	*			기존 리스트의 아이템을 전부 복사한 뒤 기존 리스트는 파기함.
	*	@post	리스트가 초기화됨. 메모리가 충분함.
	*	@pre	크기가 더 큰 리스트로 대체됨.
	*	@return	성공 시 1, 실패 시 0.
	*/
	bool Expand();

	/**
	*	@brief	리스트의 크기를 줄임. 현재 리스트보다 단위크기만큼 작은 리스트여도
	*			아이템을 전부 담을 수 있다고 판단될 때 크기가 더 작은 리스크를 새로 만들고
	*			기존 리스트의 아이템을 전부 복사한 뒤 기존 리스트는 파기함.
	*			크기는 1 미만으로 줄어들지 않음.
	*	@post	리스트가 초기화됨.
	*	@pre	크기가 더 작은 리스트로 대체됨.
	*	@return	성공 시 1, 실패 시 0.
	*/
	bool Shrink();

	/**
	*	@brief	Starting from startIndex + 1 to the last index of the list,
	*			copy each item to the previous index.
	*	@pre	List should be initialized.
	*	@post	Each data in (`startIndex` + 1) ... (last index of the list) is
	*			moved to the previous index.
	*	@param	startIndex		index to start moving data
	*	@return	None.
	*/
	void PushForward(int startIndex);

	/**
	*	@brief	Starting from startIndex to the last index - 1 of the list,
	*			copy each item to the next index.
	*	@pre	List should be initialized.
	*	@post	Each data in (`startIndex`) ... (last index of the list - 1) is
	*			moved to the next index.
	*	@param	startIndex		index to start moving data
	*	@return	None.
	*/
	void PushBackward(int startIndex);
};


/* Begin implementation */


// Constructor.
template <typename T>
SortedList<T>::SortedList() {
	mArray = new T[SORTEDLIST_INIT_SIZE];
	mCurMaxSize = SORTEDLIST_INIT_SIZE;
	mLength = 0;
	ResetIterator();
}

// Destructor
template <typename T>
SortedList<T>::~SortedList() {
	delete[] mArray;
}

// Make list empty.
template <typename T>
void SortedList<T>::MakeEmpty() {
	mLength = 0;
}

// Get a number of records in current list.
template <typename T>
int SortedList<T>::GetLength() {
	return mLength;
}

// Check capacity of list is full.
template <typename T>
bool SortedList<T>::IsFull() {
	if (mLength > mCurMaxSize - 1)
		return true;
	else
		return false;
}

// Check is list is empty.
template <typename T>
bool SortedList<T>::IsEmpty() {
	return mLength == 0;
}

// add a new data into list.
template <typename T>
int SortedList<T>::Add(T inData) {
	if (IsFull()) {
		// List is full, increase size
		if (!Expand()) {
			// Increase failed
			return 0;
		}
	}
	if (IsEmpty()) {
		// Array is empty, just add the data at the very front
		mArray[0] = inData;
	} else if (inData > mArray[mLength - 1]) {
		// Item is bigger than last item in the list,
		// just add to the very back
		mArray[mLength] = inData;
	} else {
		for (int curIndex = 0; curIndex <= mLength - 1; ++curIndex) {
			// Iterate through each item, find a position
			// where our item is bigger than the previous item
			// and smaller than the next item.
			if (inData == mArray[curIndex]) {
				// Same item exists, abort since we do not allow duplicates
				return 0;
			} else if (inData < mArray[curIndex]) {
				// Found
				// Push data backwards, make space for our item
				PushBackward(curIndex);
				mArray[curIndex] = inData;
				break;
			}
		}
	}

	++mLength;
	return 1;
}

// Get data from list using binary search.
template <typename T>
int SortedList<T>::Retrieve(T &inData) {
	if (IsEmpty() || mArray[mLength - 1] < inData) {
		// Either list is empty or its last element's primary key is
		// smaller than given data's, so no need to check.
		return -1;
	}

	// Reset iterator
	ResetIterator();

	T data; // Variable to hold info from list
	// Start binary search
	int start = 0, mid, end = mLength - 1;
	while (start <= end) {
		mid = (start + end) / 2;
		data = mArray[mid];

		if (data < inData) {
			start = mid + 1;
		} else if (data > inData) {
			end = mid - 1;
		} else {
			inData = data;
			return mid;
		}
	}

	return -1;
}

// Delete data from list.
template <typename T>
int SortedList<T>::Delete(T &inData) {
	if (IsEmpty()) {
		// List is empty, no need to check
		return 0;
	}

	// Find the position of item that matches inData
	int index = Retrieve(inData);
	if (index != -1) { // Found
		PushForward(index);
		--mLength;
	} else { // Not found
		return 0;
	}

	// Decrease array size if possible
	Shrink();

	return 1;
}

// Replace data in list.
template <typename T>
int SortedList<T>::Replace(T inData) {
	if (IsEmpty()) {
		// List is empty, no need to check
		return 0;
	}

	T data = inData; // Temporary variable to hold info to search
	int index = Retrieve(data);
	if (index != -1) { // Found
		mArray[index] = inData;
	} else { // Not found
		return 0;
	}

	return 1;
}

// Initialize list iterator.
template <typename T>
void SortedList<T>::ResetIterator() {
	mCurPointer = -1;
}

// move list iterator to the next item in list and get that item.
template <typename T>
int SortedList<T>::GetNextItem(T &inData) {
	++mCurPointer;	// list pointer 증가
	if (mCurPointer >= mCurMaxSize || mCurPointer >= mLength)
		// end of list이거나 list의 마지막 element에 도달하면 -1을 리턴
		return -1;
	inData = mArray[mCurPointer];	// 현재 list pointer의 레코드를 복사

	return mCurPointer;
}

template<typename T>
bool SortedList<T>::Expand() {
	mCurMaxSize += SORTEDLIST_EXPAND_SIZE; // Increase max size
	// Try to allocate new array
	T *newArray;
	try {
		newArray = new T[mCurMaxSize];
	} catch (bad_alloc &) { // Failed
		return false;
	}
	// Deep copy
	for (int i = 0; i < mLength; ++i) {
		newArray[i] = mArray[i];
	}
	delete[] mArray; // Deallocate old array
	mArray = newArray; // Point array to the new, bigger one

	return true;
}

template<typename T>
bool SortedList<T>::Shrink() {
	if ((mLength > mCurMaxSize - SORTEDLIST_EXPAND_SIZE)
		// Is the new array size too small to afford current items?
		|| (mCurMaxSize - SORTEDLIST_EXPAND_SIZE < 1)) {
		// Or are we shrinking to size below 1?
		return false;
	}

	mCurMaxSize -= SORTEDLIST_EXPAND_SIZE; // Decrease
	// Try to allocate new array
	T *newArray;
	try {
		newArray = new T[mCurMaxSize];
	} catch (bad_alloc &) { // Failed
		return false;
	}
	// Deep copy
	for (int i = 0; i < mLength; ++i) {
		newArray[i] = mArray[i];
	}
	delete[] mArray; // Deallocate old array
	mArray = newArray; // Point array to the new, bigger one

	return true;
}

// Move items to the previous index.
template <typename T>
void SortedList<T>::PushForward(int startIndex) {
	for (int i = startIndex; i < mLength - 1; ++i) {
		// Copy each item to the next index
		mArray[i] = mArray[i + 1];
	}
}

// Move items to the next index.
template <typename T>
void SortedList<T>::PushBackward(int startIndex) {
	for (int i = mLength; i > startIndex; --i) {
		// Copy each item to the previous index
		mArray[i] = mArray[i - 1];
	}
}

#endif // _SORTEDLIST_H
