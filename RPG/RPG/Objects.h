#pragma once
#include "Shared.h"
#include <SFML/Graphics.hpp>
class Objects
{
public:
	Objects(Shared*,std::string,sf::Vector2f size);
	~Objects();
	
	void Draw()
	{
		shared->renderWindow->draw(_Sprite);
	}

private:
	Shared* shared;
	sf::Sprite _Sprite;
};

