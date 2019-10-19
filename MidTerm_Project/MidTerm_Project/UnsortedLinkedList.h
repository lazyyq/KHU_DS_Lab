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
	//����Ʈ���� ��� node ����
	MakeEmpty();
}


// Initialize list to empty state.
template <typename T>
void UnsortedLinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	// ����Ʈ���� ��� ��� ���� �ϰ� ����Ʈ�� length�� �ʱ�ȭ
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
	// ����Ʈ �ʱ�ȭ
	ResetList();

	// ����Ʈ�� �߰��� ���ο� node ��ü ����
	NodeType<T> *node = new NodeType<T>;

	// node ��ü�� �Է¹��� ������ ���� �� �ʱ�ȭ
	node->data = item;
	node->next = NULL;

	// list �� node �� �������� �ʴ� ���
	if (!mLength) {
		mList = node;
	}
	// list �� node �� �ϳ� �̻� �����ϴ� ���
	else {
		// �����͸� ���� ������ node �� �̵��ϸ鼭
		// �߰��߰� �����Ͱ� �̹� �����ϴ��� Ȯ��
		while (mCurPointer->next != NULL) {
			mCurPointer = mCurPointer->next;
			if (node->data == mCurPointer->data) {
				// ������ �̹� ����, �Լ� ����
				return 0;
			}
		}
		// �� node ��ü�� �ּҰ� ����
		mCurPointer->next = node;
	}

	mLength++;

	return 1;
}

//Delete item from this list.
template <typename T>
int UnsortedLinkedList<T>::Delete(T item) {
	bool moreToSearch, found;
	NodeType<T> *pre = NULL;	//���� ����

	mCurPointer = mList;
	found = false;
	moreToSearch = (mCurPointer != NULL);	//���� �ʱ�ȭ

	while (moreToSearch && !found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
	{
		if (item == mCurPointer->data)	//���� ����Ű�� ������ ���� item�� ���� ��ġ�� ��
		{
			found = true;	//ã�����Ƿ� found �� ����
			if (pre == NULL)
				mList = mCurPointer->next;	//�׸� ������ �ٸ� ���Ұ� ���� �� �׸��� ���� ���Ҹ� ù��° ���ҷ� �Ѵ�.
			else {
				pre->next = mCurPointer->next;
				delete mCurPointer;
			}	//������ ������ ���� ���Ҹ� '����Ű�� �׸��� ���� ����'�� �ٲ۴�.
			mLength--;	//����Ʈ�� ���̸� 1 �ٿ��ش�.
		} else {
			pre = mCurPointer;
			mCurPointer = mCurPointer->next;
			moreToSearch = (mCurPointer != NULL);
		}	//��ġ���� ���� �� ���� ���Ҹ� ����Ų��. ��, pre�� ������ ���Ҹ� ����Ų��.
	}

	if (found)
		return 1;
	else
		return 0;	//������ �����ϸ� 1, �ƴϸ� 0�� �����Ѵ�.
}

//Change value of item which is in this list.
template <typename T>
int UnsortedLinkedList<T>::Replace(T item) {
	bool moreToSearch, found;
	NodeType<T> *location;	//���� ����

	location = mList;
	found = false;
	moreToSearch = (location != NULL);	//���� �ʱ�ȭ

	while (moreToSearch && !found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
	{
		if (item == location->data) {
			found = true;
			location->data = item;
		}	//��ġ�ϴ� �׸��� ã���� �� found�� ���� �������ְ� ����Ʈ�� �׸� item�� �������ش�.
		else {
			location = location->next;
			moreToSearch = (location != NULL);
		}	//ã�� ������ �� ���� �׸����� location�� �ű�� �� ���� NULL�̸� ����Ʈ�� ���̹Ƿ� moreToSearch�� ���� �������ش�.
	}

	if (found)
		return 1;
	else
		return 0;	//������ �����ϸ� 1, �׷��� ���ϸ� 0�� �����Ѵ�.
}

// Retrieve list element whose key matches item's key (if present).
template <typename T>
int UnsortedLinkedList<T>::Get(T &item) {
	bool moreToSearch, found;
	NodeType<T> *location;	//���� ����

	location = mList;
	found = false;
	moreToSearch = (location != NULL);	//���� �ʱ�ȭ

	while (moreToSearch && !found)	//����Ʈ�� ���� �ƴϸ鼭 ���� ã�� �ʾ����� �ݺ��Ѵ�.
	{
		if (item == location->data) {
			found = true;
			item = location->data;
		}	//��ġ�ϴ� �׸��� ã���� �� found�� ���� �������ְ� item�� �ش� �׸��� �������ش�.
		else {
			location = location->next;
			moreToSearch = (location != NULL);
		}	//ã�� ������ �� ���� �׸����� location�� �ű�� �� ���� NULL�̸� ����Ʈ�� ���̹Ƿ� moreToSearch�� ���� �������ش�.
	}

	if (found)
		return 1;
	else
		return 0;	//ã���� 1, �׷��� ���ϸ� 0�� �����Ѵ�.
}


// Initializes current pointer for an iteration through the list.
template <typename T>
void UnsortedLinkedList<T>::ResetList() {
	// current pointer �ʱ�ȭ
	mCurPointer = NULL;
}


// Gets the next element in list.
template <typename T>
void UnsortedLinkedList<T>::GetNextItem(T &item) {
	// current pointer �� NULL�̶�� ó�� node�� ����Ŵ.
	if (mCurPointer == NULL) {
		mCurPointer = mList;
	} else
		//current position �� ���� ���� �̵�
		mCurPointer = mCurPointer->next;

	//item �� current position �� info �� ����
	item = mCurPointer->data;
}


#endif	// _UNSORTEDLINKEDLIST_H_
