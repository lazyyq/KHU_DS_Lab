#pragma once

/**
*	���Ḯ��Ʈ���� ���̴� NodeType�� ����ü
*/
template <typename T>
struct DoublyNodeType {
	T data; // �� ����� ������.
	DoublyNodeType *prev = NULL; // ����� ���� ����Ű�� ������.
	DoublyNodeType *next = NULL; // ����� ������ ����Ű�� ������.
};
