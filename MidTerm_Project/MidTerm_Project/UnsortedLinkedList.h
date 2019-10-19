#ifndef _UNSORTEDLINKEDLIST_H_
#define _UNSORTEDLINKEDLIST_H_

/**
*	Simple unsorted list class for managing items.
*/
template <typename T>
class UnsortedLinkedList {
public:



	UnsortedLinkedList<T>(const UnsortedLinkedList<T> &that) {
		mLength = 0;
		mList = NULL;
		mCurPointer = NULL;

		this->mLength = that.mLength;

		NodeType<T> *thisPtr;
		NodeType<T> *thatPtr = that.mList;
		if (thatPtr == NULL) {
			return;
		}
		NodeType<T> *newNode = new NodeType<T>;
		newNode->data = thatPtr->data;
		this->mList = newNode;
		thisPtr = mList;
		// thisPtr = mList->next = newNode; ?
		while (thatPtr->next != NULL) {
			thatPtr = thatPtr->next;
			newNode = new NodeType<T>;
			newNode->data = thatPtr->data;
			thisPtr->next = newNode;
			thisPtr = thisPtr->next;
		}
	}

	UnsortedLinkedList<T> &operator=(const UnsortedLinkedList<T> &that) {
		if (this == &that) {
			return *this;
		}

		this->mLength = that.mLength;

		NodeType<T> *thisPtr;
		NodeType<T> *thatPtr = that.mList;
		if (thatPtr == NULL) {
			return *this;
		}
		NodeType<T> *newNode = new NodeType<T>;
		newNode->data = thatPtr->data;
		this->mList = newNode;
		thisPtr = mList;
		// thisPtr = mList->next = newNode; ?
		while (thatPtr->next != NULL) {
			thatPtr = thatPtr->next;
			newNode = new NodeType<T>;
			newNode->data = thatPtr->data;
			thisPtr->next = newNode;
			thisPtr = thisPtr->next;
		}

		return *this;
	}






	/**
	*	default constructor.
	*/
	UnsortedLinkedList();

	/**
	*	destructor.
	*/
	~UnsortedLinkedList();

	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;

	/**
	*	@brief	Add item into appropriate spot of this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T item);

	/**
	*	@brief	Delete item from this list.
	*	@pre	List is not empty. the item exists in list.
	*	@post	Item is deleted from this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Delete(T item);

	/**
	*	@brief	Change value of item which is in this list.
	*	@pre	List is not empty. the item exists in list.
	*	@post	Item's value is changed.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Replace(T item);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T &item);

	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetList();

	/**
	*	@brief	Get the next element in list.
	*	@pre	current pointer is defined. Element at current pointer is not last in list.
	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
	*/
	void GetNextItem(T &item);

private:
	/**
	*	Structure for NodeType to use in Linked structure.
	*/
	template <typename T>
	struct NodeType {
		T data;	///< A data for each node.
		NodeType *next = NULL;	///< A node pointer to point succeed node.
	};

	NodeType<T> *mList;	///< Pointer for pointing a first node.
	NodeType<T> *mCurPointer;	///< Node pointer for pointing current node to use iteration.
	int mLength;	///< Number of node in the list.
};


// Class constructor
template <typename T>
UnsortedLinkedList<T>::UnsortedLinkedList() {
	mLength = 0;
	mList = NULL;
	mCurPointer = NULL;
}


// Class destructor
template <typename T>
UnsortedLinkedList<T>::~UnsortedLinkedList() {
	//리스트내의 모든 node 제거
	MakeEmpty();
}


// Initialize list to empty state.
template <typename T>
void UnsortedLinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	// 리스트내의 모든 노드 제거 하고 리스트의 length를 초기화
	NodeType<T> *tempPtr;

	while (mList != NULL) {
		tempPtr = mList;
		mList = mList->next;
		delete tempPtr;
	}

	mLength = 0;
}


// Get number of elements in the list.
template <typename T>
int UnsortedLinkedList<T>::GetLength() const {
	return mLength;
}


// Add item into this list.
template <typename T>
int UnsortedLinkedList<T>::Add(T item) {
	// 리스트 초기화
	ResetList();

	// 리스트에 추가할 새로운 node 객체 선언
	NodeType<T> *node = new NodeType<T>;

	// node 객체에 입력받은 데이터 설정 및 초기화
	node->data = item;
	node->next = NULL;

	// list 에 node 가 존재하지 않는 경우
	if (!mLength) {
		mList = node;
	}
	// list 에 node 가 하나 이상 존재하는 경우
	else {
		// 포인터를 가장 마지막 node 로 이동하면서
		// 중간중간 데이터가 이미 존재하는지 확인
		while (mCurPointer->next != NULL) {
			mCurPointer = mCurPointer->next;
			if (node->data == mCurPointer->data) {
				// 데이터 이미 존재, 함수 종료
				return 0;
			}
		}
		// 새 node 객체의 주소값 삽입
		mCurPointer->next = node;
	}

	mLength++;

	return 1;
}

//Delete item from this list.
template <typename T>
int UnsortedLinkedList<T>::Delete(T item) {
	bool moreToSearch, found;
	NodeType<T> *pre = NULL;	//변수 선언

	mCurPointer = mList;
	found = false;
	moreToSearch = (mCurPointer != NULL);	//변수 초기화

	while (moreToSearch && !found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
	{
		if (item == mCurPointer->data)	//현재 가리키는 원소의 값과 item의 값이 일치할 때
		{
			found = true;	//찾았으므로 found 값 변경
			if (pre == NULL)
				mList = mCurPointer->next;	//항목 이전에 다른 원소가 없을 때 항목의 다음 원소를 첫번째 원소로 한다.
			else {
				pre->next = mCurPointer->next;
				delete mCurPointer;
			}	//이전의 원소의 다음 원소를 '가리키는 항목의 다음 원소'로 바꾼다.
			mLength--;	//리스트의 길이를 1 줄여준다.
		} else {
			pre = mCurPointer;
			mCurPointer = mCurPointer->next;
			moreToSearch = (mCurPointer != NULL);
		}	//일치하지 않을 때 다음 원소를 가리킨다. 단, pre는 지금의 원소를 가리킨다.
	}

	if (found)
		return 1;
	else
		return 0;	//삭제가 성공하면 1, 아니면 0을 리턴한다.
}

//Change value of item which is in this list.
template <typename T>
int UnsortedLinkedList<T>::Replace(T item) {
	bool moreToSearch, found;
	NodeType<T> *location;	//변수 선언

	location = mList;
	found = false;
	moreToSearch = (location != NULL);	//변수 초기화

	while (moreToSearch && !found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
	{
		if (item == location->data) {
			found = true;
			location->data = item;
		}	//일치하는 항목을 찾았을 때 found의 값을 변경해주고 리스트의 항목에 item을 복사해준다.
		else {
			location = location->next;
			moreToSearch = (location != NULL);
		}	//찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 NULL이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
	}

	if (found)
		return 1;
	else
		return 0;	//수정에 성공하면 1, 그렇지 못하면 0을 리턴한다.
}

// Retrieve list element whose key matches item's key (if present).
template <typename T>
int UnsortedLinkedList<T>::Get(T &item) {
	bool moreToSearch, found;
	NodeType<T> *location;	//변수 선언

	location = mList;
	found = false;
	moreToSearch = (location != NULL);	//변수 초기화

	while (moreToSearch && !found)	//리스트의 끝이 아니면서 아직 찾지 않았으면 반복한다.
	{
		if (item == location->data) {
			found = true;
			item = location->data;
		}	//일치하는 항목을 찾았을 때 found의 값을 변경해주고 item에 해당 항목을 복사해준다.
		else {
			location = location->next;
			moreToSearch = (location != NULL);
		}	//찾지 못했을 때 다음 항목으로 location을 옮기고 그 값이 NULL이면 리스트의 끝이므로 moreToSearch의 값을 변경해준다.
	}

	if (found)
		return 1;
	else
		return 0;	//찾으면 1, 그렇지 못하면 0을 리턴한다.
}


// Initializes current pointer for an iteration through the list.
template <typename T>
void UnsortedLinkedList<T>::ResetList() {
	// current pointer 초기화
	mCurPointer = NULL;
}


// Gets the next element in list.
template <typename T>
void UnsortedLinkedList<T>::GetNextItem(T &item) {
	// current pointer 이 NULL이라면 처음 node를 가리킴.
	if (mCurPointer == NULL) {
		mCurPointer = mList;
	} else
		//current position 을 다음 노드로 이동
		mCurPointer = mCurPointer->next;

	//item 에 current position 의 info 를 삽입
	item = mCurPointer->data;
}


#endif	// _UNSORTEDLINKEDLIST_H_
