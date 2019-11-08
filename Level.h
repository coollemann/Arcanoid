#pragma once
#include <memory>

#include "Input.h"
#include "CollideGrid.h"
#include <vector>

#define BLOCKS_IN_LINE 16
#define BLOCK_LINE_AMOUNT 15

#define BALL_SPEED 8.0f

class Block;
class Platform;
class Ball;

class Level
{
public:
	Level();
	~Level();

	void init();
	void startGame(float ball_speed);

	void gameOver();
	void setOnStart();

	CollideGrid* getGrid() const { return grid.get(); }

	void update(Input* input);
	void render(SDL_Renderer *renderer);
	void clear();

private:

	std::shared_ptr<Platform> m_platform;
	std::shared_ptr<Ball> m_ball;
	std::vector<std::shared_ptr<Entity>> m_blocks;
	std::unique_ptr<CollideGrid> grid;

	float m_currentBallSpeed;
	bool m_start;
	bool m_isGameOver;
};

