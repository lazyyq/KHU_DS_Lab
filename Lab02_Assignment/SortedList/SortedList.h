#ifndef _SORTEDLIST_H
#define _SORTEDLIST_H

#include <iostream>
#include <fstream>	
#include <string>
using namespace std;

#include "ItemType.h"

#define MAXSIZE 10

/**
*	array based simple unsorted list.
*/
class SortedList
{
public:
	/**
	*	default constructor.
	*/
	SortedList();

	/**
	*	destructor.
	*/
	~SortedList() {}

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
	int Add(ItemType inData);

	/**
	*	@brief	Get data from list.
	*	@pre	List should be initialized.
	*	@post	Parameter data contains data retrieved from list.
	*	@param	inData	object to contain data retrieved from list.
	*	@return	Return index of the item on success, -1 on failure.
	*/
	int Retrieve(ItemType& inData);

	/**
	*	@brief	Delete data from list.
	*	@pre	List should be initialized.
	*	@post	Data is deleted from list.
	*	@param	inData	Object containing data to remove.
	*	@return	return 1 on success, 0 on failure.
	*/
	int Delete(ItemType& inData);

	/**
	*	@brief	Replace data in list.
	*	@pre	List should be initialized.
	*	@post	Selected data is replaced with provided one.
	*	@param	inData	Object containing data to replace.
	*	@return	return 1 on success, 0 on failure.
	*/
	int Replace(ItemType inData);

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
	int GetNextItem(ItemType& data);

private:
	ItemType mArray[MAXSIZE];  ///< list array.
	int mLength;				///< number of elements in list.
	int mCurPointer;			///< iterator pointer.
	
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

#endif	// _SORTEDLIST_H