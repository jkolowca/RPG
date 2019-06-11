#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Shared.h"
class Player
{
public:
	Player(Shared*);
	~Player();

	void Update();

	void moveUp(float);
	void moveDown(float);
	void moveRight(float);
	void moveLeft(float);
	void setSpeed(float sp, sf::Time anTime);
	sf::Sprite getSprite() { return _Sprite; }
	void Draw()
	{
		shared->renderWindow->draw(_Sprite);
	}
	void SetPosition(sf::Vector2f _position);
	sf::Vector2f GetPosition() { return m_position; }
	bool isMoving() { return moving; }
private:
	
	sf::Vector2f m_position; //aktualna pozycja jednostki
	sf::Sprite _Sprite;
	Shared* shared;
	sf::Texture texture;
	sf::Vector2f _Source;

	//animation
	sf::Time frameTime, animationTime;
	sf::Clock frameClock, animationClock;
	sf::Vector2f speed;
	bool moving;
};

