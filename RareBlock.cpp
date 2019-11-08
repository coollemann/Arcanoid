#include "RareBlock.h"

#include "Game.h"

RareBlock::RareBlock()
{
	m_type = Block::RARE;
	m_score = 3;
	color.r = 43;
	color.g = 86;
	color.b = 133;
	color.a = 255;
}


RareBlock::~RareBlock()
{
	std::cout << "~RareBlock()" << std::endl;
}

void RareBlock::render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &m_rect);
}

void RareBlock::collide(const Entity *e, Point p)
{
	dead();
	std::list<Entity*> list;
	Game::Instance().getLevel()->getGrid()->getNearest(this, list);
	if (!list.empty()) {
		for (auto &item : list) {
			if (!item->isDead())
				item->dead();
		}
	}
}

void RareBlock::dead()
{
	Block::dead();
}
