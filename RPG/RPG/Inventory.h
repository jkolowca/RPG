#pragma once
#include "Objects.h"
using ObjectsContainer = std::unordered_map<unsigned int, Objects*>;

class Inventory
{
public:
	Inventory(Shared* _Shareed_context);
	~Inventory();
	int AddObjects(std::string, sf::Vector2f);
	Objects*FindObj(unsigned int _Obj_ID);
	void RemoveObj(unsigned int _Obj_ID);
	void Update(); //update wszystkich jednostek
	void Draw();
	void Purge();
	void ProcessRemovals();
	Shared*GetContext() { return Shared_context; }
private:
	Shared*Shared_context;
	ObjectsContainer objects;
	unsigned int Obj_counter;
	std::vector<unsigned int> objects_To_Remove;
};

