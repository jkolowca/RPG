#pragma once
#include <SFML\Graphics.hpp>

enum direction {
	Up,
	Down,
	Left,
	Right
};

class C_movable {
public:
	void Move();
private:
	virtual sf::Sprite getSprite() = 0;
	sf::Time moveTime;
	sf::Clock moveClock;
};