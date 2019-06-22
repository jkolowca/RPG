#include "Object_Doors.h"

Doors::Doors(Shared *_shared, unsigned int _ID) : Object(_shared, "dep\\ts\\doors.png", { TileSize,TileSize }, _ID), C_Animated({ TileSize,TileSize }) {
	animations[Open] = { {0,0},3,sf::milliseconds(210), sf::milliseconds(70) };
	animations[Close] = { {0,1},3,sf::milliseconds(210), sf::milliseconds(70) };
}

void Doors::Update() {
	C_Animated::Update();
}

void Doors::Interact() {
	if (locked) return;
	if (colliding)
		Animate(Open);
	else Animate(Close);
	colliding = !colliding;
}

sf::Sprite& Doors::getSprite() { return Sprite; }