#include "Application.h"

Application::Application(): v_manager(&shared), shared{&window, window.GetEventManager(), window.GetRenderWindow()} {}
Application::~Application() {}

void Application::Update() {
	window.Update();
	v_manager.Update();
}
void Application::Render() {
	window.Clear();
	v_manager.Draw();
	window.Display();
}

Window* Application::GetWindow() {
	return &window;
}