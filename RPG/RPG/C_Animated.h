#pragma once
#include <SFML/Graphics.hpp>
#include <map>

enum animation_type {
	Up = 0,
	Down,
	Left,
	Right,
	Open,
	Close
};

struct Animation {
	sf::Vector2i firstFrame;
	int frames;
	sf::Time duration, frameTime;
};

class C_Animated {
public:
	C_Animated() {
		animations[Up] = { {0,8},9,sf::milliseconds(300), sf::milliseconds(70) };
		animations[Down] = { {0,10},9,sf::milliseconds(300), sf::milliseconds(70) };
		animations[Left] = { {0,9},9,sf::milliseconds(300), sf::milliseconds(70) };
		animations[Right] = { {0,11},9,sf::milliseconds(300), sf::milliseconds(70) };
	}

	void Update() {
		if (clock.getElapsedTime() < animation.duration) {
			if (frameClock.getElapsedTime() > animation.frameTime) {
				frame.x++;
				if (frame.x >= animation.frames) {
					frame=animation.firstFrame;
				}
				getSprite().setTextureRect(sf::IntRect(frame.x * PlayerSize, frame.y * PlayerSize, PlayerSize, PlayerSize));
				frameClock.restart();
			}
		}
	}

	void Animate(animation_type _type) {
		animation = animations[_type];
		frame = animation.firstFrame;
		frameClock.restart();
		clock.restart();
	}

	virtual sf::Sprite& getSprite() = 0;
protected:
	std::map<animation_type, Animation> animations;
	Animation animation;
	sf::Vector2i frame;
	sf::Clock clock, frameClock;
};