#pragma once
#include <windows.h>
#include <winuser.h>
class Mouse
{
	public:
	Mouse();

	void updateMousePosition(HWND hWnd, UINT w, UINT h);
	void updateMouse();
	//singleton
	static Mouse* get();
	static void initialize();
	bool destroy();

	Mouse(Mouse const&) {};
	Mouse& operator=(Mouse const&) {};
	static Mouse* sharedInstance;

	float mouseX;
	float mouseY;

	PBYTE m_keys_state;
};

