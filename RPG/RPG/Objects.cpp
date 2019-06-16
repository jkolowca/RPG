#include "Objects.h"




Objects::Objects(Shared *_shared, std::string name, sf::Vector2f size,unsigned int _ID) : shared(_shared),ID(_ID)
{
	_Sprite.setTexture(*shared->textureManager.GetResource(name));
	_Sprite.setOrigin({ size.x / 2, 3 * TileSize / 4 });
	_Sprite.setScale(1, 1);
	_Sprite.setTextureRect(sf::IntRect(0 * size.x, 10 * size.y, size.x, size.y)); //Crop Sprite Sheet (Default Crop)

}

Objects::~Objects()
{
}
