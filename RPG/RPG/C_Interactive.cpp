#include "C_Interactive.h"

void C_Interactive::isInteracting(sf::Vector2i _coord) {
	sf::Vector2i coord = getCoordinates();
	if (_coord == coord) return;
	if (_coord.x == coord.x - 1 || _coord.x == coord.x + 1 || _coord.x == coord.x)
		if (_coord.y == coord.y - 1 || _coord.y == coord.y + 1 || _coord.y == coord.y)
			Interact();
}