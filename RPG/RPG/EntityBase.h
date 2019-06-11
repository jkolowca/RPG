#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"


enum class EntityType{Base,NonPlayedCharacter,Player};
enum class EntityState {Idle,Walking};

class EntityManager;

class EntityBase
{
	friend class EntityManager;
public:
	EntityBase(EntityManager*l_entityMgr);
	virtual ~EntityBase();

	void Move(float l_x, float l_y);
	void SetVelocity(float l_x,float l_y); //prêdkoœæ
	
	virtual void Update(float l_dT); //delta time
	virtual void Draw(sf::RenderWindow*l_wind) = 0;

	void SetPosition(const float& l_x, const float& l_y);
	void SetPosition(const sf::Vector2f& l_pos);
	void SetSize(const float& l_x, const float& l_y);
	void SetState(const EntityState& l_state);
	
	
protected:
	//metody do wykrywania i rozwi¹zywania kolizji
	/*TO DO*/
	void UpdateAABB(); //axis-aligned bounding box do wykrywania kolizji
	//dane
	std::string m_name;
	EntityType m_type;
	unsigned int m_id; 
	sf::Vector2f m_position; //aktualna pozycja jednostki
	sf::Vector2f m_positionOld; //pozycja przed wykonaniem ruchu
	sf::Vector2f m_velocity; //aktualna prêdkoœæ
	sf::Vector2f m_size; //size of the collision box
	sf::FloatRect m_AABB; //bb for collisions
	EntityState m_state; //aktualny stan
	bool m_collidingOnX; //koliduje z X
	bool m_collidingOnY; //koliduje z Y
	EntityManager* m_entityManager;
	
};

