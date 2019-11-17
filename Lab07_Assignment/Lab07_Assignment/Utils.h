#pragma once

#include <iostream>

namespace utils {
	/**
	*	@brief	CMD 창 초기화.
	*	@post	CMD 창 위의 모든 메시지가 삭제됨.
	*/
	void Clear();

	/**
	*	@brief	CMD를 멈춤.
	*/
	void Pause();

	/**
	*	@brief	메시지를 화면에 표시하고 CMD를 멈춤.
	*	@param	message	CMD를 멈추기 전에 화면에 표시할 메시지.
	*/
	void Pause(const std::string &message);

	/**
	*	@brief	키보드 입력으로 숫자를 받음.
	*	@post	입력이 숫자가 맞다면 숫자를 n에 저장함.
	*	@param	n	사용자가 입력한 게 숫자가 맞다면 숫자가 저장됨.
	*	@return	입력이 숫자가 맞다면 1, 아니면 0.
	*/
	int GetNum(int &n);

	/**
	*	@brief	스트링의 문자를 전부 소문자로 변환.
	*	@post	스트링의 문자열이 전부 소문자로 변환됨.
	*	@param	str	소문자로 변환할 스트링
	*	@return	소문자로 변환된 스트링
	*/
	std::string ToLowerCase(const std::string &str);

	/**
	*	@brief	wstring을 string으로 변환
	*	@param	wstr	변환할 wstring, 최대 길이 10000자
	*	@return	변환된 string
	*/
	std::string WstrToStr(const std::wstring &wstr);
};
