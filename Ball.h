#pragma once
#include "Entity.h"
#include "Game.h"

#define BALL_RADIUS 10.0f
#define DEFAULT_BALL_SPEED 5.0f
#define LIFE_COUNT 4
#define BONUS_COUNT 4

class Ball : public Entity
{
public:
	Ball();
	Ball(float radius);
	~Ball();

	void setSpeed(float speed);
	void resetBonus() { m_bonusCount = 0; }
	void update(Input* input) override;
	void render(SDL_Renderer *renderer) override;
	void collide(const Entity* e, Point p) override;
	void setDirection(Point dir);

private:

	SDL_Color color;
	SDL_Color m_currentColor;
	SDL_Color m_bonusColor;
	int m_life;
	int m_bonusCount;
	float m_speed;
	Point m_direction;
	float m_radius;
};

