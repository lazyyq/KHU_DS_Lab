#pragma once

#include <string>

class Launcher {
public:
	// �α����ϰų� ȸ������ �� ���α׷� ����
	void StartApp();

private:
	// ���α׷� ù��° �������� Ȯ��
	bool IsFirstLaunch() const;

	// �α��� â�� ���� �α��� ���� �� ���α׷� ����
	void Login();

	// ���� ����
	bool CreateAccount(const bool isAdmin);

	// �־��� ���̵�� ������� ����ڰ� �����ϴ���, ���������� Ȯ��
	bool Authorize(const std::string &inputId, const std::string &inputPw, bool &isAdmin) const;

	// ��й�ȣ�� �Է¹���. �Է³����� �ֿܼ� ǥ�õ��� ����.
	void GetPassword(std::string &pw) const;

	// ���α׷� ����
	void Start(const std::string &id, const bool isAdmin);

	// ���� CMDâ�� color scheme�� ������
	void SetConsoleColor();
};
