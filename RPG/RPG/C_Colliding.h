#pragma once
#include "SFML/Graphics.hpp"

class C_Colliding {
public:
	bool IsColliding(sf::Vector2i _coord) {
		if (!colliding) return false;
		sf::Vector2i coord = getCoordinates();
		if (_coord.x >= coord.x && _coord.x <= coord.x  && _coord.y >= coord.y && _coord.y <= coord.y) return true;
		return false;
	}

	virtual sf::Vector2i getCoordinates() = 0;
protected:
	bool colliding = true;
};