#pragma once
#include <iostream>
#include "Shared.h"
#include "C_Moveable.h"
#include "C_Animated.h"
#include "C_Colliding.h"


class Player : public C_Moveable, public C_Animated, public C_Colliding
{
public:
	Player(Shared*, int);
	~Player();
	void Update();
	void Move(sf::Vector2f, animation_type);
	sf::Sprite& getSprite();
	void Draw();

	void setId(int _id);
	int getId();

	sf::Vector2i getCoordinates();
private:
	int id;
	sf::Sprite _Sprite;
	Shared* shared;
};