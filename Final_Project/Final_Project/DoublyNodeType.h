#pragma once

/**
*	���Ḯ��Ʈ���� ���̴� NodeType�� ����ü
*/
template <typename T>
struct DoublyNodeType {
	T data; // �� ����� ������.
	DoublyNodeType *prev = nullptr; // ����� ���� ����Ű�� ������.
	DoublyNodeType *next = nullptr; // ����� ������ ����Ű�� ������.
};
