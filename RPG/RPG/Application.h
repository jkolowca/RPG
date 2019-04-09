#pragma once
#include "Window.h"
#include "Shared.h"
class Application {
public:
	Application();
	~Application();

	void Update();
	void Render();

	Window* GetWindow();
private:
	Window window;
	Shared shared;
};