#include "Ball.h"

#include "Block.h"
#include "Platform.h"

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius )
{
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; 
			int dy = radius - h; 
			if ((dx*dx + dy*dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}

Ball::Ball()
{
	m_speed = DEFAULT_BALL_SPEED;
	auto rnd = Game::Instance().getRandom(2);
	m_direction.x = (rnd == 0) ? rnd - 1 : rnd;
	m_direction.y = 1.0f;
	m_radius = BALL_RADIUS;

	m_life = LIFE_COUNT;
	m_bonusCount = 0;

	color.r = 150; color.g = 155; color.b = 200; color.a = 255;
	m_bonusColor.r = 140; m_bonusColor.g = 0; m_bonusColor.b = 0; m_bonusColor.a = 255;

	m_currentColor = color;
}

Ball::Ball(float radius): 
Ball()
{
	m_radius = radius;
	m_rect.w = m_rect.h = m_radius;
}


Ball::~Ball()
{
	std::cout << "~Ball()" << std::endl;
}

void Ball::setSpeed(float speed)
{
	m_speed = speed;
}

void Ball::update(Input * input)
{
	m_posX += m_direction.x * m_speed;
	m_posY += m_direction.y * m_speed;

	m_aabb.center.x = m_posX;
	m_aabb.center.y = m_posY;
	m_aabb.r[0] = m_aabb.r[1] = m_radius;

	if (m_posX - m_radius <= 0.0f || m_posX + m_radius >= Game::Instance().getScreenWidth())
		m_direction.x = -m_direction.x;
	if (m_posY - m_radius <= 0.0f)
		m_direction.y = -m_direction.y;

	if (m_posY + m_radius >= Game::Instance().getScreenHeight()) {
		
		m_bonusCount = 0;
		m_currentColor = color;
		if (--m_life > 0)
			Game::Instance().getLevel()->setOnStart();
		else
			Game::Instance().getLevel()->gameOver();
	}
}

void Ball::render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, m_currentColor.r, m_currentColor.g, m_currentColor.b, m_currentColor.a);
	draw_circle(renderer, m_posX, m_posY, m_radius);
}

void Ball::collide(const Entity * e, Point p)
{
	auto block = dynamic_cast<const Block*>(e);
	if (block != nullptr) {
		if (block->getType() == Block::eBlockType::LEGENDARY) {
			m_bonusCount = BONUS_COUNT;
			m_currentColor = m_bonusColor;
		}
	}
	auto platform = dynamic_cast<const Platform*>(e);
	if (m_bonusCount == 0 || platform) 
	{
		if (fabs(p.x) > 0.0f)
			m_direction.x = -m_direction.x;
		else
			m_direction.y = -m_direction.y;

		if (m_bonusCount > 0) {
			m_bonusCount--;
			if (m_bonusCount == 0)
				m_currentColor = color;
		}
	}
}

void Ball::setDirection(Point dir)
{
	m_direction.x = dir.x;
	m_direction.y = dir.y;
}
