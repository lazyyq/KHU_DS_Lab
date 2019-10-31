#pragma once

#include <iostream>

namespace utils {
	/**
	*	@brief	CMD â �ʱ�ȭ.
	*	@post	CMD â ���� ��� �޽����� ������.
	*/
	void Clear();

	/**
	*	@brief	CMD�� ����.
	*/
	void Pause();

	/**
	*	@brief	�޽����� ȭ�鿡 ǥ���ϰ� CMD�� ����.
	*	@param	message	CMD�� ���߱� ���� ȭ�鿡 ǥ���� �޽���.
	*/
	void Pause(const std::string &message);

	/**
	*	@brief	Ű���� �Է����� ���ڸ� ����.
	*	@post	�Է��� ���ڰ� �´ٸ� ���ڸ� n�� ������.
	*	@param	n	����ڰ� �Է��� �� ���ڰ� �´ٸ� ���ڰ� �����.
	*	@return	�Է��� ���ڰ� �´ٸ� 1, �ƴϸ� 0.
	*/
	int GetNum(int &n);
};

