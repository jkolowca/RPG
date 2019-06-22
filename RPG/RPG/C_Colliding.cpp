#include "C_Colliding.h"

bool C_Colliding::IsColliding(sf::Vector2i _coord) {
	if (!colliding) return false;
	sf::Vector2i coord = getCoordinates();
	if (_coord.x >= coord.x && _coord.x <= coord.x  && _coord.y >= coord.y && _coord.y <= coord.y) return true;
	return false;
}