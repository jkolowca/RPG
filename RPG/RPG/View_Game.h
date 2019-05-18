#pragma once
#include "View.h"

class View_Game : public View {
public:
	View_Game(ViewManager*);
	~View_Game();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();
	void Position();

	void Interact(sf::Event::KeyEvent);
	void Escape(sf::Event::KeyEvent);
	void Up(sf::Event::KeyEvent);
	void Down(sf::Event::KeyEvent);
	void Right(sf::Event::KeyEvent);
	void Left(sf::Event::KeyEvent);

private:
};