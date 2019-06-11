#pragma once
#include "EntityManager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
class Character:public EntityBase
{
	friend class EntityManager;
public:
	Character(EntityManager* l_entityMgr);
	virtual ~Character();
	void Load(const std::string& l_path);
	virtual void Update(float l_dT);
	void Draw(sf::RenderWindow* l_wind);
protected:
	//void Animate();
	sf::Sprite m_spriteSheet;
	

};


