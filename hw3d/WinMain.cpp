#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow) 
{
	try {
		Window wnd(800, 300, "The Box");

		MSG msg;
		BOOL gResult;

		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.kbd.KeyIsPressed(VK_MENU))
			{
				MessageBox(nullptr, "Something Happened!", "Alt key was pressed",MB_OK);
			}

		}

		if (gResult == -1) {
			return -1;
		}

		//wParam here is the value passed to PostQuitMessage
		return msg.wParam;
	}
	catch(const CustomException& e) 
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch(const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}