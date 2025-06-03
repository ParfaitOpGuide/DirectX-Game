#include "Mouse.h"
#include <iostream>

Mouse* Mouse::sharedInstance;

Mouse::Mouse()
{
}

void Mouse::updateMousePosition(HWND hWnd, UINT w, UINT h)
{
	POINT cursorPos;
	::GetCursorPos(&cursorPos);

	// Convert from screen coordinates to client coordinates
	::ScreenToClient(hWnd, &cursorPos);




	/*
	if (cursorPos.x << w && cursorPos.y << h)
	{
		//less than half width is negative range, initially displayed from 0 to 1, then right side is 1 to 2, so we must push the scale back
		mouseX = cursorPos.x / (w / 2.0);
		mouseX -= 1;
		
		mouseY = cursorPos.y / (h / 2.0);
		mouseY -= 1;
		mouseY *= -1;



	}*/

	mouseX = cursorPos.x;
	mouseY = cursorPos.y;
}

void Mouse::updateMouse() {
	if (::GetKeyboardState(m_keys_state)) {

	}
}

void Mouse::initialize()
{
	sharedInstance = new Mouse();
}

bool Mouse::destroy()
{
	delete this;
	return true;
}

Mouse* Mouse::get()
{
	if (!sharedInstance) {
		initialize();
	}

	return sharedInstance;
}