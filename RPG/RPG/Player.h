#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Shared.h"
//class EntityManager;
class Player
{
	//friend class EntityManager;
public:
	Player(Shared*, int);
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
	void setId(int _id) {
		id = _id;
	}

	int getId() {
		return id;
	}
private:
	int id;
	sf::Vector2f m_position; //aktualna pozycja jednostki
	sf::Sprite _Sprite;
	Shared* shared;
	//EntityManager*entityMgr;
	sf::Texture texture;
	sf::Vector2f _Source;

	//animation
	sf::Time frameTime, animationTime;
	sf::Clock frameClock, animationClock;
	sf::Vector2f speed;
	bool moving;
};

