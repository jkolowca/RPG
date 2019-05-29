#include "View_Game.h"
#include "Shared.h"
#include "ViewManager.h"

View_Game::View_Game(ViewManager* _manager) : View(_manager), map(manager->GetShared()) {}
View_Game::~View_Game() {}

void View_Game::Activate() {
	Position();
	map.Load(0);
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

void View_Game::Update(const sf::Time& l_time) {}

void View_Game::Draw() {
	map.Draw();
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
	map.playerposition.y--;
}
void View_Game::Down(sf::Event::KeyEvent) {
	map.playerposition.y++;
}
void View_Game::Right(sf::Event::KeyEvent) {
	map.playerposition.x++;
}
void View_Game::Left(sf::Event::KeyEvent) {
	map.playerposition.x--;
}