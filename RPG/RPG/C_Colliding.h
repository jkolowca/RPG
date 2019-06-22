#pragma once
#include "SFML/Graphics.hpp"

class C_Colliding {
public:
	bool IsColliding(sf::Vector2i _coord);

	virtual sf::Vector2i getCoordinates() = 0;
protected:
	bool colliding = true;
};