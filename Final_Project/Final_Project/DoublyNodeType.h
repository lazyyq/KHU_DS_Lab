#pragma once

/**
*	연결리스트에서 쓰이는 NodeType의 구조체
*/
template <typename T>
struct DoublyNodeType {
	T data; // 각 노드의 데이터.
	DoublyNodeType *prev = nullptr; // 노드의 앞을 가리키는 포인터.
	DoublyNodeType *next = nullptr; // 노드의 다음를 가리키는 포인터.
};
