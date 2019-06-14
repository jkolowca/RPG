#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Shared.h"
#include "C_Moveable.h"


class Player : public C_Moveable
{
public:
	Player(Shared*, int);
	~Player();

	void Update();

	void move(sf::Vector2f, direction);
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
private:
	int id;
	sf::Sprite _Sprite;
	Shared* shared;
	sf::Vector2f _Source;

	//animation
	sf::Time frameTime;
	sf::Clock frameClock;
};