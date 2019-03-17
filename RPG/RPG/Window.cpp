#include "Window.h"

Window::Window() 
	:isOpen(true), isFullscreen(false){
	Create();
}

Window::~Window() {
	window.close();
}

void Window::Create() {
	if (isFullscreen) {
		size = sf::Vector2u(sf::VideoMode::getDesktopMode().width,
			sf::VideoMode::getDesktopMode().height);
	}
	else size = WINDOWSIZE;
	window.create(sf::VideoMode(size.x, size.y, 32), title, sf::Style::Close);
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

void Window::SwitchFullscreen() {
	isFullscreen = !isFullscreen;
	window.close();
	Create();
}

void Window::Close() {
	isOpen = false;
}

sf::Vector2u Window::GetSize() {
	return size;
}

bool Window::IsOpen() {
	return isOpen;
}