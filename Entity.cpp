#include "Entity.h"



Entity::Entity()
{
	m_is_dead = false;
	updateAABB();
}


Entity::~Entity()
{
}

void Entity::setPos(float x, float y)
{
	m_posX = x;
	m_posY = y;
	m_rect.x = m_posX;
	m_rect.y = m_posY;
	updateAABB();
}

void Entity::setSize(float w, float h)
{
	m_rect.w = w;
	m_rect.h = h;

	updateAABB();

}

void Entity::updateAABB()
{
	m_aabb.center.x = m_posX + m_rect.w / 2.0f;
	m_aabb.center.y = m_posY + m_rect.h / 2.0f;
	m_aabb.r[0] = m_rect.w / 2.0f;
	m_aabb.r[1] = m_rect.h / 2.0f;
}
