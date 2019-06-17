#pragma once
#include "Level.h"
#include "Highlight.h"

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
		h[0].SetPosition(map->getTilePosition({ 2,3 }));
		h[1].SetPosition(map->getTilePosition({ 11,3 }));
		h[2].SetPosition(map->getTilePosition({ 18,3 }));
		h[3].SetPosition(map->getTilePosition({ 27,3 }));
		if (e_manager->FindEntity(0)->getCoordinates() == sf::Vector2i{ 2, 3 })
			h[0].Select();
		else if (e_manager->FindEntity(0)->getCoordinates() == sf::Vector2i{ 11, 3 })
			h[1].Select();
		else if (e_manager->FindEntity(0)->getCoordinates() == sf::Vector2i{ 18, 3 })
			h[2].Select();
		else if (e_manager->FindEntity(0)->getCoordinates() == sf::Vector2i{ 27, 3 })
			h[3].Select();

		if (h[0].IsSelected() && h[1].IsSelected() && h[2].IsSelected() && h[3].IsSelected()) {
			finished = true;
		}
	}
private:
	ViewManager* manager;
	Highlight h[4];
};