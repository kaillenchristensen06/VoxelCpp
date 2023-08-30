#include "Window.h"

Window* window = nullptr;

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{

	case WM_CREATE:
	{
		//called when window is created
		window->onCreate();
		break;
	}

	case WM_DESTROY:
	{
		//called when window is destroyed
		window->OnDestroy();
		::PostQuitMessage(0);
		break;
	}

	//called when s
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}


bool Window::init()
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
	//(LPCWSTR)
	wc.lpszClassName = (LPCWSTR)"MyWindowClass";
	wc.lpszMenuName = (LPCWSTR)"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;


	if (!::RegisterClassEx(&wc)) //if window registration fails, return false
		return false;

	if (!window)
		window = this;

	//creat Window
	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, (LPCWSTR)"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, NULL);

	//if creation fails, return false
	if (!m_hwnd)
		return false;

	//show the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	

	//set to indicate window is running
	m_is_isRunning = true;
	return true;
}

bool Window::broadcast()
{
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	window->OnUpdate();

	Sleep(0);

	return true;
}

bool Window::release()
{
	//destroy Window
	if (!::DestroyWindow(m_hwnd))
		return false;


	return true;
}

bool Window::isRunning()
{
	return m_is_isRunning;
}

void Window::OnDestroy()
{
	m_is_isRunning = false;
}

Window::~Window()
{
}
