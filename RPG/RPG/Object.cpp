#include "Object.h"




Object::Object(Shared *_shared, std::string name, sf::Vector2f size,unsigned int _ID) : shared(_shared),ID(_ID)
{
	Sprite.setTexture(*shared->textureManager.GetResource(name));
	Sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	Sprite.setOrigin({ size.x / 2, size.y/2 });
	Sprite.setScale(1, 1);

}

void Object::setPosition(sf::Vector2f _position) {
	Sprite.setPosition(_position);
}
void Object::Update() {}
void Object::Draw()
{
	shared->renderWindow->draw(Sprite);
}

sf::Vector2i Object::getCoordinates() {
	return coordinates;

}
void Object::setCoordinates(sf::Vector2i _coordinates) {
	coordinates = _coordinates;
}
void Object::setLocked(bool _t) {
	locked = _t;
}