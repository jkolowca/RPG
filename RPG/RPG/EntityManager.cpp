#include "EntityManager.h"



EntityManager::EntityManager(Shared * _Shareed_context, Map* _map)
	:Shared_context(_Shareed_context),ID_counter(0), map(_map)
{}


EntityManager::~EntityManager(){
	Purge();
}

int EntityManager::AddEntity(){
	Player* player = new Player(Shared_context,ID_counter);
	entities.emplace(ID_counter, player); //dodanie do kontenera
	++ID_counter;
	return ID_counter - 1;

}


Player * EntityManager::FindEntity(unsigned int _ID){
	auto itr = entities.find(_ID);
	if (itr == entities.end()) { return nullptr; }
	return itr->second;
}


void EntityManager::RemoveEntity(unsigned int _ID){ //dodanie do kontenera
	entities_To_Remove.emplace_back(_ID);
}

void EntityManager::Update() {
	for (auto &itr : entities){
		if (itr.second->getId() != 0)
		itr.second->setPosition(map->getTilePosition(itr.second->getCoordinates()));

		itr.second->Update();
	}
	
	ProcessRemovals();
}

void EntityManager::Draw(){
	for (auto &itr : entities){
		itr.second->Draw();
	}
}

void EntityManager::Purge(){
	for (auto &itr : entities) {
		delete itr.second;
	}
	entities.clear();
	ID_counter = 0;

}

void EntityManager::ProcessRemovals(){ //usuwanie jednostek i œci¹gniêcie ich z procesu do usuniêcia
	while (entities_To_Remove.begin() != entities_To_Remove.end()){
		unsigned int id =entities_To_Remove.back();
		auto itr = entities.find(id);
		if (itr != entities.end()){
			std::cout << "Discarding entity: "
				<< itr->second->getId() << std::endl;
			delete itr->second;
			entities.erase(itr);
		}
		entities_To_Remove.pop_back();
	}
}

bool EntityManager::isColliding(sf::Vector2i _coord) {
	for (auto &itr : entities)
	{
		if (itr.second->getId() == 0)continue;
		if (itr.second->IsColliding(_coord))
			return true;
	}
	return false;
}

void EntityManager::Interact(sf::Vector2i _coord) {
	for (auto &itr : entities) {
		itr.second->isInteracting(_coord);
	}
}