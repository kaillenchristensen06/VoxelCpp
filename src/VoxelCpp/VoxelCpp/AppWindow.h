#pragma once
#include "Window.h"


class AppWindow: public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
};

