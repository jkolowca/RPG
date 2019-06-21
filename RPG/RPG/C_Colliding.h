#pragma once
#include "SFML/Graphics.hpp"

class C_Colliding {
public:
	bool IsColliding(sf::Vector2i _coord) {
		sf::Vector2i coord = getCoordinates();
		if (_coord.x >= coord.x && _coord.x <= coord.x + size.x && _coord.y >= coord.y && _coord.y <= coord.y + size.y) return true;
		return false;
	}

	virtual sf::Vector2i getCoordinates() = 0;
	void setSize(sf::Vector2i _size) {
		size = _size;
	}
protected:
	sf::Vector2i size;
};