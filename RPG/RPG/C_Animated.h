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
	C_Animated(sf::Vector2f _size) : size(_size) {}
	void Update() {
		if (clock.getElapsedTime() < animation.duration) {
			if (frameClock.getElapsedTime() > animation.frameTime) {
				frame.x++;
				if (frame.x >= animation.frames) {
					frame=animation.firstFrame;
				}
				getSprite().setTextureRect(sf::IntRect(frame.x * size.x, frame.y * size.y, size.x, size.y));
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
private:
	Animation animation;
	sf::Vector2i frame;
	sf::Clock clock, frameClock;
	sf::Vector2f size;
};