#include "View_Game.h"
#include "ViewManager.h"
#include "Level_0.h"
#include "Level_1.h"
#include <iostream>

View_Game::View_Game(ViewManager* _manager) : View(_manager), map(manager->GetShared()), entityMgr(manager->GetShared(), &map), ObjMgr(manager->GetShared(), &map) {
	levels.push_back(new Level_0(&map, &entityMgr, &ObjMgr));
	levels.push_back(new Level_1(&map, &entityMgr, &ObjMgr, manager));
	activeLevel = 0;
	load = new std::thread(&Level::Load, levels[activeLevel]);
}
View_Game::~View_Game() {}

void View_Game::Activate() {
	manager->GetShared()->eventManager->AddCallback("select", &View_Game::Interact, this);
	manager->GetShared()->eventManager->AddCallback("interact", &View_Game::Interact, this);
	manager->GetShared()->eventManager->AddCallback("escape", &View_Game::Escape, this);
	manager->GetShared()->eventManager->AddCallback("up", &View_Game::Up, this);
	manager->GetShared()->eventManager->AddCallback("down", &View_Game::Down, this);
	manager->GetShared()->eventManager->AddCallback("right", &View_Game::Right, this);
	manager->GetShared()->eventManager->AddCallback("left", &View_Game::Left, this);
	if(load->joinable())
	load->join();
	Position();
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
	map.Update();
	entityMgr.Update();
	ObjMgr.Update();
	if (activeLevel < levels.size()) {
		levels[activeLevel]->Update();
		if (levels[activeLevel]->isFinished()) {
			activeLevel++;
			if (activeLevel < levels.size()) {
				load = new std::thread(&Level::Load, levels[activeLevel]);
			}
			manager->SwitchTo(Story);
		}
	}
}

void View_Game::Draw() {
	map.Draw(0);
	map.Draw(1);
	levels[activeLevel]->Draw(0);
	ObjMgr.Draw();
	entityMgr.Draw();
	map.Draw(2);
	levels[activeLevel]->Draw(1);
}

void View_Game::Position() {
	map.MakeMove({ 0,0 });
	entityMgr.FindEntity(0)->setPosition( map.getTilePosition(map.getPlayerCoordinates()));
}

void View_Game::Interact(sf::Event::KeyEvent) {
	ObjMgr.Interact(map.getPlayerCoordinates());
}

void View_Game::Escape(sf::Event::KeyEvent) {
	manager->SwitchTo(MainMenu);
}
void View_Game::Up(sf::Event::KeyEvent) {
	Move({ 0,-1 }, animation_type::Up);
}
void View_Game::Down(sf::Event::KeyEvent) {
	Move({ 0,1 }, animation_type::Down);
}
void View_Game::Right(sf::Event::KeyEvent) {
	Move({ 1,0 }, animation_type::Right);
}
void View_Game::Left(sf::Event::KeyEvent) {
	Move({-1,0}, animation_type::Left);
}

void View_Game::Move(sf::Vector2i _shift, animation_type _t) {
	if (entityMgr.FindEntity(0)->isMoving()) return;
		sf::Vector2i coord = map.getPlayerCoordinates() + _shift;
		if (!entityMgr.isColliding(coord)&& !ObjMgr.isColliding(coord)) {
			if (map.MakeMove(_shift)) {
				levels[activeLevel]->OnMove();
				entityMgr.FindEntity(0)->Move(map.getPlayerShift(), _t);
				return;
			}
		}
		entityMgr.FindEntity(0)->Move({ 0,0 }, _t);
}