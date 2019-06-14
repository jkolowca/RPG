#pragma once
#include <SFML\Graphics.hpp>

class C_Moveable {
public:
	void Update();

	void Move(sf::Vector2f);
	bool isMoving();

	sf::Vector2f getPosition();

	void setPosition(sf::Vector2f _position);
	virtual sf::Sprite& getSprite() = 0;

protected:
	sf::Vector2f shift;
	sf::Vector2f speed;
	sf::Vector2f position;
	bool moving;
	sf::Time moveTime;
	sf::Clock moveClock;
};