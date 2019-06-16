#include "ObjectManager.h"



ObjectManager::ObjectManager(Shared * _Shareed_context,Map* _map) :Shared_context(_Shareed_context) , Obj_counter(0),map(_map)
{

}


ObjectManager::~ObjectManager()
{
	Purge();
}

int ObjectManager::AddObjects(std::string nazwa, sf::Vector2f size)
{
	Objects* object = new Objects(Shared_context, nazwa, size, Obj_counter);
	objects.emplace(Obj_counter, object); //dodanie do kontenera
	++Obj_counter;
	return Obj_counter - 1;
}

Objects * ObjectManager::FindObj(unsigned int _Obj_ID)
{
	auto itr = objects.find(_Obj_ID);
	if (itr == objects.end()) { return nullptr; }
	return itr->second;
}

void ObjectManager::RemoveObj(unsigned int _Obj_ID)
{
	objects_To_Remove.emplace_back(_Obj_ID);
}

void ObjectManager::Update()
{
	for (auto &itr : objects)
	{
		itr.second->SetObjPosition(map->getTilePosition(itr.second->getCoordinates()));
		itr.second->Update();
	}

	ProcessRemovals();

}

void ObjectManager::Draw()
{
	for (auto &itr : objects)
	{
		itr.second->Draw();
	}
}

void ObjectManager::Purge()
{
	for (auto &itr : objects) {
		delete itr.second;
	}
	objects.clear();
	Obj_counter = 0;
}

void ObjectManager::ProcessRemovals()
{
	while (objects_To_Remove.begin() != objects_To_Remove.end())
	{
		unsigned int id = objects_To_Remove.back();
		auto itr = objects.find(id);
		if (itr != objects.end())
		{
			std::cout << "Discarding object: "
				<< itr->second->getId() << std::endl;
			delete itr->second;
			objects.erase(itr);
		}
		objects_To_Remove.pop_back();
	}
}
