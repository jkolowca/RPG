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
	animationTime = sf::milliseconds(300);
}


Player::~Player() {}

void Player::Update() {
	if (animationClock.getElapsedTime() < animationTime) {
		_Sprite.setPosition(m_position.x + speed.x*animationClock.getElapsedTime().asSeconds(), m_position.y + speed.y*animationClock.getElapsedTime().asSeconds());
		if (frameClock.getElapsedTime() > frameTime) {
			_Source.x++;
			if (_Source.x >= 9) {
				_Source.x = 0;
			}
			_Sprite.setTextureRect(sf::IntRect(_Source.x * 64, _Source.y * 64, 64, 64));
			frameClock.restart();
		}
	}
	else {
		m_position = { m_position.x + speed.x*animationTime.asSeconds(), m_position.y + speed.y*animationTime.asSeconds() };
		_Sprite.setPosition(m_position.x, m_position.y);
		speed = { 0,0 };
		moving = false;
	}
}

void Player::moveUp(float _shift)
{
	_Source.y = 8; //Set '_Source.y' Equal To 'Up' (_Direction Enum)
	speed.y = _shift / animationTime.asSeconds();
	moving = true;
	frameClock.restart();
	animationClock.restart();
}
void Player::moveDown(float _shift)
{
	_Source.y = 10; //Set '_Source.y' Equal To 'Down'
	speed.y = _shift / animationTime.asSeconds();
	moving = true;
	frameClock.restart();
	animationClock.restart();
}

void Player::moveRight(float _shift)
{
	_Source.y = 11; //Set '_Source.y' Equal To 'Right'
	speed.x = _shift / animationTime.asSeconds();
	moving = true;
	frameClock.restart();
	animationClock.restart();
}

void Player::moveLeft(float _shift)
{
	_Source.y = 9; //Set '_Source.y' Equal To 'Left'
	speed.x = _shift / animationTime.asSeconds();
	moving = true;
	frameClock.restart();
	animationClock.restart();
}

void Player::SetPosition(sf::Vector2f _position)
{
	m_position = _position;
	_Sprite.setPosition(_position.x, _position.y);
}
void Player::setSpeed(float sp, sf::Time anTime)
{
	//_Speed = sp;
	//_AnimTime = anTime;
}

