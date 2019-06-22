#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Shared.h"
#include "C_Moveable.h"
#include "C_Animated.h"
#include "C_Colliding.h"
#include "C_Interactive.h"
#include "Text.h"

class Player : public C_Moveable, public C_Animated, public C_Colliding, public C_Interactive
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
	void Interact();
	void SetText(std::string);

	sf::Vector2i getCoordinates();
private:
	bool talking = false;
	sf::Clock speakClock;
	sf::Time speakTime;
	Text text;
	int id;
	sf::Sprite _Sprite;
	Shared* shared;
};