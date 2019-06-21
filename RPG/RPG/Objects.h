#pragma once
#include "Shared.h"
#include "C_Interface.h"
#include <iostream>
#include <SFML/Graphics.hpp>
class Objects:public C_Interface
{
public:
	Objects(Shared*,std::string,sf::Vector2f size,unsigned int _ID);
	~Objects();
	void Update()
	{
		_Sprite.setPosition(position);
	}
	void Draw()
	{
		shared->renderWindow->draw(_Sprite);
	}
	void setId(int _id) {
		ID = _id;
	}

	int getId() {
		return ID;
	}
	sf::Sprite& getSprite() { return _Sprite; }

	sf::Vector2i getCoordinates() {
		return coordinates;

	}
	void setCoordinates(sf::Vector2i _coordinates) {
		coordinates = _coordinates;
	}
private:
	sf::Vector2i coordinates;
	Shared* shared;
	sf::Sprite _Sprite;
	unsigned int ID;
};

