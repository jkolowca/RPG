#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Shared.h"

//stworzy� liste postaci
//dodawa� je po id do listy
//funkcja zwracaj�ca postaa�
//shared??




class Player
{
public:
	Player(Shared*,int id);
	~Player();

	void Update();

	void moveUp(float);
	void moveDown(float);
	void moveRight(float);
	void moveLeft(float);
	void setSpeed(float sp, sf::Time anTime);
	sf::Sprite getSprite() { return _Sprite; }
	void setID(int _id) { m_id = _id; }
	int getID() { return m_id; }
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
	int m_id; //dodanie id jednostki
	//animation
	sf::Time frameTime, animationTime;
	sf::Clock frameClock, animationClock;
	sf::Vector2f speed;
	bool moving;
};

