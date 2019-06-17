#pragma once
#include "Level.h"

class Level_1 : public Level {
public:
	Level_1(Map* _map, EntityManager* _e_manager, ObjectManager* _o_manager) : Level(_map, _e_manager, _o_manager) {}
	void Load() {
		map->Load(1);
		e_manager->FindEntity(e_manager->AddEntity())->setPosition(map->getPlayerPosition());
		e_manager->FindEntity(0)->setCoordinates({ 1, 3 });
	}
	void Update() {
		if (e_manager->FindEntity(0)->getCoordinates() == sf::Vector2i{ 5, 5 })
			finished = true;
	}
};