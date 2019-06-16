#pragma once
#include "Shared.h"
#include <SFML/Graphics.hpp>
class Objects
{
public:
	Objects(Shared*,std::string,sf::Vector2f size,unsigned int _ID);
	~Objects();
	
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
	void SetObjPosition(sf::Vector2f _position)
	{
		position = _position;
		getSprite().setPosition(_position);
	}
sf::Sprite getSprite()
{
	return _Sprite;
}
private:
	Shared* shared;
	sf::Sprite _Sprite;
	unsigned int ID;
	sf::Vector2f position;
};

