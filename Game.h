#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <random>
#include "Input.h"
#include "Level.h"


class Game
{
public:

	static Game& Instance() {
		static Game myInstance;

		return myInstance;
	}
	
	void setDimensions(int screenW, int screenH);

	bool init();
	void run();
	void clear();

	int getRandom(int max);
	int getScreenWidth() const { return m_screenW; }
	int getScreenHeight() const { return m_screenH; }

	Level* getLevel() const { return m_level.get(); }
	
private:
	Game();
	~Game();

	Game(Game const&) = delete;             
	Game(Game&&) = delete;                  
	Game& operator=(Game const&) = delete;  
	Game& operator=(Game &&) = delete;

	void update();
	void render();

private:
	std::mt19937 rnd;

	int m_screenW;
	int m_screenH;
	Uint32 FPS, Ticks;

	std::unique_ptr<Input> m_input;
	std::unique_ptr<Level> m_level;

	SDL_Event m_event;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

};

