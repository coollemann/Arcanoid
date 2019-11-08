#pragma once
#include <iostream>

#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 20

#include "Entity.h"
class Block : public Entity
{
public:

	enum eBlockType {TYPICAL, RARE, LEGENDARY};

	Block();
	virtual ~Block();

	virtual int getScore() const { return m_score; }
	eBlockType getType() const { return m_type; }

	void setColor(SDL_Color& _color);
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	void update(Input* input) override;
	void render(SDL_Renderer *renderer) = 0;
	void collide(const Entity* e, Point p) override;

protected:

	eBlockType m_type;
	SDL_Color color;
	int m_score;
};

