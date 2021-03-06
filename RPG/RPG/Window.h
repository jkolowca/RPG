#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

struct Shared;

class Window {
public:
	Window(Shared*);
	~Window();

	void Create();
	
	void Clear();
	void Display();
	void Update();

	void SwitchFullscreen(sf::Event::KeyEvent);
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
	Shared* shared;
};