# include "C_Moveable.h"

void C_Moveable::Update() {
	if (moveClock.getElapsedTime() < moveTime) {
		getSprite().setPosition({ position.x + speed.x*moveClock.getElapsedTime().asSeconds(), position.y + speed.y*moveClock.getElapsedTime().asSeconds() });
	}
	else {
		setPosition({ position.x + shift.x, position.y + shift.y });

		if (shift.x > 0) coordinates.x++;
		else if (shift.x < 0) coordinates.x--;
		else if (shift.y > 0) coordinates.y++;
		else if (shift.y < 0)coordinates.y--;

		speed = shift = { 0,0 };
		moving = false;
	}
}

void C_Moveable::Move(sf::Vector2f _shift) {
	shift = _shift;
	speed = { shift.x / moveTime.asSeconds(), shift.y / moveTime.asSeconds() };
	moving = true;
	moveClock.restart();
}
bool C_Moveable::isMoving() {
	return moving;
}
sf::Vector2f C_Moveable::getPosition() {
	return position;
}

void C_Moveable::setPosition(sf::Vector2f _position) {
	position = _position;
	getSprite().setPosition(position);
}

sf::Vector2i C_Moveable::getCoordinates() {
	return coordinates;

}
void C_Moveable::setCoordinates(sf::Vector2i _coordinates) {
	coordinates = _coordinates;
}