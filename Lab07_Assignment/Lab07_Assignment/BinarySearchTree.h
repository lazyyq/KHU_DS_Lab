#pragma once

#include <iostream>

#include "LinkedQueueList.h"

enum OrderType { PRE, IN, POST };

// Binary Search Tree 
template<class T>
class BinarySearchTree {
public:
	// ������
	BinarySearchTree();

	// �Ҹ���
	~BinarySearchTree();

	/**
	*	@brief	Tree�� Empty���� Ȯ��
	*	@pre	none
	*	@post	none
	*	@return	Tree�� ��������� true����, �ƴϸ� false ����
	*/
	bool IsEmpty() const;

	/**
	*	@brief	Tree�� Full���� Ȯ��
	*	@pre	none
	*	@post	none
	*	@return	Tree�� Full�̸� true ����, �ƴϸ� false ����
	*/
	bool IsFull() const;

	/**
	*	@brief	Tree�� ����
	*	@pre	none
	*	@post	none
	*/
	void MakeEmpty();

	/**
	*	@brief	Tree�� node�� �� ������ Ȯ����
	*	@pre	none
	*	@post	none
	*	@return	Tree�� node ������ ����
	*/
	int GetLength();

	/**
	*	@brief	Tree�� �� node�� �߰��Ѵ�
	*	@pre	T�� ��ü�� ����
	*	@post	Tree�� �� node�� �߰���
	*	@return	�߰� ���� �� true, �ƴ� �� false
	*/
	bool Add(T item);

	/**
	*	@brief	Tree�� �����ϴ� node�� ������ ������Ʈ�Ѵ�
	*	@return	������Ʈ ���� �� true, �ƴ� �� false
	*/
	bool ReplaceItem(T item);

	/**
	*	@brief	Tree���� ������� �ϴ� node�� ã�� ����
	*	@pre	T�� ��ü�� ����
	*	@post	Tree���� �Է��� node�� ������
	*/
	void DeleteItem(T item);

	/**
	*	@brief	�Է��� ���� node�� Tree���� �˻���
	*	@pre	ã���� �ϴ� item�� �˻������ ���� found ����
	*	@post	node�� Tree�� �ִ��� �˻������ �˷���
	*	@return	�߰� �� true, �ƴϸ� false
	*/
	bool RetrieveItem(T &item);

	/**
	*	@brief	Tree�� node�� ��ũ���� ����Ѵ�.
	*	@pre	none
	*	@post	��ũ���� Tree�� InOrder, PreOrder, PostOrder ������� ���� ��µ�.
	*/
	void PrintTree(std::ostream &out);

	// Update queue with given order type
	void ResetTree(OrderType order);

	// Get next item in bst with given order type
	void GetNextItem(T &item, OrderType order,
		bool &finished);

private:
	// Tree�� �����ϴ� Node (node data, left ������, right ������)
	template<class T>
	struct Node {
		T data;
		Node *left;
		Node *right;
	};

	Node<T> *root;		// Node Ÿ���� root
	// Queues to store items in bst. For iterating purpose.
	LinkedQueueList<T> preQueue, inQueue, postQueue;

	// Empty tree
	void MakeEmptyTree(Node<T> *&root);

	// Count nodes
	int CountNodes(Node<T> *root);

	// Insert an item
	void Insert(Node<T> *&root, T item, bool &result);

	// Replace an item
	void Replace(Node<T> *&root, T item, bool &result);

	// Find the biggest item
	void GetPredecessor(Node<T> *root, T &item);

	// Delete a node
	void DeleteNode(Node<T> *&root);

	// Delete an item
	void Delete(Node<T> *&root, T item);

	// Retrieve an item
	void Retrieve(Node<T> *root, T &item, bool &found);

	// Print in InOrder
	void PrintInOrderTraversal(Node<T> *root, std::ostream &out);

	// Print in PreOrder
	void PrintPreOrderTraversal(Node<T> *root, std::ostream &out);

	// Print in PostOrder
	void PrintPostOrderTraversal(Node<T> *root, std::ostream &out);

	// Put items in queue with given order type
	void Reset(Node<T> *root, OrderType order);
};

// ������
template<class T>
BinarySearchTree<T>::BinarySearchTree() {
	root = NULL;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
	MakeEmpty();
	preQueue.MakeEmpty();
	inQueue.MakeEmpty();
	postQueue.MakeEmpty();
}

// Tree�� ����ִ��� Ȯ��
template<class T>
bool BinarySearchTree<T>::IsEmpty() const {
	if (root == NULL)			// root ��尡 NULL�� ��� true ����
		return true;
	else
		return false;			// root ��尡 NULL�� �ƴ� ��� false ����
}

// Tree�� Full���� Ȯ��
template<class T>
bool BinarySearchTree<T>::IsFull() const {
	Node *room;					// �ӽ��� node�� �����
	try {
		room = new Node;		// �� ��带 �߰��� �� �ִ��� Ȯ��
		delete room;			// �ӽ÷� ���� room ��带 ����
		return false;			// isFull�� ���� false ����
	} catch (std::bad_alloc exception)		// �� �̻� ������ �߰��� �� �� ���� Full�� ���
	{
		return true;					// isFull�� ���� true ����
	}
}

// Tree�� ���
template<class T>
void BinarySearchTree<T>::MakeEmpty() {
	MakeEmptyTree(root);				// Tree �ʱ�ȭ �Լ� ȣ��
}

// Tree�� node������ �˷���
template<class T>
int BinarySearchTree<T>::GetLength() {
	return CountNodes(root);			// node ������ ���� �Լ� ȣ��
}

// Tree�� ���ο� node �߰�
template<class T>
bool BinarySearchTree<T>::Add(T item) {
	bool result = false;
	Insert(root, item, result);					// �� node �߰��ϴ� �Լ� ȣ��
	return result;
}

// Node�� ���� ������Ʈ
template<class T>
bool BinarySearchTree<T>::ReplaceItem(T item) {
	bool result = false;
	Replace(root, item, result);
	return result;
}

// Tree�� node�� ����
template<class T>
void BinarySearchTree<T>::DeleteItem(T item) {
	Delete(root, item);					// �����ϴ� node �����ϴ� �Լ��� ȣ��
}

// Tree���� ã���� �ϴ� ���� node�� �˻�
template<class T>
bool BinarySearchTree<T>::RetrieveItem(T &item) {
	bool found = false;
	Retrieve(root, item, found);		// Tree �˻� �Լ� ȣ��
	return found;
}

// Tree�� node�� ������ ������ �����
template<class T>
void BinarySearchTree<T>::PrintTree(std::ostream &out) {
	std::cout << "[InOrder]" << std::endl;
	PrintInOrderTraversal(root, out);			// InOrder ������� ���
	std::cout << std::endl << "[PreOrder]" << std::endl;
	PrintPreOrderTraversal(root, out);			// PreOrder ������� ���
	std::cout << std::endl << "[PostOrder]" << std::endl;
	PrintPostOrderTraversal(root, out);			// PostOrder ������� ���
}

// Put items in queue
template<class T>
void BinarySearchTree<T>::ResetTree(OrderType order) {
	// Reset appropriate queue
	switch (order) {
	case PRE:
		preQueue.MakeEmpty(); break;
	case IN:
		inQueue.MakeEmpty(); break;
	case POST:
		postQueue.MakeEmpty(); break;
	}
	Reset(root, order); // Start recursion
}

// Get next item in bst
template<class T>
void BinarySearchTree<T>::GetNextItem(T &item, OrderType order,
	bool &finished) {
	// Dequeue item from appropriate queue
	switch (order) {
	case PRE:
		if (preQueue.IsEmpty()) {
			finished = true;
		} else {
			preQueue.Dequeue(item);
		}
		break;
	case IN:
		if (inQueue.IsEmpty()) {
			finished = true;
		} else {
			inQueue.Dequeue(item);
		}
		break;
	case POST:
		if (postQueue.IsEmpty()) {
			finished = true;
		} else {
			postQueue.Dequeue(item);
		}
		break;
	}
}

/////////////////////////////Global functions//////////////////////////
// Tree�� �ʱ�ȭ�ϴ� �Լ�
template<class T>
void BinarySearchTree<T>::MakeEmptyTree(Node<T> *&root) {
	root = NULL;			// root ��带 Null�� ��
}

// Tree�� node ������ ���� �Լ�
template<class T>
int BinarySearchTree<T>::CountNodes(Node<T> *root) {
	if (root == NULL)		// root ��尡 null�ϰ�� 0�� ����
		return 0;
	else
		// ����� ����, �����ʿ� ���� ����� ȣ��� root�� �ش��ϴ� 1�� ���ؼ� ���� ����
		return CountNodes(root->left) + CountNodes(root->right) + 1;
}

// BinarySearchTree�� ���ο� ��� �߰�
template<class T>
void BinarySearchTree<T>::Insert(Node<T> *&root, T item, bool &result) {
	if (root == NULL)				// root�� null�� ��� 
	{
		root = new Node<T>;	// root ��� ����
		root->left = NULL;			// root ����̹Ƿ� left�� right�� NULL�� ����
		root->right = NULL;
		root->data = item;			// root ����� ��
		result = true; // ���������� �߰������� �˸�
	} else if (root->data > item)		// root�� �����ϰ�, �� ���� ���ο� item ������ Ŭ ��
		Insert(root->left, item, result);	// root�� �������� Insert �Լ� �ٽ� ȣ��
	else if (root->data < item)		// root�� �����ϰ�, �� ���� ���ο� item ������ ���� ��
		Insert(root->right, item, result);	// root�� ���������� Insert �Լ� �ٽ� ȣ��
}

// Replace item
template<class T>
void BinarySearchTree<T>::Replace(Node<T> *&root, T item, bool &result) {
	if (root->data > item)		// root�� �����ϰ�, �� ���� ���ο� item ������ Ŭ ��
		Replace(root->left, item, result);	// root�� �������� Insert �Լ� �ٽ� ȣ��
	else if (root->data < item)		// root�� �����ϰ�, �� ���� ���ο� item ������ ���� ��
		Replace(root->right, item, result);	// root�� ���������� Insert �Լ� �ٽ� ȣ��
	else { // ��ü�ϰ��� �ϴ� �����͸� �߰���
		root->data = item;
		result = true;
	}
}

// ���� ū ���� ã�� �Լ� 
template<class T>
void BinarySearchTree<T>::GetPredecessor(Node<T> *root, T &item) {
	while (root->right != NULL)			// root�� �������� ������ ���
		root = root->right;				// root�� ������ ��尪�� root�� ������ �Ѵ�
	item = root->data;					// root ����� ���� item�� �����Ѵ�.
}

// ������� ��带 ã���� ������ Ʈ������ �� ��带 ����� �Լ�
template<class T>
void BinarySearchTree<T>::DeleteNode(Node<T> *&root) {
	T item;
	Node<T> *tempPtr;			// �ӽ� ��带 �����ϰ� root ��带 �ӽ� ��忡 ����
	tempPtr = root;

	if (root->left == NULL)				// ���ʳ�尡 ���� ��
	{
		root = root->right;				// ������ ��尡 root�� �ǵ��� �����ϰ� �ӽó�带 ����
		delete tempPtr;
	} else if (root->right == NULL)		// �����ʳ�尡 ���� ��
	{
		root = root->left;				// ���� ��尡 root�� �ǵ��� �����ϰ� �ӽó�带 ����
		delete tempPtr;
	} else {
		GetPredecessor(root->left, item);	// �߰��� �ִ� ��带 ����� ���� �� (left, right, child ��� ���� ���)
		root->data = item;					// ������� ��庸�� ���� ���� �߿� ���� ū ��带 ã��
		Delete(root->left, item);			// �� ���� ���� ��忡 ���縦 �ؼ� ���� ��ó�� ������
	}
}

// ���� ������� �ϴ� ��带 ã�� recursive �Լ�
template<class T>
void BinarySearchTree<T>::Delete(Node<T> *&root, T item) {
	if (item < root->data)				// root��尪���� item��尡 ���� ��
		Delete(root->left, item);		// ���ʳ��� ���� delete�Լ� ȣ��
	else if (item > root->data)			// root��尪���� item��尡 Ŭ ��
		Delete(root->right, item);		// �����ʳ��� ���� delete�Լ� ȣ��
	else
		DeleteNode(root);				// ã���� �ϴ� ���� ��ġ�ϴ� ��� deletenode �Լ� ȣ��
}

// Tree���� node�� �˻��ϴ� �Լ�
template<class T>
void BinarySearchTree<T>::Retrieve(Node<T> *root, T &item, bool &found) {
	if (root == NULL)						// root�� NULL�� ��� found�� false 
		found = false;
	else if (item < root->data)				// ã���� �ϴ� �����۰��� root������ ���� �� 
		Retrieve(root->left, item, found);	// ���� ���� ���� retrieve �Լ� ȣ��
	else if (item > root->data)				// ã���� �ϴ� �����۰��� root������ Ŭ ��
		Retrieve(root->right, item, found);	// ������ ���� ���� retrieve �Լ� ȣ��
	else {										// ã���� �ϴ� ���� ��ġ�� ��
		item = root->data;					// item�� ��� ������ ����
		found = true;						// found���� true�� �ؼ� ã�� ������ ����
	}
}

// InOrder ������� ����ϴ� �Լ� 
template<class T>
void BinarySearchTree<T>::PrintInOrderTraversal(Node<T> *root, std::ostream &out) {
	if (root != NULL)								// root�� �����ϴ� ���
	{
		PrintInOrderTraversal(root->left, out);		// root�� �������� ���� �ٽ� InOrder �Լ� ȣ��
		out << root->data;							// root ���
		PrintInOrderTraversal(root->right, out);	// root�� ���������� ���� �ٽ� InOrder �Լ� ȣ��
	}
}

// PreOrder ������� ����ϴ� �Լ�
template<class T>
void BinarySearchTree<T>::PrintPreOrderTraversal(Node<T> *root, std::ostream &out) {
	if (root != NULL)								// root�� �����ϴ� ���
	{
		out << root->data;							// root�� ���� ���
		PrintPreOrderTraversal(root->left, out);	// root�� �������� ���� PreOrder �Լ� �ٽ� ȣ��
		PrintPreOrderTraversal(root->right, out);	// root�� ���������� ���� PreOrder �Լ� �ٽ� ȣ��
	}
}

// PostOrder ������� ����ϴ� �Լ�
template<class T>
void BinarySearchTree<T>::PrintPostOrderTraversal(Node<T> *root, std::ostream &out) {
	if (root != NULL)								// root�� �����ϴ� ���
	{
		PrintPostOrderTraversal(root->left, out);	// root�� �������� ���� �ٽ� PostOrder �Լ� ȣ��
		PrintPostOrderTraversal(root->right, out);	// root�� ���������� ���� �ٽ� PostOrder �Լ� ȣ��
		out << root->data;							// root�� �� ���
	}
}

// Put items in queue
template<class T>
void BinarySearchTree<T>::Reset(Node<T> *root, OrderType order) {
	switch (order) {
	case PRE:
		if (root == NULL) {
			break;
		}
		preQueue.Enqueue(root->data); // Enqueue root first
		if (root->left != NULL) {
			Reset(root->left, order); // then left
		}
		if (root->right != NULL) {
			Reset(root->right, order); // then right
		}
		break;
	case IN:
		if (root == NULL) {
			break;
		}
		if (root->left != NULL) {
			Reset(root->left, order); // Enqueue left first
		}
		inQueue.Enqueue(root->data); // then root
		if (root->right != NULL) {
			Reset(root->right, order); // then right
		}
		break;
	case POST:
		if (root == NULL) {
			break;
		}
		if (root->left != NULL) {
			Reset(root->left, order); // Enqueue left irst
		}
		if (root->right != NULL) {
			Reset(root->right, order); // then right
		}
		postQueue.Enqueue(root->data); // then root
		break;
	}
}
