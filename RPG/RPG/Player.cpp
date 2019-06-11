#include "Player.h"



Player::Player()
{
	texture.loadFromFile("dep\\Player\\Player.png");
	_Sprite.setTexture(texture);
	_Sprite.setPosition(600 - 64, 350 - 64); //Set Sprite Position
	_Sprite.setOrigin({ 64 / 2, 3 * 72 / 4 });
	_Sprite.setScale(1.3, 1.3);
	sf::Vector2i _Source(0, 10); //Default Sprite Sheet Crop
	_Sprite.setTextureRect(sf::IntRect(_Source.x *64, _Source.y *64, 64, 64)); //Crop Sprite Sheet (Default Crop)

	//PLAYER / ANIMATION SPEED
	_AnimTime = sf::milliseconds(80); //Animation Speed
	_Speed = 1.5f; //Player Speed
}


Player::~Player()
{
}


void Player::moveUp()
{
	_Source.y = 8; //Set '_Source.y' Equal To 'Up' (_Direction Enum)
	_Sprite.move(0, -_Speed); //Move Player Sprite

	if (_AnimClock.getElapsedTime() > _AnimTime)
	{
		_Sprite.setTextureRect(sf::IntRect(_Source.x * 64, _Source.y * 64, 64, 64)); //Crop Sprite Sheet

		//Animation
		_Source.x++;
		if (_Source.x * 64 >= 576) //last anim.
		{
			_Source.x = 0;
		}
		_AnimClock.restart();
	}
}
void Player::moveDown()
{
	_Source.y = 10; //Set '_Source.y' Equal To 'Down'
	_Sprite.move(0, _Speed); //Move Player Sprite

	if (_AnimClock.getElapsedTime() > _AnimTime)
	{
		_Sprite.setTextureRect(sf::IntRect(_Source.x * 64, _Source.y * 64, 64, 64)); //Crop Sprite Sheet

		//Animation
		_Source.x++;
		if (_Source.x * 64 >= 576)
		{
			_Source.x = 0;
		}
		_AnimClock.restart();

	}

}

void Player::moveRight()
{
	_Source.y = 11; //Set '_Source.y' Equal To 'Right'
	_Sprite.move(_Speed, 0); //Move Player Sprite

	if (_AnimClock.getElapsedTime() > _AnimTime)
	{
		_Sprite.setTextureRect(sf::IntRect(_Source.x * 64, _Source.y * 64, 64, 64)); //Crop Sprite Sheet

		//Animation
		_Source.x++;
		if (_Source.x * 64 >= 576)
		{
			_Source.x = 0;
		}
		_AnimClock.restart();
	}
}

void Player::moveLeft()
{
	_Source.y = 9; //Set '_Source.y' Equal To 'Left'
	_Sprite.move(-_Speed, 0); //Move Player Sprite

	if (_AnimClock.getElapsedTime() > _AnimTime)
	{
		_Sprite.setTextureRect(sf::IntRect(_Source.x * 64, _Source.y * 64, 64,64)); //Crop Sprite Sheet

		//Animation
		_Source.x++;
		if (_Source.x * 64 >= 576)
		{
			_Source.x = 0;
		}
		_AnimClock.restart();
	}
}
void Player::SetPosition(const float & l_x, const float & l_y)
{
	m_position = sf::Vector2f(l_x, l_y);
	_Sprite.setPosition(l_x, l_y);
}
void Player::setSpeed(float sp, sf::Time anTime)
{
	_Speed = sp;
	_AnimTime = anTime;
}

