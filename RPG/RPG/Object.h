#pragma once
#include "Shared.h"
#include "C_Colliding.h"
#include "C_Interactive.h"
#include <iostream>
#include <SFML/Graphics.hpp>
class ObjectManager;

class Object: public C_Colliding, public C_Interactive
{
public:
	Object(Shared*,std::string,sf::Vector2f size,unsigned int _ID);

	void setPosition(sf::Vector2f _position);
	virtual void Update();
	void Draw();

	sf::Vector2i getCoordinates();
	void setCoordinates(sf::Vector2i _coordinates);
	void setLocked(bool _t);
	sf::Sprite& getSprite();
	virtual void SetObjectManager(ObjectManager*) {};
protected:
	bool locked = false;
	sf::Sprite Sprite;
	unsigned int ID;
private:
	sf::Vector2i coordinates;
	Shared* shared;
};

