#include "ObjectManager.h"

ObjectManager::ObjectManager(Shared * _Shareed_context,Map* _map) :Shared_context(_Shareed_context) , Obj_counter(0),map(_map) {}


ObjectManager::~ObjectManager(){
	Purge();
}

int ObjectManager::AddObject(ObjectType _t){
	if (_t == ObjectType::doors) {
		objects.emplace(Obj_counter, doorsFactory.create(Shared_context, Obj_counter));
	}
	else if (_t == ObjectType::key) {
		objects.emplace(Obj_counter, keyFactory.create(Shared_context, Obj_counter));
		objects[Obj_counter]->SetObjectManager(this);
	}

	++Obj_counter;
	return Obj_counter - 1;
}

Object * ObjectManager::FindObj(unsigned int _Obj_ID){
	if (_Obj_ID < 0){
		throw;
	}
	auto itr = objects.find(_Obj_ID);
	if (itr == objects.end()) { return nullptr; }
	return itr->second;
}

void ObjectManager::RemoveObj(unsigned int _Obj_ID){
	objects_To_Remove.emplace_back(_Obj_ID);
}

void ObjectManager::Update(){
	for (auto &itr : objects){
		itr.second->setPosition(map->getTilePosition(itr.second->getCoordinates()));
		itr.second->Update();
	}

	ProcessRemovals();
}

void ObjectManager::Draw(){
	for (auto &itr : objects){
		itr.second->Draw();
	}
}

void ObjectManager::Purge(){
	for (auto &itr : objects) {
		delete itr.second;
	}
	objects.clear();
	Obj_counter = 0;
}

void ObjectManager::ProcessRemovals() {
	while (objects_To_Remove.begin() != objects_To_Remove.end()) {
		unsigned int id = objects_To_Remove.back();
		auto itr = objects.find(id);
		if (itr != objects.end()) {
			std::cout << "Discarding object: "
				<< id << std::endl;
			delete itr->second;
			objects.erase(itr);
		}
		objects_To_Remove.pop_back();
	}
}

bool ObjectManager::isColliding(sf::Vector2i _coord) {
	for (auto &itr : objects)
	{
		if (itr.second->IsColliding(_coord))
			return true;
	}
	return false;
}
void ObjectManager::Interact(sf::Vector2i _coord) {
	for (auto &itr : objects) {
		itr.second->isInteracting(_coord);
	}
}