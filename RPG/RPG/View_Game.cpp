#include "View_Game.h"
#include "ViewManager.h"
#include <iostream>

View_Game::View_Game(ViewManager* _manager) : View(_manager), map(manager->GetShared()), player(manager->GetShared()) {
	map.Load(0);
	player.SetPosition(map.getPlayerPosition());
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
	player.Update();
}

void View_Game::Draw() {
	map.Draw(0);
	map.Draw(1);
	player.Draw();
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
	if(!player.isMoving())
	if (map.MakeMove(0, -1)) 
		player.moveUp(map.getPlayerShift().y);
}
void View_Game::Down(sf::Event::KeyEvent) {
	if (!player.isMoving())
	if(map.MakeMove(0, 1)) 
		player.moveDown(map.getPlayerShift().y);
}
void View_Game::Right(sf::Event::KeyEvent) {
	if (!player.isMoving())
	if(map.MakeMove(1, 0)) 
		player.moveRight(map.getPlayerShift().x);
}
void View_Game::Left(sf::Event::KeyEvent) {
	if (!player.isMoving())
	if(map.MakeMove(-1, 0)) 
		player.moveLeft(map.getPlayerShift().x);
}