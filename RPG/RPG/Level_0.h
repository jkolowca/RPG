

\\/#pragma once
#include "Level.h"

class Level_0 : public Level {
public:
	Level_0(Map* _map, EntityManager* _e_manager, ObjectManager* _o_manager) : Level(_map, _e_manager, _o_manager) {}
	void Load() {
		map->Load(0);
		e_manager->FindEntity(e_manager->AddEntity())->setPosition(map->getTilePosition(map->getPlayerCoordinates()));
		e_manager->FindEntity(0)->setCoordinates({ 1, 3 });
	}
	void Update() {
		if (e_manager->FindEntity(0)->getCoordinates() == sf::Vector2i{5, 5})
			finished = true;
	}
};