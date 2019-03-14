#pragma once
#include "Window.h"
class Application {
public:
	Application();
	~Application();

	void Update();
	void Render();

	Window* GetWindow();
private:
	Window window;
};