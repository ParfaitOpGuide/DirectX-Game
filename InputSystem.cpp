#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::m_system = nullptr;

InputSystem* InputSystem::get()
{
	return m_system;
}

void InputSystem::create()
{
	if (InputSystem::m_system) throw std::exception("Graphics Engine already exists");
	InputSystem::m_system = new InputSystem();
}

void InputSystem::release()
{
	if (!InputSystem::m_system) return;
	delete InputSystem::m_system;
}



void InputSystem::update()
{
	POINT curr_mouse_pos = {};
	::GetCursorPos(&curr_mouse_pos);

	if (m_first_time) {
		m_old_mouse_pos = Point(curr_mouse_pos.x, curr_mouse_pos.y);
		m_first_time = false;
	}

	if (curr_mouse_pos.x != m_old_mouse_pos.m_x || curr_mouse_pos.y != m_old_mouse_pos.m_y) {


		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			(*it)->onMouseMove(Point(curr_mouse_pos.x - m_old_mouse_pos.m_x, curr_mouse_pos.y - m_old_mouse_pos.m_y));
			++it;
		}

	}
	m_old_mouse_pos = Point(curr_mouse_pos.x, curr_mouse_pos.y);
	

	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0;i < 256;i++)
		{
			if (m_keys_state[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end())
				{
					if (i == VK_LBUTTON) 
					{
						if (m_keys_state[i] != m_old_keys_state[i]) 
							(*it)->onLeftMouseDown(Point(curr_mouse_pos.x, curr_mouse_pos.y));
					}

					if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onRightMouseDown(Point(curr_mouse_pos.x, curr_mouse_pos.y));
					}

					(*it)->onKeyDown(i);
					++it;
				}
			}
			else // up
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{

						if (i == VK_LBUTTON) {
							(*it)->onLeftMouseUp(Point(curr_mouse_pos.x, curr_mouse_pos.y));
						}
						if (i == VK_LBUTTON) {
							(*it)->onRightMouseUp(Point(curr_mouse_pos.x, curr_mouse_pos.y));
						}
						(*it)->onKeyUp(i);
						++it;
					}
				}
			}
		}
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	InputSystem::m_system = nullptr;
}



