#pragma once
#include <Windows.h>


class Window
{
public:
	Window();

	bool isRun();

	RECT getClientWindowRect();

	~Window();

	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

	virtual void onFocus();
	virtual void onKillFocus();
private:
	bool broadcast();

protected:
	HWND m_hwnd;
	bool m_is_run;
	bool m_is_init = false;
};

