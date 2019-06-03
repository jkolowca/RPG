#include "EntityBase.h"
#include "EntityManager.h"


EntityBase::EntityBase(EntityManager * l_entityMgr):m_entityManager(l_entityMgr), m_name("BaseEntity"),
m_type(EntityType::Base),m_state(EntityState::Idle), m_id(0),
m_collidingOnX(false),m_collidingOnY(false)
{
}

EntityBase::~EntityBase()
{
}

void EntityBase::Move(float l_x, float l_y) {
	m_positionOld = m_position;
	m_position += sf::Vector2f(l_x, l_y);
	UpdateAABB();
}

void EntityBase::SetVelocity(float l_x, float l_y)
{
	m_velocity = sf::Vector2f(l_x, l_y);

}

void EntityBase::Update(float l_dT)
{

	sf::Vector2f deltaPos = m_velocity * l_dT;
	Move(deltaPos.x, deltaPos.y);
	m_collidingOnX = false;
	m_collidingOnY = false;
	
}

void EntityBase::SetPosition(const float & l_x, const float & l_y)
{
	m_position = sf::Vector2f(l_x, l_y);
	UpdateAABB();
}

void EntityBase::SetPosition(const sf::Vector2f & l_pos)
{
	m_position = l_pos;
	UpdateAABB();
}

void EntityBase::SetSize(const float & l_x, const float & l_y)
{
	m_size = sf::Vector2f(l_x, l_y);
	UpdateAABB();
}

void EntityBase::SetState(const EntityState & l_state)
{
	m_state = l_state;
}

void EntityBase::UpdateAABB()
{
	m_AABB = sf::FloatRect(m_position.x - (m_size.x / 2),
		m_position.y - (m_size.y), m_size.x, m_size.y);
}


