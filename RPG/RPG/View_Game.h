#pragma once
#include "View.h"
#include "Map.h"
#include "Player.h"
#include "EntityManager.h"
#include "ObjectManager.h"
#include "Level.h"

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
	int activeLevel = 0;
	std::vector<Level*> levels;
	Map map;
	EntityManager entityMgr;
	ObjectManager ObjMgr;
};