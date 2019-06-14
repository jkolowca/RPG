#include "View_Game.h"
#include "ViewManager.h"
#include <iostream>

View_Game::View_Game(ViewManager* _manager) : View(_manager), map(manager->GetShared()), entityMgr(manager->GetShared())/*player(manager->GetShared(),0)*/ {
	map.Load(0);
	//player.setPosition(map.getPlayerPosition());
	entityMgr.Find(entityMgr.Add())->setPosition(map.getPlayerPosition());
}
View_Game::~View_Game() {}

void View_Game::Activate() {
	Position();
	manager->GetShared()->eventManager->AddCallback("select", &View_Game::Interact, this);
	manager->GetShared()->eventManager->AddCallback("interact", &View_Game::Interact, this);
	manager->GetShared()->eventManager->AddCallback("escape", &View_Game::Escape, this);
	manager->GetShared()->eventManager->AddCallback("up", &View_Game::Up, this);
	manager->GetShared()->eventManager->AddCallback("down", &View_Game::Down, this);
	manager->GetShared()->eventManager->AddCallback("right", &View_Game::Right, this);
	manager->GetShared()->eventManager->AddCallback("left", &View_Game::Left, this);
}

void View_Game::Deactivate() {
	manager->GetShared()->eventManager->RemoveCallback("select");
	manager->GetShared()->eventManager->RemoveCallback("interact");
	manager->GetShared()->eventManager->RemoveCallback("escape");
	manager->GetShared()->eventManager->RemoveCallback("up");
	manager->GetShared()->eventManager->RemoveCallback("down");
	manager->GetShared()->eventManager->RemoveCallback("right");
	manager->GetShared()->eventManager->RemoveCallback("left");
}

void View_Game::Update() {
	//player.Update();
	entityMgr.Update();
}

void View_Game::Draw() {
	map.Draw(0);
	map.Draw(1);
	//player.Draw();
	entityMgr.Draw();
	map.Draw(2);
}

void View_Game::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
}

void View_Game::Interact(sf::Event::KeyEvent) {
	manager->SwitchTo(MainMenu);
}

void View_Game::Escape(sf::Event::KeyEvent) {
	manager->SwitchTo(MainMenu);
}
void View_Game::Up(sf::Event::KeyEvent) {
	//if(!player.isMoving())
	if (!entityMgr.Find(0)->isMoving())
		if (map.MakeMove(0, -1))
			//player.move(map.getPlayerShift(), direction::Up);
			entityMgr.Find(0)->move(map.getPlayerShift(), direction::Up);
}
void View_Game::Down(sf::Event::KeyEvent) {
	//if (!player.isMoving())
	if (!entityMgr.Find(0)->isMoving())
		if (map.MakeMove(0, 1))
			//player.move(map.getPlayerShift(), direction::Down);
			entityMgr.Find(0)->move(map.getPlayerShift(), direction::Down);
}
void View_Game::Right(sf::Event::KeyEvent) {
	//if (!player.isMoving())
	if (!entityMgr.Find(0)->isMoving())
		if (map.MakeMove(1, 0))
			//player.move(map.getPlayerShift(), direction::Right);
			entityMgr.Find(0)->move(map.getPlayerShift(), direction::Right);
}
void View_Game::Left(sf::Event::KeyEvent) {
	//if (!player.isMoving())
	if (!entityMgr.Find(0)->isMoving())
		if (map.MakeMove(-1, 0))
			//player.move(map.getPlayerShift(), direction::Left);
			entityMgr.Find(0)->move(map.getPlayerShift(), direction::Left);
}