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

	/**
	*	@brief	��Ʈ���� ���ڸ� ���� �ҹ��ڷ� ��ȯ.
	*	@post	��Ʈ���� ���ڿ��� ���� �ҹ��ڷ� ��ȯ��.
	*	@param	str	�ҹ��ڷ� ��ȯ�� ��Ʈ��
	*	@return	�ҹ��ڷ� ��ȯ�� ��Ʈ��
	*/
	std::string ToLowerCase(const std::string &str);

	/**
	*	@brief	wstring�� string���� ��ȯ
	*	@param	wstr	��ȯ�� wstring, �ִ� ���� 10000��
	*	@return	��ȯ�� string
	*/
	std::string WstrToStr(const std::wstring &wstr);
};
