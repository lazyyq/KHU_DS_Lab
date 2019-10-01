#include "ArrayList.h"


// Make list empty.
void ArrayList::MakeEmpty()
{
	m_Length = 0;
}


// Get a number of records in current list.
int ArrayList::GetLength()
{
	return m_Length;
}


// Check capacity of list is full.
bool ArrayList::IsFull()
{
	if (m_Length > MAXSIZE - 1)
		return true;
	else
		return false;
}

// Check is list is empty.
bool ArrayList::IsEmpty() {
	return m_Length == 0;
}


// add a new data into list.
int ArrayList::Add(ItemType inData)
{
	if (!IsFull())
	{
		m_Array[m_Length] = inData;
		m_Length++;
	}
	else
		return 0;

	return 1;
}

// Get data from list.
int ArrayList::Get(ItemType& data) {
	ItemType thisData;
	// Reset iterator
	ResetList();
	do {
		GetNextItem(thisData);
		if (thisData == data) {
			// Id matched
			data = thisData;
			return 1;
		}
	} while (m_CurPointer > -1 && m_CurPointer < m_Length - 1);

	return 0;
}

// Delete data from list.
int ArrayList::Delete(ItemType data) {
	ItemType thisData;
	// Reset iterator
	ResetList();
	do {
		GetNextItem(thisData);
		if (thisData == data) {
			// Id matched
			while (m_CurPointer < m_Length - 1) {
				// Backward push data
				m_Array[m_CurPointer] = m_Array[m_CurPointer + 1];
				++m_CurPointer;
			}
			// Reduce max length
			--m_Length;

			return 1;
		}
	} while (m_CurPointer > -1 && m_CurPointer < m_Length - 1);

	return 0;
}

// Replace data in list.
int ArrayList::Replace(ItemType data) {
	ItemType thisData;
	// Reset iterator
	ResetList();
	do {
		GetNextItem(thisData);
		if (thisData == data) {
			// Id matched
			// Put found data in parameter data
			m_Array[m_CurPointer] = data;
			return 1;
		}
	} while (m_CurPointer > -1 && m_CurPointer < m_Length - 1);

	return 0;
}

// Initialize list iterator.
void ArrayList::ResetList()
{
	m_CurPointer = -1;
}


// move list iterator to the next item in list and get that item.
int ArrayList::GetNextItem(ItemType& data)
{
	m_CurPointer++;	// list pointer 증가	
	if (m_CurPointer == MAXSIZE)	// end of list이면 -1을 리턴
		return -1;
	data = m_Array[m_CurPointer];	// 현재 list pointer의 레코드를 복사

	return m_CurPointer;
}