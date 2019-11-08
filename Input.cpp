#include "Input.h"
#include <iostream>


Input::Input():
	m_mousePressed(false),
	m_wasMousePressed(false)
{
}


Input::~Input()
{
	std::cout << "~Input()" << std::endl;
}

void Input::pollEvent(SDL_Event & event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT)
			m_mousePressed = true;
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT)
			m_mousePressed = false;
	}
	if (event.type == SDL_MOUSEMOTION) {
		mX = event.motion.x;
		mY = event.motion.y;
	}
}

void Input::update()
{
	m_wasMousePressed = m_mousePressed;
}
