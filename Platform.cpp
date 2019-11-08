#include "Platform.h"
#include <algorithm>
#include "Game.h"
#include "Input.h"

#define OFFSET 10

float clamp(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}


Platform::Platform()
{
	color.r = 150;
	color.g = 150;
	color.b = 150;
	color.a = 255;

	m_rect.x = m_posX = Game::Instance().getScreenWidth() / 2;
	m_rect.y = m_posY = Game::Instance().getScreenHeight() - 50;
	setSize(80, 20);
}


Platform::~Platform()
{
	std::cout << "~Platform()" << std::endl;
}

void Platform::update(Input * input)
{
	float mouseX = input->getMouseX();
	m_posX = mouseX;
	m_posX = clamp(mouseX, OFFSET, Game::Instance().getScreenWidth() - m_rect.w - OFFSET);
	m_rect.x = m_posX;
	updateAABB();
}

void Platform::render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &m_rect);
}

void Platform::collide(const Entity * e, Point p)
{
}
