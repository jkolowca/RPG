#pragma once
#include "View.h"
#include "Sprite.h"

class View_Intro : public View {
public:
	View_Intro(ViewManager*);
	~View_Intro();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();
	void Position();

	void Interact(sf::Event::KeyEvent);
	void Escape(sf::Event::KeyEvent);
private:
	sf::Sprite sprite;
};