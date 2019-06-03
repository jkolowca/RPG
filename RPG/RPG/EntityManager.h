#pragma once
#include "EntityBase.h"
#include <functional>
#include <map>
#include <unordered_map>


using EntityContainer = std::unordered_map<unsigned int, EntityBase*>;
using EntityFactory = std::unordered_map<EntityType, std::function<EntityBase*(void)>>;
using NPCTypes = std::unordered_map<std::string, std::string>;

class EntityManager
{
	public:
	EntityManager(Shared*l_context, unsigned int l_maxEntites);
	~EntityManager();
	int Add(const EntityType & l_type, const std::string & l_name = "");
	EntityBase * Find(unsigned int l_id);
	EntityBase * Find(const std::string&name);

	void Remove(unsigned int l_id);
	void Update(float l_dT);
	void Draw();
	void Purge(); //usuwa wszystkie jednostki
	Shared*GetContext() { return m_context; };
	private:

	template<class T>
	void RegisterEntity(const EntityType& l_type)
	{
		m_entityFactory[l_type] = [this]()->EntityBase*
		{
			return new T(this);
		};
	}

	void ProcessRemovals();
	Shared*m_context;
	EntityContainer m_entities;
	EntityFactory m_entityFactory;
	NPCTypes m_npcTypes;
	unsigned int m_idCounter; //licznik jednostek
	unsigned int m_maxEntities; //maksymalna liczba jednostek
	

	std::vector<unsigned int>m_entitiesToRemove;
};

