#include "Block.h"



Block::Block()
{
	m_rect.w = BLOCK_WIDTH;
	m_rect.h = BLOCK_HEIGHT;
}


Block::~Block()
{
}

void Block::setColor(SDL_Color & _color)
{
	color = _color;
}

void Block::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	color.r = r; color.g = g; color.b = b;
}

void Block::update(Input * input)
{
}

void Block::collide(const Entity* e, Point p)
{
	dead();
}
