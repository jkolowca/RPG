#pragma once
#include <SFML/Graphics.hpp>

class C_Interactive {
public:
	void isInteracting(sf::Vector2i _coord);
	virtual void Interact() =0;
	virtual sf::Vector2i getCoordinates() = 0;
};