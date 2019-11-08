#pragma once
#include "Block.h"
class TypicalBlock final : public Block
{
public:
	TypicalBlock();
	~TypicalBlock();

	void render(SDL_Renderer *renderer) override;

};

