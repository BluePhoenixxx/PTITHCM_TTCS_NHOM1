#pragma once

#ifndef MOUSEHOOKER_HPP_
#define MOUSEHOOKER_HPP_

#include "ADataHooker.hpp"

class MouseHooker : public ADataHooker
{
public:
	MouseHooker();
	~MouseHooker() = default;

	void startHook();
	void stopHook();
	// theo dõi các sự kiện chuột trên hệ thống
	static LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
	// hàm theo dõi di chuyển của chuột  và xác đinh vị trí
	static void mouseMoved(WPARAM wParam, std::pair<int, int> pos, PMSLLHOOKSTRUCT msStruct, char buff[MAXLENGTH]);
};

#endif // !MOUSEHOOKER_HPP_