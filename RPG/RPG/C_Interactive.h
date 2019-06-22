#pragma once
#include <SFML/Graphics.hpp>

class C_Interactive {
public:
	void isInteracting(sf::Vector2i _coord) {
		sf::Vector2i coord = getCoordinates();
		if (_coord == coord) return;
		if (_coord.x == coord.x - 1 || _coord.x == coord.x + 1 || _coord.x == coord.x)
			if (_coord.y == coord.y - 1 || _coord.y == coord.y + 1 || _coord.y == coord.y)
				Interact();
	}
	virtual void Interact() =0;
	virtual sf::Vector2i getCoordinates() = 0;
};