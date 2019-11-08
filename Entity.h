#pragma once
#include <SDL.h>
#include <iostream>

#include "AABB.h"

class Input;

class Entity
{
	friend class CollideGrid;

public:
	Entity();
	virtual ~Entity();

	void setPos(float x, float y);
	void setSize(float w, float h);

	void updateAABB();

	int getW() const noexcept { return m_rect.w; }
	int getH() const noexcept { return m_rect.h; }

	float getPosX() const noexcept { return m_posX; }
	float getPosY() const noexcept { return m_posY; }

	bool isDead() const noexcept { return m_is_dead; }
	virtual void dead() { m_is_dead = true; }

	virtual void update(Input* input) = 0;
	virtual void render(SDL_Renderer *renderer) = 0;
	virtual void collide(const Entity* e, Point p) {}

protected:

	float m_posX, m_posY;
	SDL_Rect m_rect;

	AABB m_aabb;
	
	bool m_is_dead;
};

