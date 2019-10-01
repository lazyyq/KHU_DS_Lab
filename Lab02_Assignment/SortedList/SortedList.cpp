#include "SortedList.h"

SortedList::SortedList()
{
	mLength = 0;
	ResetIterator();
}

// Make list empty.
void SortedList::MakeEmpty()
{
	mLength = 0;
}

// Get a number of records in current list.
int SortedList::GetLength()
{
	return mLength;
}

// Check capacity of list is full.
bool SortedList::IsFull()
{
	if (mLength > MAXSIZE - 1)
		return true;
	else
		return false;
}

// Check is list is empty.
bool SortedList::IsEmpty() {
	return mLength == 0;
}

// add a new data into list.
int SortedList::Add(ItemType inData)
{
	if (IsFull()) {
		// List is full
		return 0;
	}
	else if (IsEmpty()) {
		// Array is empty, just add the data at the very front
		mArray[0] = inData;
	}
	else if (inData > mArray[mLength - 1]) {
		// Item is bigger than last item in the list,
		// just add to the very back
		mArray[mLength] = inData;
	}
	else {
		for (int curIndex = 0; curIndex <= mLength - 1; ++curIndex) {
			// Iterate through each item, find a position
			// where our item is bigger than the previous item
			// and smaller than the next item.
			if (inData == mArray[curIndex]) {
				// Same item exists, abort since we do not allow duplicates
				return 0;
			}
			else if (inData < mArray[curIndex]) {
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
int SortedList::Retrieve(ItemType& inData) {
	if (IsEmpty() || mArray[mLength - 1] < inData) {
		// Either list is empty or its last element's primary key is
		// smaller than given data's, so no need to check.
		return -1;
	}

	// Reset iterator
	ResetIterator();

	ItemType data; // Variable to hold info from list
	// Start binary search
	int start = 0, mid, end = mLength - 1;
	while (start <= end) {
		mid = (start + end) / 2;
		data = mArray[mid];

		if (data < inData) {
			start = mid + 1;
		}
		else if (data > inData) {
			end = mid - 1;
		}
		else {
			inData = data;
			return mid;
		}
	}

	return -1;
}

// Delete data from list.
int SortedList::Delete(ItemType& inData) {
	if (IsEmpty()) {
		// List is empty, no need to check
		return 0;
	}

	// Find the position of item that matches inData
	int index = Retrieve(inData);
	if (index != -1) { // Found
		PushForward(index);
		--mLength;
	}
	else { // Not found
		return 0;
	}

	return 1;
}

// Replace data in list.
int SortedList::Replace(ItemType inData) {
	if (IsEmpty()) {
		// List is empty, no need to check
		return 0;
	}

	ItemType data = inData; // Temporary variable to hold info to search
	int index = Retrieve(data);
	if (index != -1) { // Found
		mArray[index] = inData;
	}
	else { // Not found
		return 0;
	}

	return 1;
}

// Initialize list iterator.
void SortedList::ResetIterator()
{
	mCurPointer = -1;
}

// move list iterator to the next item in list and get that item.
int SortedList::GetNextItem(ItemType& inData)
{
	++mCurPointer;	// list pointer 증가
	if (mCurPointer >= MAXSIZE || mCurPointer >= mLength)
		// end of list이거나 list의 마지막 element에 도달하면 -1을 리턴
		return -1;
	inData = mArray[mCurPointer];	// 현재 list pointer의 레코드를 복사

	return mCurPointer;
}

// Move items to the previous index.
void SortedList::PushForward(int startIndex) {
	for (int i = startIndex; i < mLength - 1; ++i) {
		// Copy each item to the next index
		mArray[i] = mArray[i + 1];
	}
}

// Move items to the next index.
void SortedList::PushBackward(int startIndex) {
	for (int i = mLength; i > startIndex; --i) {
		// Copy each item to the previous index
		mArray[i] = mArray[i - 1];
	}
}