#pragma once
#include "View.h"
#include "Button.h"

class View_MainMenu : public View {
public:
	View_MainMenu(ViewManager*);
	~View_MainMenu();

	void Activate();
	void Deactivate();

	void Update();
	void Draw();
	void Position();

	void select(sf::Event::KeyEvent);
	void up(sf::Event::KeyEvent);
	void down(sf::Event::KeyEvent);
	void escape(sf::Event::KeyEvent);
private:
	bool first = true;
	Text title;
	Button buttons[3];
	int selected;
};