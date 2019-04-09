#include "Application.h"

Application::Application() {
	shared.window = &window;
	shared.eventManager = window.GetEventManager();
}
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