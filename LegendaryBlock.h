#pragma once
#include "Block.h"
class LegendaryBlock final : public Block
{
public:
	LegendaryBlock();
	~LegendaryBlock();

	void render(SDL_Renderer *renderer) override;
};

