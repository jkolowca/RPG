#include "EntityManager.h"


EntityManager::EntityManager(Shared* l_context,unsigned int l_maxEntities) :m_context(l_context),m_maxEntities(l_maxEntities), m_idCounter(0)
{
//	/*RegisterEntity<Player>(EntityType::Player);
//	RegisterEntity<NonPlayedCharacter>(EntityType::NonPlayedCharacter);*/
}





	EntityManager::~EntityManager()
{
	Purge();
}

int EntityManager::Add(const EntityType & l_type, const std::string & l_name)
{
	auto itr = m_entityFactory.find(l_type);	//szuka typu podanego w argumencie
	if (itr == m_entityFactory.end()) { return -1; } //brak podanego typu
	EntityBase*entity = itr->second();
	entity->m_id = m_idCounter; //ustawienie id
	if (l_name != "") { entity->m_name = l_name; }
	m_entities.emplace(m_idCounter, entity);
	if (l_type == EntityType::NonPlayedCharacter)
	{
		
			/*NPC*npc = (NPC*)entity;
			npc->Load(itr->second);*/
		
	}
		++m_idCounter;
		return m_idCounter - 1;
	

}

EntityBase * EntityManager::Find(unsigned int l_id)
{
	auto itr = m_entities.find(l_id);
	if (itr == m_entities.end()) { return nullptr; }
	return itr->second;
}

EntityBase * EntityManager::Find(const std::string & name)
{
	for (auto &itr : m_entities)
	{
		if (itr.second->m_name == name)
		{
			return itr.second;
		}
	}
	return nullptr;
}
void EntityManager::Remove(unsigned int l_id)
{
	m_entitiesToRemove.emplace_back(l_id);
}

void EntityManager::Update(float l_dT)
{

	for (auto & itr : m_entities)
	{
		itr.second->Update(l_dT);
}
	ProcessRemovals();
}

void EntityManager::Draw()
{
	sf::RenderWindow*wnd = m_context->window->GetRenderWindow();
	for (auto &itr : m_entities)
	{
		itr.second->Draw(wnd);
	}
}

void EntityManager::Purge()
{
	for (auto &itr : m_entities)
	{
		delete itr.second;
	}
	m_entities.clear();
	m_idCounter = 0;
}

void EntityManager::ProcessRemovals()
{
	while (m_entitiesToRemove.begin() != m_entitiesToRemove.end())
	{
		unsigned int id = m_entitiesToRemove.back();
		auto itr = m_entities.find(id);
		if (itr != m_entities.end())

		{
			std::cout << "Discarding entity: " << itr->second->m_id<<std::endl;
			delete itr->second;
			m_entities.erase(itr);
		}
		m_entitiesToRemove.pop_back();
	}
}



