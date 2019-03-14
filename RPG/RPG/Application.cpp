#include "Application.h"

Application::Application() {}
Application::~Application() {}

void Application::Update() {
	window.Clear();
	window.Update();
	window.Display();
}
void Application::Render() {}

Window* Application::GetWindow() {
	return &window;
}