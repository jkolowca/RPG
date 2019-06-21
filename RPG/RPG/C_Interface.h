#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>
class C_Interface
{
public:
	bool checkIfInteract(sf::Vector2f playerPosition); //zwaraca true jesli postaæ jest obok obiektu
	bool checkIfCollision(sf::Vector2f playerPosition); //zwraca true jeœli nachodz¹ na siebie
	void SetObjPosition(sf::Vector2f);
	sf::Vector2f ObjGetPosition();
protected:
	sf::Vector2f position;
};