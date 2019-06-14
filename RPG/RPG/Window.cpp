#include "Window.h"
#include "Shared.h"

Window::Window(Shared* _shared) 
	: shared(_shared), isOpen(true), isFullscreen(false){
	Create();
	eventManager.AddCallback("resize", &Window::SwitchFullscreen, this);
}

Window::~Window() {
	window.close();
}

void Window::Create() {
	if (isFullscreen) {
		size = sf::Vector2u(sf::VideoMode::getDesktopMode().width,
			sf::VideoMode::getDesktopMode().height);
	}
	else size = WindowSize;
	window.create(sf::VideoMode(size.x, size.y, 32), title, sf::Style::None);
	window.setFramerateLimit(60);
}

void Window::Clear() {
	window.clear(sf::Color(0, 0, 0, 255));
}

void Window::Update() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			Close(); 
		if (window.hasFocus()) {
			eventManager.ProcessEvent(event);
		}
	}
	eventManager.Update();
}

void Window::Display() {
	window.display();
}

void Window::SwitchFullscreen(sf::Event::KeyEvent) {
	isFullscreen = !isFullscreen;
	window.close();
	Create();
	shared->viewManager->Position();
}

void Window::Close() {
	isOpen = false;
}

EventManager* Window::GetEventManager() {
	return &eventManager;
}

sf::Vector2u Window::GetSize() {
	return size;
}

bool Window::IsOpen() {
	return isOpen;
}

sf::RenderWindow* Window::GetRenderWindow() {
	return &window;
}