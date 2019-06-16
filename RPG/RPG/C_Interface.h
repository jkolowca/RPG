#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>
class C_Interface
{
public:
	bool checkIfInteract(sf::Vector2f playerPosition);
	bool checkIfCollision(sf::Vector2f playerPosition);
protected:
	sf::Vector2f position;
};

