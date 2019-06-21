#include "Objects.h"




Objects::Objects(Shared *_shared, std::string name, sf::Vector2f size,unsigned int _ID) : shared(_shared),ID(_ID)
{
	_Sprite.setTexture(*shared->textureManager.GetResource(name));
	_Sprite.setOrigin({ size.x / 2, size.y/2 });
	_Sprite.setScale(1, 1);

}
