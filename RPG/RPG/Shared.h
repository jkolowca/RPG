#pragma once
#include "Window.h"
#include "TextureManager.h"
#include "ViewManager.h"
#define TileSize 72
#define PlayerSize 64

struct  Shared {
	Shared(Window* _w, EventManager* _e, sf::RenderWindow* _r, ViewManager* _v) :window(_w), eventManager(_e), renderWindow(_r), viewManager(_v){}
	Window* window;
	sf::RenderWindow* renderWindow;
	EventManager* eventManager;
	TextureManager textureManager;
	ViewManager* viewManager;
};