#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

#define WINDOWSIZE sf::Vector2u(1200,800);

class Window {
public:
	Window();
	~Window();

	void Create();
	
	void Clear();
	void Display();
	void Update();

	void SwitchFullscreen();
	void Close();
	
	sf::RenderWindow* GetRenderWindow();
	EventManager* GetEventManager();
	sf::Vector2u GetSize();
	bool IsOpen();

private:
	bool isFullscreen;
	bool isOpen;
	sf::Vector2u size;
	std::string title;
	sf::RenderWindow window;
	EventManager eventManager;
};