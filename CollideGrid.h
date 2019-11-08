#pragma once
#include <vector>
#include <list>
#include <memory>
#include "AABB.h"

class Entity;

class CollideGrid
{
public:
	CollideGrid();
	CollideGrid(int mapW, int mapH, int cellSize);
	~CollideGrid();

	void resize(int mapW, int mapH, int cellSize);

	void update(Entity* e);
	void clear();

	void removeEntity(Entity* e);
	void addEntity(Entity* e);

	void getNearest(const Entity* e, std::list<Entity*> &list);
	void retrieve(const Entity *e, std::list<Entity*> &list);

	int getCellSize() const { return m_cellSize; }
	void setCellSize(int _size) { m_cellSize = _size; }


private:

	bool collideObjects(const Entity *objA, const Entity *objB, Point &p);

private:

	int m_rows, m_cols;
	int m_cellSize;

	std::vector< std::vector< std::list< Entity* > >> m_grid;
};

