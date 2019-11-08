#pragma once
#include "Block.h"

class Platform : public Block
{
public:
	Platform();
	~Platform();

	void update(Input* input) override;
	void render(SDL_Renderer *renderer) override;

	void collide(const Entity* e, Point p) override;
};

