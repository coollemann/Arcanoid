#pragma once
#include "Block.h"
class RareBlock final : public Block
{
public:
	RareBlock();
	~RareBlock();

	void render(SDL_Renderer *renderer) override;
	void collide(const Entity* e, Point p) override;
	void dead() override;
};

