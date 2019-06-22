#pragma once
#include "Object.h"
#include "C_Animated.h"

class Doors : public Object, public C_Animated {
public:
	Doors(Shared *_shared, unsigned int _ID);

	void Update();

	void Interact();

	sf::Sprite& getSprite();
};