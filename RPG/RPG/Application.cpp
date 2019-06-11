#include "Application.h"

Application::Application(): v_manager(&shared), shared{&window, window.GetEventManager(), window.GetRenderWindow()} {}
Application::~Application() {}

void Application::Update() {
	window.Update();
}
void Application::Render() {
	window.Clear();
	v_manager.Draw();
	window.Display();
}

Window* Application::GetWindow() {
	return &window;
}