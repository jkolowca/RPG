#pragma once
#include "Level.h"
#include "Highlight.h"

class Level_1 : public Level {
public:
	Level_1(Map* _map, EntityManager* _e_manager, ObjectManager* _o_manager, ViewManager* _manager) : Level(_map, _e_manager, _o_manager), manager(_manager) {}
	void Load() {
		map->Load(1);
		e_manager->FindEntity(0)->setCoordinates(map->getPlayerCoordinates());
		e_manager->AddEntity();
		e_manager->FindEntity(1)->setCoordinates({ 5, 3 });
		e_manager->FindEntity(1)->SetText("What do you want? Go away...");
		o_manager->FindObj(o_manager->AddObject(doors))->setCoordinates({ 6,6 });
		o_manager->FindObj(o_manager->AddObject(key))->setCoordinates({ 3,8 });
		o_manager->FindObj(o_manager->AddObject(doors))->setCoordinates({ 11,6 });
		o_manager->FindObj(o_manager->AddObject(doors))->setCoordinates({ 18,6 });
		o_manager->FindObj(o_manager->AddObject(doors))->setCoordinates({ 23,6 });
		o_manager->FindObj(1)->setLocked(true);
		o_manager->FindObj(2)->setLocked(true);
	}
	void Draw(int i) {
		if(i==0)
		for (unsigned int i = 0; i < 4; i++) h[i].Draw(manager->GetShared()->renderWindow);
	}
	void Update() {
		h[0].SetPosition(map->getTilePosition({ 2,3 }));
		h[1].SetPosition(map->getTilePosition({ 11,3 }));
		h[2].SetPosition(map->getTilePosition({ 18,3 }));
		h[3].SetPosition(map->getTilePosition({ 27,3 }));
	}
	void OnMove() {
		for (unsigned int i = 0; i < 4; i++)
			h[i].Clicked(map->getTilePosition(map->getPlayerCoordinates()));
		if (h[0].IsSelected() && h[3].IsSelected()) {
			o_manager->FindObj(2)->setLocked(false);
		}
		if (map->getPlayerCoordinates() == sf::Vector2i{ 18,3 }) {
			o_manager->FindObj(1)->setLocked(false);
			o_manager->FindObj(2)->Interact();
			o_manager->FindObj(2)->setLocked(true);
			h[0].Switch();
		}
		if (h[0].IsSelected() && h[1].IsSelected() && h[2].IsSelected() && h[3].IsSelected()) {
			finished = true;
		}
	}
private:
	ViewManager* manager;
	Highlight h[4];
};