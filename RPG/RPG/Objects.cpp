#include "Objects.h"




Objects::Objects(Shared *_shared, std::string name, sf::Vector2f size,unsigned int _ID) : shared(_shared),ID(_ID)
{
	position = sf::Vector2f(72 * 5, 72 * 3);
	_Sprite.setTexture(*shared->textureManager.GetResource(name));
	_Sprite.setPosition(position);
	_Sprite.setOrigin({ size.x / 2, 3 * TileSize / 4 });
	_Sprite.setScale(1, 1);
	_Sprite.setTextureRect(sf::IntRect(10 * size.x, 10000* size.y, size.x, size.y)); //Crop Sprite Sheet (Default Crop)

}
