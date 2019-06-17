#include "C_Interface.h"




bool C_Interface::checkIfInteract(sf::Vector2f playerPosition)
{
	if (abs(playerPosition.x - position.x )< 72 * 2 || abs(playerPosition.y - position.y) < 72 * 2) { return true; }
	return false;
}

bool C_Interface::checkIfCollision(sf::Vector2f playerPosition)
{
	if (abs(playerPosition.x - position.x) < 72  || abs(playerPosition.y - position.y) < 72 ) { return true; }
	return false;
}

void C_Interface::SetObjPosition(sf::Vector2f _position)
{
	position = _position;
}

sf::Vector2f C_Interface::ObjGetPosition()
{
	return position;
}
