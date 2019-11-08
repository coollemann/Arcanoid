#pragma once
#include <SDL.h>

class Input final
{
public:
	Input();
	~Input();

	inline bool isMousePressed() const { return m_mousePressed; }
	inline bool wasMousePressed() const { return m_wasMousePressed; }

	bool isButtonClicked() const { return isMousePressed() && !wasMousePressed(); }

	Uint32 getMouseX() const { return mX; }
	Uint32 getMouseY() const { return mY; }

	void pollEvent(SDL_Event &event);
	void update();
	

private:

	Uint32 mX, mY;
	bool m_mousePressed;
	bool m_wasMousePressed;
};

