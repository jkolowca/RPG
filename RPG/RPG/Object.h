#pragma once
#include "Shared.h"
#include "C_Colliding.h"
#include "C_Interactive.h"
#include <iostream>
#include <SFML/Graphics.hpp>
class Object: public C_Colliding, public C_Interactive
{
public:
	Object(Shared*,std::string,sf::Vector2f size,unsigned int _ID);

	void setPosition(sf::Vector2f _position) {
		Sprite.setPosition(_position);
	}
	virtual void Update() {}
	void Draw()
	{
		shared->renderWindow->draw(Sprite);
	}

	sf::Vector2i getCoordinates() {
		return coordinates;

	}
	void setCoordinates(sf::Vector2i _coordinates) {
		coordinates = _coordinates;
	}
	void setLocked(bool _t) {
		locked = _t;
	}
protected:
	bool locked = false;
	sf::Sprite Sprite;
private:
	sf::Vector2i coordinates;
	Shared* shared;
	unsigned int ID;
};

