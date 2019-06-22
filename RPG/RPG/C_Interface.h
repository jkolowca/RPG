#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>
class C_Interface
{
public:
	bool checkIfInteract(sf::Vector2f playerPosition); //zwaraca true jesli postaæ jest obok obiektu
	void SetObjPosition(sf::Vector2f);
	sf::Vector2f ObjGetPosition();
protected:
	sf::Vector2f position;
};