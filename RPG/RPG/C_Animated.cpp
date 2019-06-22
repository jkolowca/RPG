#include "C_Animated.h"

C_Animated::C_Animated(sf::Vector2f _size) : size(_size) {}

void C_Animated::Update() {
	if (clock.getElapsedTime() < animation.duration) {
		if (frameClock.getElapsedTime() > animation.frameTime) {
			frame.x++;
			if (frame.x >= animation.frames) {
				frame = animation.firstFrame;
			}
			getSprite().setTextureRect(sf::IntRect(frame.x * size.x, frame.y * size.y, size.x, size.y));
			frameClock.restart();
		}
	}
}

void C_Animated::Animate(animation_type _type) {
	animation = animations[_type];
	frame = animation.firstFrame;
	frameClock.restart();
	clock.restart();
}