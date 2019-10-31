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
};

