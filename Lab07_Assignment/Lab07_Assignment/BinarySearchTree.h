#pragma once

#include <iostream>

#include "LinkedQueueList.h"

enum OrderType { PRE, IN, POST };

// Binary Search Tree 
template<class T>
class BinarySearchTree {
public:
	// 생성자
	BinarySearchTree();

	// 소멸자
	~BinarySearchTree();

	/**
	*	@brief	Tree가 Empty인지 확인
	*	@pre	none
	*	@post	none
	*	@return	Tree가 비어있으면 true리턴, 아니면 false 리턴
	*/
	bool IsEmpty() const;

	/**
	*	@brief	Tree가 Full인지 확인
	*	@pre	none
	*	@post	none
	*	@return	Tree가 Full이면 true 리턴, 아니면 false 리턴
	*/
	bool IsFull() const;

	/**
	*	@brief	Tree를 비운다
	*	@pre	none
	*	@post	none
	*/
	void MakeEmpty();

	/**
	*	@brief	Tree에 node가 몇 개인지 확인함
	*	@pre	none
	*	@post	none
	*	@return	Tree의 node 개수를 리턴
	*/
	int GetLength();

	/**
	*	@brief	Tree에 새 node를 추가한다
	*	@pre	T의 객체를 생성
	*	@post	Tree에 새 node가 추가됨
	*	@return	추가 성공 시 true, 아닐 시 false
	*/
	bool Add(T item);

	/**
	*	@brief	Tree에 존재하는 node의 정보를 업데이트한다
	*	@return	업데이트 성공 시 true, 아닐 시 false
	*/
	bool ReplaceItem(T item);

	/**
	*	@brief	Tree에서 지우고자 하는 node를 찾고 지움
	*	@pre	T의 객체를 생성
	*	@post	Tree에서 입력한 node가 삭제됨
	*/
	void DeleteItem(T item);

	/**
	*	@brief	입력한 값의 node를 Tree에서 검색함
	*	@pre	찾고자 하는 item과 검색결과에 대한 found 설정
	*	@post	node가 Tree에 있는지 검색결과를 알려줌
	*	@return	발견 시 true, 아니면 false
	*/
	bool RetrieveItem(T &item);

	/**
	*	@brief	Tree의 node를 스크린에 출력한다.
	*	@pre	none
	*	@post	스크린에 Tree가 InOrder, PreOrder, PostOrder 방법으로 각각 출력됨.
	*/
	void PrintTree(std::ostream &out);

	// Update queue with given order type
	void ResetTree(OrderType order);

	// Get next item in bst with given order type
	void GetNextItem(T &item, OrderType order,
		bool &finished);

private:
	// Tree를 구성하는 Node (node data, left 포인터, right 포인터)
	template<class T>
	struct Node {
		T data;
		Node *left;
		Node *right;
	};

	Node<T> *root;		// Node 타입의 root
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

// 생성자
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

// Tree가 비어있는지 확인
template<class T>
bool BinarySearchTree<T>::IsEmpty() const {
	if (root == NULL)			// root 노드가 NULL인 경우 true 리턴
		return true;
	else
		return false;			// root 노드가 NULL이 아닌 경우 false 리턴
}

// Tree가 Full인지 확인
template<class T>
bool BinarySearchTree<T>::IsFull() const {
	Node *room;					// 임시의 node를 만들고
	try {
		room = new Node;		// 새 노드를 추가할 수 있는지 확인
		delete room;			// 임시로 만든 room 노드를 지움
		return false;			// isFull에 대한 false 리턴
	} catch (std::bad_alloc exception)		// 더 이상 아이템 추가를 할 수 없고 Full일 경우
	{
		return true;					// isFull에 대한 true 리턴
	}
}

// Tree를 비움
template<class T>
void BinarySearchTree<T>::MakeEmpty() {
	MakeEmptyTree(root);				// Tree 초기화 함수 호출
}

// Tree의 node개수를 알려줌
template<class T>
int BinarySearchTree<T>::GetLength() {
	return CountNodes(root);			// node 개수를 새는 함수 호출
}

// Tree에 새로운 node 추가
template<class T>
bool BinarySearchTree<T>::Add(T item) {
	bool result = false;
	Insert(root, item, result);					// 새 node 추가하는 함수 호출
	return result;
}

// Node의 정보 업데이트
template<class T>
bool BinarySearchTree<T>::ReplaceItem(T item) {
	bool result = false;
	Replace(root, item, result);
	return result;
}

// Tree의 node를 지움
template<class T>
void BinarySearchTree<T>::DeleteItem(T item) {
	Delete(root, item);					// 존재하는 node 삭제하는 함수를 호출
}

// Tree에서 찾고자 하는 값의 node를 검색
template<class T>
bool BinarySearchTree<T>::RetrieveItem(T &item) {
	bool found = false;
	Retrieve(root, item, found);		// Tree 검색 함수 호출
	return found;
}

// Tree의 node를 각각의 방법대로 출력함
template<class T>
void BinarySearchTree<T>::PrintTree(std::ostream &out) {
	std::cout << "[InOrder]" << std::endl;
	PrintInOrderTraversal(root, out);			// InOrder 방법으로 출력
	std::cout << std::endl << "[PreOrder]" << std::endl;
	PrintPreOrderTraversal(root, out);			// PreOrder 방법으로 출력
	std::cout << std::endl << "[PostOrder]" << std::endl;
	PrintPostOrderTraversal(root, out);			// PostOrder 방법으로 출력
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
// Tree를 초기화하는 함수
template<class T>
void BinarySearchTree<T>::MakeEmptyTree(Node<T> *&root) {
	root = NULL;			// root 노드를 Null로 함
}

// Tree의 node 개수를 세는 함수
template<class T>
int BinarySearchTree<T>::CountNodes(Node<T> *root) {
	if (root == NULL)		// root 노드가 null일경우 0을 리턴
		return 0;
	else
		// 노드의 왼쪽, 오른쪽에 대한 재귀적 호출과 root에 해당하는 1을 더해서 값을 리턴
		return CountNodes(root->left) + CountNodes(root->right) + 1;
}

// BinarySearchTree에 새로운 노드 추가
template<class T>
void BinarySearchTree<T>::Insert(Node<T> *&root, T item, bool &result) {
	if (root == NULL)				// root가 null일 경우 
	{
		root = new Node<T>;	// root 노드 생성
		root->left = NULL;			// root 노드이므로 left와 right는 NULL로 설정
		root->right = NULL;
		root->data = item;			// root 노드의 값
		result = true; // 성공적으로 추가했음을 알림
	} else if (root->data > item)		// root가 존재하고, 그 값이 새로운 item 값보다 클 때
		Insert(root->left, item, result);	// root의 왼쪽으로 Insert 함수 다시 호출
	else if (root->data < item)		// root가 존재하고, 그 값이 새로운 item 값보다 작을 때
		Insert(root->right, item, result);	// root의 오른쪽으로 Insert 함수 다시 호출
}

// Replace item
template<class T>
void BinarySearchTree<T>::Replace(Node<T> *&root, T item, bool &result) {
	if (root->data > item)		// root가 존재하고, 그 값이 새로운 item 값보다 클 때
		Replace(root->left, item, result);	// root의 왼쪽으로 Insert 함수 다시 호출
	else if (root->data < item)		// root가 존재하고, 그 값이 새로운 item 값보다 작을 때
		Replace(root->right, item, result);	// root의 오른쪽으로 Insert 함수 다시 호출
	else { // 교체하고자 하는 데이터를 발견함
		root->data = item;
		result = true;
	}
}

// 가장 큰 값을 찾는 함수 
template<class T>
void BinarySearchTree<T>::GetPredecessor(Node<T> *root, T &item) {
	while (root->right != NULL)			// root의 오른쪽이 존재할 경우
		root = root->right;				// root의 오른쪽 노드값이 root에 오도록 한다
	item = root->data;					// root 노드의 값을 item에 복사한다.
}

// 지우려는 노드를 찾으면 실제로 트리에서 그 노드를 지우는 함수
template<class T>
void BinarySearchTree<T>::DeleteNode(Node<T> *&root) {
	T item;
	Node<T> *tempPtr;			// 임시 노드를 생성하고 root 노드를 임시 노드에 복사
	tempPtr = root;

	if (root->left == NULL)				// 왼쪽노드가 없을 때
	{
		root = root->right;				// 오른쪽 노드가 root가 되도록 복사하고 임시노드를 지움
		delete tempPtr;
	} else if (root->right == NULL)		// 오른쪽노드가 없을 때
	{
		root = root->left;				// 왼쪽 노드가 root가 되도록 복사하고 임시노드를 지움
		delete tempPtr;
	} else {
		GetPredecessor(root->left, item);	// 중간에 있는 노드를 지우고 싶을 때 (left, right, child 노드 있을 경우)
		root->data = item;					// 지우려는 노드보다 작은 노드들 중에 가장 큰 노드를 찾음
		Delete(root->left, item);			// 그 값을 지울 노드에 복사를 해서 지운 것처럼 눈속임
	}
}

// 내가 지우려고 하는 노드를 찾는 recursive 함수
template<class T>
void BinarySearchTree<T>::Delete(Node<T> *&root, T item) {
	if (item < root->data)				// root노드값보다 item노드가 작을 때
		Delete(root->left, item);		// 왼쪽노드로 가서 delete함수 호출
	else if (item > root->data)			// root노드값보다 item노드가 클 때
		Delete(root->right, item);		// 오른쪽노드로 가서 delete함수 호출
	else
		DeleteNode(root);				// 찾고자 하는 값이 일치하는 경우 deletenode 함수 호출
}

// Tree에서 node를 검색하는 함수
template<class T>
void BinarySearchTree<T>::Retrieve(Node<T> *root, T &item, bool &found) {
	if (root == NULL)						// root가 NULL인 경우 found는 false 
		found = false;
	else if (item < root->data)				// 찾고자 하는 아이템값이 root값보다 작을 때 
		Retrieve(root->left, item, found);	// 왼쪽 노드로 가서 retrieve 함수 호출
	else if (item > root->data)				// 찾고자 하는 아이템값이 root값보다 클 때
		Retrieve(root->right, item, found);	// 오른쪽 노드로 가서 retrieve 함수 호출
	else {										// 찾고자 하는 값과 일치할 때
		item = root->data;					// item에 노드 정보를 복사
		found = true;						// found값을 true로 해서 찾는 과정을 멈춤
	}
}

// InOrder 방법으로 출력하는 함수 
template<class T>
void BinarySearchTree<T>::PrintInOrderTraversal(Node<T> *root, std::ostream &out) {
	if (root != NULL)								// root가 존재하는 경우
	{
		PrintInOrderTraversal(root->left, out);		// root의 왼쪽으로 가서 다시 InOrder 함수 호출
		out << root->data;							// root 출력
		PrintInOrderTraversal(root->right, out);	// root의 오른쪽으로 가서 다시 InOrder 함수 호출
	}
}

// PreOrder 방법으로 출력하는 함수
template<class T>
void BinarySearchTree<T>::PrintPreOrderTraversal(Node<T> *root, std::ostream &out) {
	if (root != NULL)								// root가 존재하는 경우
	{
		out << root->data;							// root를 먼저 출력
		PrintPreOrderTraversal(root->left, out);	// root의 왼쪽으로 가서 PreOrder 함수 다시 호출
		PrintPreOrderTraversal(root->right, out);	// root의 오른쪽으로 가서 PreOrder 함수 다시 호출
	}
}

// PostOrder 방법으로 출력하는 함수
template<class T>
void BinarySearchTree<T>::PrintPostOrderTraversal(Node<T> *root, std::ostream &out) {
	if (root != NULL)								// root가 존재하는 경우
	{
		PrintPostOrderTraversal(root->left, out);	// root의 왼쪽으로 가서 다시 PostOrder 함수 호출
		PrintPostOrderTraversal(root->right, out);	// root의 오른쪽으로 가서 다시 PostOrder 함수 호출
		out << root->data;							// root의 값 출력
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
