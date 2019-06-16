#include "EntityManager.h"



EntityManager::EntityManager(Shared * _Shareed_context):Shared_context(_Shareed_context),ID_counter(0),Obj_counter(0)
{
}

EntityManager::~EntityManager()
{
	Purge();
}

int EntityManager::AddEntity()
{
	Player* player = new Player(Shared_context,ID_counter);
	entities.emplace(ID_counter, player); //dodanie do kontenera
	++ID_counter;
	return ID_counter - 1;

}

int EntityManager::AddObjects(std::string nazwa,sf::Vector2f size)
{
	Objects* object = new Objects(Shared_context,nazwa,size,Obj_counter);
	objects.emplace(ID_counter, object); //dodanie do kontenera
	++Obj_counter;
	return Obj_counter - 1;
}

Player * EntityManager::FindEntity(unsigned int _ID)
{
	auto itr = entities.find(_ID);
	if (itr == entities.end()) { return nullptr; }
	return itr->second;
}

Objects * EntityManager::FindObj(unsigned int _Obj_ID)
{
	auto itr = objects.find(_Obj_ID);
	if (itr == objects.end()) { return nullptr; }
	return itr->second;
}

void EntityManager::RemoveEntity(unsigned int _ID) //dodanie do kontenera
{
	entities_To_Remove.emplace_back(_ID);
}

void EntityManager::RemoveObj(unsigned int _Obj_ID) //dodanie do kontenera
{
	objects_To_Remove.emplace_back(_Obj_ID);
}
void EntityManager::Update() 
{
	for (auto &itr : entities)
	{
		itr.second->Update();
	}
	
	ProcessRemovals();
}

void EntityManager::Draw()
{
	for (auto &itr : entities)
	{
		itr.second->Draw();
	}
	for (auto &itr : objects)
	{
		itr.second->Draw();
	}
}

void EntityManager::Purge()
{
	for (auto &itr : entities) {
		delete itr.second;
	}
	for (auto &itr : objects) {
		delete itr.second;
	}
	entities.clear();
	objects.clear();
	ID_counter = 0;
	Obj_counter = 0;
}

void EntityManager::ProcessRemovals() //usuwanie jednostek i œci¹gniêcie ich z procesu do usuniêcia
{
	while (entities_To_Remove.begin() != entities_To_Remove.end())
	{
		unsigned int id =entities_To_Remove.back();
		auto itr = entities.find(id);
		if (itr != entities.end())
		{
			std::cout << "Discarding entity: "
				<< itr->second->getId() << std::endl;
			delete itr->second;
			entities.erase(itr);
		}
		entities_To_Remove.pop_back();
	}

	while (objects_To_Remove.begin() != objects_To_Remove.end())
	{
		unsigned int id = objects_To_Remove.back();
		auto itr = objects.find(id);
		if (itr != objects.end())
		{
			std::cout << "Discarding entity: "
				<< itr->second->getId() << std::endl;
			delete itr->second;
			objects.erase(itr);
		}
		objects_To_Remove.pop_back();
	}
}


