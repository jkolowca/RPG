#include "Application.h"

Application::Application(): s_manager(&shared), shared{&window, window.GetEventManager(), window.GetRenderWindow()} {}
Application::~Application() {}

void Application::Update() {
	window.Update();
}
void Application::Render() {
	window.Clear();
	s_manager.Draw();
	window.Display();
}

Window* Application::GetWindow() {
	return &window;
}