#ifndef UNICODE
#define UNICODE
#endif
#include "Window.h"
#include "EngineTime.h"
#include <string>
#include "imgui/imgui.h"
#include <exception>



extern IMGUI_IMPL_API LRESULT CALLBACK ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM uparam, LPARAM lparam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true; // If ImGui is handling the message, return true to prevent further processing

	switch (msg) {
	case WM_CREATE:
	{
		// Event fired when the window is created
		// collected here..

	}

	case WM_DESTROY:
	{
		// Event fired when the window is destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (window)
			window->onDestroy();
		::PostQuitMessage(0);
		break;
	}

	case WM_SETFOCUS:
	{
		// Event fired when the window is destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (window)
			window->onFocus();
		break;
	}

	case WM_KILLFOCUS:
	{
		// Event fired when the window is destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onKillFocus();
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);

	}
	return NULL;
}

Window::Window()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;



	if (!::RegisterClassEx(&wc))
		throw std::exception("Window failed to start");


	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, NULL);

	if (!m_hwnd)
		throw std::exception("Window failed to start");

	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);



	m_is_run = true;
}

bool Window::broadcast()
{
	EngineTime::LogFrameStart();

	MSG msg;

	if (!m_is_init)
	{
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		//	window->onCreate();

		this->m_is_init = true;
	}

	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}



	Sleep(1);
	EngineTime::LogFrameEnd();
	return true;
}

bool Window::isRun()
{
	if (m_is_run)
		broadcast();
	return m_is_run;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);

	return rc;
}

Window::~Window()
{
	if (!::DestroyWindow(m_hwnd))
		throw std::exception("Window failed to start");

}

void Window::onDestroy()
{
	m_is_run = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}
