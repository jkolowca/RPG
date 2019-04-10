#pragma once
#include "Screen.h"
#include "Sprite.h"

class Screen_Intro : public Screen {
public:
	Screen_Intro(ScreenManager*);
	~Screen_Intro();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();
	void Position();

	void Interact(sf::Event::KeyEvent);
private:
	Sprite sprite;
};