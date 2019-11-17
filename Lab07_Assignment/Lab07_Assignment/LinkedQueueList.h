#pragma once

#include <iostream>

/**
*	LinkedQueueList.
*/
template <class T>
class LinkedQueueList {
public:
	// Constructor
	LinkedQueueList();

	// Destructor
	~LinkedQueueList();

	// Add an item to the very end of queue.
	bool Enqueue(const T &item);

	// Get the first item of queue and remove it.
	bool Dequeue(T &item);

	// Check if queue is empty.
	bool IsEmpty() const;

	// Remove all items in queue.
	void MakeEmpty();

	// Get the number of items in queue.
	int GetLength() const;

private:
	// Node for use in queue.
	template <class T>
	struct Node {
		T data;
		Node *next = NULL; // Pointer to the next node.
	};

	Node<T> *head = NULL, *tail = NULL; // Head & tail
	int length = 0;
};

template<class T>
LinkedQueueList<T>::LinkedQueueList() {}

template<class T>
LinkedQueueList<T>::~LinkedQueueList() {
	MakeEmpty(); // Empty queue before destruction
}

template<class T>
bool LinkedQueueList<T>::Enqueue(const T &item) {
	if (IsEmpty()) {
		// Create a new node
		Node<T> *newNode = new Node<T>;
		newNode->data = item;
		head = tail = newNode; // Set head & tail & current pointer
		++length;
		return true;
	} else {
		// Create a new node
		Node<T> *newNode = new Node<T>;
		newNode->data = item;
		tail->next = newNode; // Set next pointer for previous tail node
		tail = newNode; // Update tail pointer
		++length;
		return true;
	}
}

template<class T>
bool LinkedQueueList<T>::Dequeue(T &item) {
	if (IsEmpty()) {
		return false;
	}

	Node<T> *tempPtr = head;
	item = head->data; // Return first item;
	head = head->next; // Update head pointer;
	delete tempPtr; // Delete previous head
	--length;
	return true;
}

template<class T>
bool LinkedQueueList<T>::IsEmpty() const {
	return length == 0;
}

template<class T>
void LinkedQueueList<T>::MakeEmpty() {
	if (!IsEmpty()) {
		Node<T> *tempPtr;
		// Delete all nodes
		while (head != NULL) {
			tempPtr = head;
			head = head->next; // Move head pointer to the next node
			delete tempPtr; // Delete previous head
		}
		length = 0;
	}
}

template<class T>
int LinkedQueueList<T>::GetLength() const {
	return length;
}
