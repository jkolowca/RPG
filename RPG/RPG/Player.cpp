#include "Player.h"

Player::Player(Shared* _shared, int _id): shared(_shared), id(_id), C_Animated({PlayerSize, PlayerSize})
{
	_Sprite.setTexture(*shared->textureManager.GetResource("dep\\Player\\Player"+std::to_string(id)+".png"));
	_Sprite.setOrigin({ PlayerSize / 2, 3 * TileSize / 4 });
	_Sprite.setScale((float)1.3,(float) 1.3);
	_Sprite.setTextureRect(sf::IntRect(0 *PlayerSize, 10 *PlayerSize, PlayerSize, PlayerSize)); //Crop Sprite Sheet (Default Crop)

	//PLAYER / ANIMATION SPEED

	animations[Up] = { {0,8},9,sf::milliseconds(300), sf::milliseconds(70) };
	animations[Down] = { {0,10},9,sf::milliseconds(300), sf::milliseconds(70) };
	animations[Left] = { {0,9},9,sf::milliseconds(300), sf::milliseconds(70) };
	animations[Right] = { {0,11},9,sf::milliseconds(300), sf::milliseconds(70) };
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
}
