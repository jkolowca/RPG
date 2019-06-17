#pragma once
#include "View.h"
#include "Text.h"

class View_GameOver : public View {
public:
	View_GameOver(ViewManager*);
	~View_GameOver();

	void Activate();
	void Deactivate();

	void Update();
	void Draw();
	void Position();

	void Interact(sf::Event::KeyEvent);
	void Escape(sf::Event::KeyEvent);
private:
	Text text;
};