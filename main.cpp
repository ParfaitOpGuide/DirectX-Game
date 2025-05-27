#include "AppWindow.h"

int main()
{
	//AppWindow::initialize();
	AppWindow* runningApp = (AppWindow*) AppWindow::get();
	runningApp->onCreate();

	
		while (runningApp->isRun())
		{
			runningApp->broadcast();
		}
	

	return 0;
}