#include "SortedList.h"


// Make list empty.
void SortedList::MakeEmpty()
{
	m_Length = 0;
}


// Get a number of records in current list.
int SortedList::GetLength()
{
	return m_Length;
}


// Check capacity of list is full.
bool SortedList::IsFull()
{
	return m_Length >= MAXSIZE;
}


// Check is list is empty.
bool SortedList::IsEmpty() {
	return m_Length <= 0;
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
		m_Array[0] = inData;
	}
	else if (inData.compare(m_Array[m_Length - 1]) == GREATER) {
		m_Array[m_Length] = inData;
	}
	else {
		int curIndex = 0;
		bool done = false;
		while (curIndex <= m_Length - 1 && !done) {
			switch (inData.compare(m_Array[curIndex])) {
			case GREATER:
				break;
			case LESS:
				PushBackward(curIndex);
				m_Array[curIndex] = inData;
				done = true;
				break;
			case EQUAL:
				return 0;
			}

			++curIndex;
		}
	}

	++m_Length;
	return 1;
}


void SortedList::PushBackward(int startIndex) {
	for (int i = m_Length; i > startIndex; --i) {
		m_Array[i] = m_Array[i - 1];
	}
}


// Get data from list.
int SortedList::Retrieve_Seq(ItemType& data) {
	if (IsEmpty() || m_Array[m_Length-1] < data) {
		// Either list is empty or its last element's primary key is
		// smaller than given data's, so no need to check.
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
			data = thisData;
			return 1;
		}
		curIndex = GetNextItem(thisData);
	}

	return 0;
}


// Get data from list using binary search.
int SortedList::Retrieve_BS(ItemType& data) {
	if (IsEmpty() || m_Array[m_Length - 1] < data) {
		// Either list is empty or its last element's primary key is
		// smaller than given data's, so no need to check.
		return 0;
	}

	// Reset iterator
	ResetIterator();

	ItemType item;
	int start = 0, mid, end = m_Length - 1;
	while (start <= end) {
		mid = (start + end) / 2;
		item = m_Array[mid];

		if (item < data) {
			start = mid + 1;
		}
		else if (item > data) {
			end = mid - 1;
		}
		else {
			// item == data
			data = item;
			return 1;
		}
	}

	return 0;
}

// DeleteItem data from list.
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
			while (m_CurPointer < m_Length - 1) {
				// Backward push data
				m_Array[m_CurPointer] = m_Array[m_CurPointer + 1];
				++m_CurPointer;
			}
			// Reduce array size
			--m_Length;

			return 1;
		}
		curIndex = GetNextItem(thisData);
	}

	return 0;
}

// ReplaceItem data in list.
int SortedList::Replace(ItemType data) {
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
			// ReplaceItem the data in list with provided one
			m_Array[m_CurPointer] = data;
			return 1;
		}
		curIndex = GetNextItem(thisData);
	}

	return 0;
}

// Initialize list iterator.
void SortedList::ResetIterator()
{
	m_CurPointer = -1;
}


// move list iterator to the next item in list and get that item.
int SortedList::GetNextItem(ItemType& data)
{
	m_CurPointer++;	// list pointer 증가
	if (m_CurPointer >= MAXSIZE || m_CurPointer >= m_Length)	
		// end of list이거나 list의 마지막 element에 도달하면 -1을 리턴
		return -1;
	data = m_Array[m_CurPointer];	// 현재 list pointer의 레코드를 복사

	return m_CurPointer;
}