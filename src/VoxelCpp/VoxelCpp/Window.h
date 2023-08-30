#pragma once
#include <Windows.h>



class Window
{
public:
	Window();
	//initialize Window
	bool init();
	bool broadcast();
	//Release Window
	bool release();
	bool isRunning();

	//EVENTS
	virtual void onCreate()=0;
	virtual void OnUpdate()=0;
	virtual void OnDestroy()=0;

	~Window();
protected:
	HWND m_hwnd;
	bool m_is_isRunning;
};

