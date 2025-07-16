#include "AppWindow.h"
#include "InputSystem.h"

int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::create();
	}
	catch (...) { return -1; }

	{
		try
		{
			AppWindow::initialize();
			AppWindow* runningApp = (AppWindow*)AppWindow::get();
			runningApp->onCreate();

			while (runningApp->isRun());
		}
		catch (...)
		{
			GraphicsEngine::release();
			InputSystem::release();

			return -1;
		}
	}
	InputSystem::release();
	GraphicsEngine::release();
	return 0;
}