#include "SortedList.h"

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
	else if (inData > mArray[mLength-1]) {
		mArray[mLength] = inData;
	}
	else {
		for (int curIndex = 0; curIndex <= mLength - 1; ++curIndex) {
			if (inData == mArray[curIndex]) {
				return 0;
			}
			else if (inData < mArray[curIndex]) {
				PushBackward(curIndex);
				mArray[curIndex] = inData;
				break;
			}
		}
	}

	++mLength;
	return 1;
}

// 포지션을 리턴한다고 코멘트에 추가
// Get data from list using binary search.
int SortedList::Retrieve(ItemType& data) {
	if (IsEmpty() || mArray[mLength - 1] < data) {
		// Either list is empty or its last element's primary key is
		// smaller than given data's, so no need to check.
		return -1;
	}

	// Reset iterator
	ResetIterator();

	ItemType item;
	int start = 0, mid, end = mLength - 1;
	while (start <= end) {
		mid = (start + end) / 2;
		item = mArray[mid];

		if (item < data) {
			start = mid + 1;
		}
		else if (item > data) {
			end = mid - 1;
		}
		else {
			// item == data
			data = item;
			return mid;
		}
	}

	return -1;
}

// Delete data from list.
int SortedList::Delete(ItemType data) {
	if (IsEmpty()) {
		// List is empty, no need to check
		return 0;
	}

	// Reset iterator
	ResetIterator();

	ItemType thisData;
	int curIndex = GetNextItem(thisData);
	while (curIndex > -1)
	{
		if (thisData == data) {
			// Id matched
			while (mCurPointer < mLength- 1) {
				// Backward push data
				mArray[mCurPointer] = mArray[mCurPointer + 1];
				++mCurPointer;
			}
			// Reduce array size
			--mLength;

			return 1;
		}
		curIndex = GetNextItem(thisData);
	}

	return 0;
}

// Replace data in list.
int SortedList::Replace(ItemType data) {
	if (IsEmpty()) {
		// List is empty, no need to check
		return 0;
	}

	ItemType item = data;
	int index = Retrieve(item);
	if (index != -1) {
		mArray[index] = data;
	}
	else {
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
int SortedList::GetNextItem(ItemType& data)
{
	++mCurPointer;	// list pointer 증가
	if (mCurPointer>= MAXSIZE || mCurPointer>= mLength)
		// end of list이거나 list의 마지막 element에 도달하면 -1을 리턴
		return -1;
	data = mArray[mCurPointer];	// 현재 list pointer의 레코드를 복사

	return mCurPointer;
}

void SortedList::PushBackward(int startIndex) {
	for (int i = mLength; i > startIndex; --i) {
		mArray[i] = mArray[i - 1];
	}
}