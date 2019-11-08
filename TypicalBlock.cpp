#include "TypicalBlock.h"



TypicalBlock::TypicalBlock()
{
	m_type = Block::TYPICAL;
	m_score = 1;
	color.r = 35;
	color.g = 131;
	color.b = 112;
	color.a = 255;
}


TypicalBlock::~TypicalBlock()
{
	std::cout << "~TypicalBlock()" << std::endl;
}

void TypicalBlock::render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &m_rect);
}
