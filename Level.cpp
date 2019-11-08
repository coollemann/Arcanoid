#include "Level.h"

#include <SDL.h>
#include "Platform.h"
#include "Ball.h"

#include "LegendaryBlock.h"
#include "RareBlock.h"
#include "TypicalBlock.h"


Level::Level()
{
	m_start = false;
	m_isGameOver = false;
	m_currentBallSpeed = BALL_SPEED;
}


Level::~Level()
{
	std::cout << "~Level()" << std::endl;
}

void Level::init()
{
	m_platform = std::make_unique<Platform>();
	m_ball = std::make_unique<Ball>(10.0f);
	grid = std::make_unique<CollideGrid>();

	startGame(m_currentBallSpeed);
}

void Level::startGame(float ball_speed)
{
	auto rnd = Game::Instance().getRandom(2);
	Point dir;
	dir.x = (rnd == 0) ? -1.0f : rnd; dir.y = 1.0f;
	m_ball->setDirection(dir);
	m_ball->setSpeed(ball_speed);
	m_ball->resetBonus();

	grid->resize(Game::Instance().getScreenWidth(), Game::Instance().getScreenHeight(), m_ball->getH() * 2);

	float startPosX = 0, startPosY = 5;
	startPosX = (Game::Instance().getScreenWidth() - ( BLOCK_WIDTH * BLOCKS_IN_LINE + BLOCKS_IN_LINE)) / 2.0f;

	for (int i = 0; i < BLOCKS_IN_LINE; i++) {
		for (int j = 0; j < BLOCK_LINE_AMOUNT; j++) {
			
			int number = Game::Instance().getRandom(30);
			std::shared_ptr<Entity> block;
			if (number >= 0 && number <= 27)
				block = std::make_shared<TypicalBlock>();
			else if (number > 27 && number <= 29)
				block = std::make_shared < RareBlock>();
			else
				block = std::make_shared <LegendaryBlock>();

			block->setPos(startPosX + i * block->getW() + i * 2,startPosY + j * block->getH() + j * 2);
			m_blocks.push_back(block);

			grid->addEntity(block.get());
		}
	}
}

void Level::gameOver()
{
	m_isGameOver = true;
}

void Level::setOnStart()
{
	m_start = false;
}

void Level::update(Input* input)
{
	grid->removeEntity(m_platform.get());
	m_platform->update(input);
	grid->addEntity(m_platform.get());

	if (!m_start || m_isGameOver) {
		if (input->isButtonClicked() && !m_isGameOver) {
			m_start = true;
		}

		auto platX = m_platform->getPosX();
		auto platY = m_platform->getPosY();
		m_ball->setPos(platX + m_platform->getW() / 2.0f, platY - m_ball->getH() - 4.0f);
	}
	else
	{
		if (m_blocks.empty()) {
			m_start = false;
			m_currentBallSpeed += 1.5f;
			startGame(m_currentBallSpeed);
			return;
		}

		m_ball->update(input);

		if (!m_blocks.empty()) {
			for (auto &block = m_blocks.begin(); block != m_blocks.end(); ) {
				if ((*block)->isDead()) {
					grid->removeEntity((*block).get());
					block = m_blocks.erase(block);
				}
				else {
					(*block)->update(input);
					block++;
				}
			}
		}
		grid->update(m_ball.get());

		
	}
}

void Level::render(SDL_Renderer *renderer)
{
	m_platform->render(renderer);
	if (!m_blocks.empty()) {
		for (auto &block : m_blocks)
			if(block != nullptr)
				block->render(renderer);
	}

	m_ball->render(renderer);
}

void Level::clear()
{
	grid->clear();
}
