#pragma once
#include "View.h"
#include "Map.h"
#include "Player.h"

class View_Game : public View {
public:
	View_Game(ViewManager*);
	~View_Game();

	void Activate();
	void Deactivate();

	void Update();
	void Draw();
	void Position();

	void Interact(sf::Event::KeyEvent);
	void Escape(sf::Event::KeyEvent);
	void Up(sf::Event::KeyEvent);
	void Down(sf::Event::KeyEvent);
	void Right(sf::Event::KeyEvent);
	void Left(sf::Event::KeyEvent);

private:
	Map map;
	Player player;
};