#include <Windows.h>
#include "WindowsMessageMap.h"
#include <sstream>

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	OutputDebugString(mm(msg, lParam, wParam).c_str());

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "Hello there sir!");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "No sir, please!");
		}
		break;
	case WM_CHAR:
		{
			static std::string title;
			title.push_back((char)wParam);
			SetWindowText(hWnd, title.c_str());
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINTS pt = MAKEPOINTS(lParam);
			std::stringstream oss;
			oss << "(" << pt.x << ", " << pt.y << ")";
			SetWindowText(hWnd, oss.str().c_str());
		}
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow) 
{
	const auto pClassName = "hw3d";

	//Register Window Class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof( wc );
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx( &wc );

	//Create Window Instance
	HWND hWnd = CreateWindowEx(
		0, pClassName, 
		"My Window", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480, 
		nullptr, nullptr, hInstance, nullptr
	);

	//Show the Window
	ShowWindow(hWnd, SW_SHOW);

	//Message Pump
	MSG msg;
	BOOL gResult;

	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1) {
		return -1;
	}
	else {
		return msg.wParam;
	}

}