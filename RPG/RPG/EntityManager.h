#pragma once
#include "Player.h"
#include "Objects.h"

using EntityContainer = std::unordered_map<unsigned int, Player*>;
using ObjectsContainer = std::unordered_map<unsigned int, Objects*>;

class EntityManager
{
public:
	EntityManager(Shared* _Shareed_context);
	~EntityManager();
	int AddEntity(); //zwraca ID dodanej jednostki
	int AddObjects(std::string, sf::Vector2f);
	Player *FindEntity(unsigned int _ID);
	Objects*FindObj(unsigned int _Obj_ID);
	void RemoveEntity(unsigned int _ID);
	void RemoveObj(unsigned int _Obj_ID);
	void Update(); //update wszystkich jednostek
	void Draw();
	void Purge();
	void ProcessRemovals();
	Shared*GetContext() { return Shared_context; }
	private:
	Shared*Shared_context;
	EntityContainer entities;
	ObjectsContainer objects;
	unsigned int ID_counter;
	unsigned int Obj_counter;
	std::vector<unsigned int> entities_To_Remove;
	std::vector<unsigned int> objects_To_Remove;
};

