#pragma once
#include "Level.h"

class Level_1 : public Level {
public:
	Level_1(Map* _map, EntityManager* _e_manager, ObjectManager* _o_manager, ViewManager* _manager ) : Level(_map, _e_manager, _o_manager), manager(_manager) {}
	void Load() {
		map->Load(1);
		e_manager->FindEntity(0)->setCoordinates({ 15, 7 });
		e_manager->FindEntity(0)->setPosition(map->getPlayerPosition());
		e_manager->AddEntity();
		e_manager->FindEntity(1)->setCoordinates({ 3, 3 });
		e_manager->FindEntity(1)->setPosition(map->getTilePosition({ 3,3 }));
	}
	void Update() {
		if (e_manager->FindEntity(0)->getCoordinates() == sf::Vector2i{ 5, 5 })
			finished = true;
	}
private:
	ViewManager* manager;
};