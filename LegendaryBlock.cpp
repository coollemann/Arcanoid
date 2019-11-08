#include "LegendaryBlock.h"



LegendaryBlock::LegendaryBlock()
{
	m_type = Block::LEGENDARY;
	m_score = 5;
	color.r = 56;
	color.g = 167;
	color.b = 45;
	color.a = 255;
}


LegendaryBlock::~LegendaryBlock()
{
	std::cout << "~LegendaryBlock()" << std::endl;
}

void LegendaryBlock::render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &m_rect);
}
