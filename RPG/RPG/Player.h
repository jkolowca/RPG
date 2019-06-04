#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Shared.h"
class Player
{
public:
	Player();
	~Player();
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void setSpeed(float sp, sf::Time anTime);
	
	void Draw(sf::RenderWindow &window)
	{
		window.draw(_Sprite);
	}
	void SetPosition(const float& l_x, const float& l_y);

private:
	
	sf::Vector2f m_position; //aktualna pozycja jednostki
	sf::Sprite _Sprite;
	Shared*shared;
	
	sf::Texture texture;
	sf::Vector2f _Source;
	//animation
	float _Speed;
	sf::Clock _AnimClock;
	sf::Time _AnimTime;

};

