#pragma once
#include <iostream>
#include "Shared.h"
#include "C_Moveable.h"
#include "C_Animated.h"


class Player : public C_Moveable, public C_Animated
{
public:
	Player(Shared*, int);
	~Player();
	void Update();
	void Move(sf::Vector2f, animation_type);
	sf::Sprite& getSprite() { return _Sprite; }
	void Draw()
	{
		shared->renderWindow->draw(_Sprite);
	}
	void setId(int _id) {
		id = _id;
	}

	int getId() {
		return id;
	}

	sf::Vector2i getCoordinates() {
		return coordinates;

	}
	void setCoordinates(sf::Vector2i _coordinates) {
		coordinates = _coordinates;
	}

private:
	sf::Vector2i coordinates;
	int id;
	sf::Sprite _Sprite;
	Shared* shared;
};