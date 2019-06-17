#pragma once
#include  "Map.h"
#include "EntityManager.h"
#include "ObjectManager.h"

class Level {
public:
	Level(Map* _map, EntityManager* _e_manager, ObjectManager* _o_manager) 
		: map(_map), e_manager(_e_manager), o_manager(_o_manager) {}

	virtual void Load() = 0;

	bool isFinished() {
		return finished;
	}

	virtual void Update() =0;
protected:
	bool finished = false;
	Map* map;
	EntityManager* e_manager;
	ObjectManager* o_manager;
};