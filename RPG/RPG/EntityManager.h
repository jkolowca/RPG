#pragma once
#include "Player.h"


using EntityContainer = std::unordered_map<unsigned int, Player*>;


class EntityManager
{
public:
	EntityManager(Shared* _Shareed_context);
	~EntityManager();
	int AddEntity(); //zwraca ID dodanej jednostki
	Player *FindEntity(unsigned int _ID);
	void RemoveEntity(unsigned int _ID);

	void Update(); //update wszystkich jednostek
	void Draw();
	void Purge();
	void ProcessRemovals();
	Shared*GetContext() { return Shared_context; }
	private:
	Shared*Shared_context;
	EntityContainer entities;
	unsigned int ID_counter;
	std::vector<unsigned int> entities_To_Remove;

};

