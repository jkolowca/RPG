#include "Player.h"

Player::Player(Shared* _shared, int _id): shared(_shared), id(_id)
{
	_Sprite.setTexture(*shared->textureManager.GetResource("dep\\Player\\Player"+std::to_string(id)+".png"));
	_Sprite.setOrigin({ PlayerSize / 2, 3 * TileSize / 4 });
	_Sprite.setScale(1.3, 1.3);
	_Sprite.setTextureRect(sf::IntRect(0 *PlayerSize, 10 *PlayerSize, PlayerSize, PlayerSize)); //Crop Sprite Sheet (Default Crop)

	//PLAYER / ANIMATION SPEED
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
