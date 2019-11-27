#pragma once

#include <string>

class Launcher {
public:
	// 로그인하거나 회원가입 후 프로그램 시작
	void StartApp();

private:
	// 프로그램 첫번째 실행인지 확인
	bool IsFirstLaunch() const;

	// 로그인 창을 띄우고 로그인 성공 시 프로그램 실행
	void Login();

	// 계정 생성
	bool CreateAccount(const bool isAdmin);

	// 주어진 아이디와 비번으로 사용자가 존재하는지, 관리자인지 확인
	bool Authorize(const std::string &inputId, const std::string &inputPw, bool &isAdmin) const;

	// 비밀번호를 입력받음. 입력내용은 콘솔에 표시되지 않음.
	void GetPassword(std::string &pw) const;

	// 프로그램 시작
	void Start(const std::string &id, const bool isAdmin);

	// 현재 CMD창의 color scheme을 변경함
	void SetConsoleColor();
};
