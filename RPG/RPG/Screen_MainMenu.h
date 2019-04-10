#pragma once
#include "Screen.h"
#include "Button.h"

class Screen_MainMenu : public Screen {
public:
	Screen_MainMenu(ScreenManager*);
	~Screen_MainMenu();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();
	void Position();

	void select(sf::Event::KeyEvent);
	void up(sf::Event::KeyEvent);
	void down(sf::Event::KeyEvent);
	void escape(sf::Event::KeyEvent);
private:
	Text title;
	Button buttons[3];
	int selected;
};