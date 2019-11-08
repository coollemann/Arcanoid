#include "CollideGrid.h"
#include <algorithm>
#include <Windows.h>
#include "Entity.h"

CollideGrid::CollideGrid()
{
	m_cellSize = m_rows = m_cols = 0;
}

CollideGrid::CollideGrid(int mapW, int mapH, int cellSize)
{

	m_cellSize = cellSize;
	m_rows = (mapH + cellSize - 1) / cellSize;
	m_cols = (mapW + cellSize - 1) / cellSize;

	m_grid.resize(m_cols);
	for (auto &grid : m_grid) {
		grid.resize(m_rows);
	}

}


CollideGrid::~CollideGrid()
{
	std::cout << "~CollideGrid" << std::endl;

}

void CollideGrid::resize(int mapW, int mapH, int cellSize)
{
	clear();
	m_cellSize = cellSize;
	m_rows = (mapH + cellSize - 1) / cellSize;
	m_cols = (mapW + cellSize - 1) / cellSize;

	m_grid.resize(m_cols);
	for (auto &grid : m_grid) {
		grid.resize(m_rows);
	}
	
}

void CollideGrid::update(Entity* e)
{
	std::list<Entity*> entityList;
	retrieve(e, entityList);
	Point p;
	for (auto &enemy : entityList) {
		if (enemy != e) {
			if (collideObjects(e, enemy, p)) {
				e->collide(enemy, p);
				enemy->collide(e, p);
				return;
			}
		}

	}
}



void CollideGrid::clear()
{
	for (auto& grid : m_grid) {
		for (auto &list : grid)
			list.clear();
		grid.clear();
	}
	m_grid.clear();
}

void CollideGrid::removeEntity(Entity* e)
{
	int topLeftX = (std::max)(0, int(e->m_posX / m_cellSize));
	int topLeftY = (std::max)(0, int(e->m_posY / m_cellSize));
	int bottomRightX = (std::min)(m_cols - 1, int((e->m_posX + e->m_rect.w - 1) / m_cellSize));
	int bottomRightY = (std::min)(m_rows - 1, int((e->m_posY + e->m_rect.h - 1) / m_cellSize));

	for (int x = topLeftX; x <= bottomRightX; x++)
	{
		for (int y = topLeftY; y <= bottomRightY; y++)
		{
			auto &list = m_grid[x][y];
			list.remove(e);
		}
	}
}

void CollideGrid::addEntity(Entity* e)
{
	int topLeftX = (std::max)(0, int(e->m_posX / m_cellSize));
	int topLeftY = (std::max)(0, int(e->m_posY / m_cellSize));
	int bottomRightX = (std::min)(m_cols-1, int((e->m_posX + e->m_rect.w - 1) / m_cellSize));
	int bottomRightY = (std::min)(m_rows-1, int((e->m_posY + e->m_rect.h - 1) / m_cellSize));

	for (int x = topLeftX; x <= bottomRightX; x++)
	{
		for (int y = topLeftY; y <= bottomRightY; y++)
		{
			m_grid[x][y].push_back(e);
		}
	}


}

void CollideGrid::getNearest(const Entity *e, std::list<Entity*> &list)
{
	std::list<Entity*> entityList;
	retrieve(e, entityList);
	if (!entityList.empty()) {
		for (auto &toCheck : entityList) {
			if (e != toCheck && !toCheck->isDead()) {
				float dist = sqrtf((toCheck->m_aabb.center.x - e->m_aabb.center.x) * (toCheck->m_aabb.center.x - e->m_aabb.center.x)
					+ (toCheck->m_aabb.center.y - e->m_aabb.center.y) * (toCheck->m_aabb.center.y - e->m_aabb.center.y));
				if (dist < e->getW() + 30.0f) {
					list.push_back(toCheck);
				}
			}
		}

	}
}

void CollideGrid::retrieve(const Entity * e, std::list<Entity*>& list)
{
	int topLeftX = (std::max)(0, int(e->m_posX / m_cellSize));
	int topLeftY = (std::max)(0, int(e->m_posY / m_cellSize));
	int bottomRightX = (std::min)(m_cols - 1, int((e->m_posX + e->m_rect.w - 1) / m_cellSize));
	int bottomRightY = (std::min)(m_rows - 1, int((e->m_posY + e->m_rect.h - 1) / m_cellSize));

	for (int x = topLeftX; x <= bottomRightX; x++)
	{
		for (int y = topLeftY; y <= bottomRightY; y++)
		{
			auto entityList = m_grid[x][y];
			if (!entityList.empty()) {

				for (auto &enemy : entityList) {
					if (enemy != e) {
						list.push_back(enemy);
					}
				}
			}
		}
	}
}

bool CollideGrid::collideObjects(const Entity* objA, const Entity* objB, Point &p)
{
	float rcx = fabs(objA->m_aabb.center.x - objB->m_aabb.center.x);
	float rx = (objA->m_aabb.r[0] + objB->m_aabb.r[0]);
	if (rcx > rx) return false;
	float rcy = fabs(objA->m_aabb.center.y - objB->m_aabb.center.y);
	float ry = (objA->m_aabb.r[1] + objB->m_aabb.r[1]);
	if (rcy > ry) return false;
	float x_axis = (rx - rcx);
	float y_axis = (ry - rcy);
	p.x = 0;
	p.y = 0;
	if (x_axis < y_axis)
	{
		p.x = x_axis;
		if (objA->m_aabb.center.x > objB->m_aabb.center.x)
		{
			p.x = -p.x;
		}
	}
	else {
		p.y = y_axis;
		if (objA->m_aabb.center.y > objB->m_aabb.center.y)
		{
			p.y = -p.y;
		}
	}

	return true;
}

