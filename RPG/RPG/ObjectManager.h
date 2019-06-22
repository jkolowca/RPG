#pragma once
#include "Object.h"
#include "Doors_Factory.h"
#include"Map.h"

enum ObjectType {
	doors,
	trinket
};

using ObjectsContainer = std::unordered_map<unsigned int, Object*>;

class ObjectManager
{
public:
	ObjectManager(Shared* _Shareed_context,Map*);
	~ObjectManager();
	int AddObject(ObjectType);
	Object*FindObj(unsigned int _Obj_ID);
	void RemoveObj(unsigned int _Obj_ID);
	void Update(); //update wszystkich obiektów
	void Draw();
	void Purge();
	void ProcessRemovals();
	Shared*GetContext() { return Shared_context; }
	bool isColliding(sf::Vector2i _coord);
	void Interact(sf::Vector2i _coord);
private:
	DoorsFactory doorsFactory;
	Shared*Shared_context;
	ObjectsContainer objects;
	unsigned int Obj_counter;
	std::vector<unsigned int> objects_To_Remove;
	Map*map;
};

