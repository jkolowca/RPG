#include "Player.h"


Player::Player(Shared* _shared, int _id): shared(_shared), id(_id)
{
	_Sprite.setTexture(*shared->textureManager.GetResource("dep\\Player\\Player"+std::to_string(id)+".png"));
	_Sprite.setOrigin({ 64 / 2, 3 * 72 / 4 });
	_Sprite.setScale(1.3, 1.3);
	sf::Vector2i _Source(0, 10); //Default Sprite Sheet Crop
	_Sprite.setTextureRect(sf::IntRect(_Source.x *64, _Source.y *64, 64, 64)); //Crop Sprite Sheet (Default Crop)

	//PLAYER / ANIMATION SPEED
	frameTime = sf::milliseconds(70);
	moveTime = sf::milliseconds(300);
}


Player::~Player() {}

void Player::Update() {
	C_Moveable::Update();
	C_Animated::Update();
}

void Player::Move(sf::Vector2f _shift, animation_type _dir)
{
	C_Moveable::Move(_shift);
	C_Animated::Animate(_dir);
	frameClock.restart();
}
