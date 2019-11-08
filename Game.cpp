#include "Game.h"



Game::Game():
	window(nullptr),
	renderer(nullptr),
	m_screenW(800),
	m_screenH(500)
{
	std::random_device device;
	rnd.seed(device());
}


Game::~Game()
{
	std::cout << "~Game()" << std::endl;
}

void Game::setDimensions(int screenW, int screenH)
{
	m_screenW = screenW;
	m_screenH = screenH;
}

bool Game::init()
{
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	window = SDL_CreateWindow("Arcanoid", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, m_screenW, m_screenH, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF_Init Error" << std::endl;
		return false;
	}

	m_input = std::make_unique<Input>();
	m_level = std::make_unique<Level>();
	m_level->init();

	return true;
}

void Game::run()
{
	Uint32 LastTime, TimeFPS;
	bool appRun = true;
	float unprocessed = 0.0f;
	float nsPerTick = 1000.0f / 30.0f;
	int frames = 0;
	int ticks = 0;
	LastTime = SDL_GetTicks();
	TimeFPS = SDL_GetTicks();

	while (appRun) {
		if (SDL_PollEvent(&m_event)) {
			if (m_event.type == SDL_QUIT) {
				appRun = false;
				break;
			}
			m_input->pollEvent(m_event);
		}

		Uint32 Now = SDL_GetTicks();
		unprocessed += (Now - LastTime) / nsPerTick;
		while (unprocessed >= 1.0f) {

			update();
			m_input->update();
			ticks++;
			unprocessed -= 1.0f;
		}
		LastTime = Now;
		frames++;
		render();
		if (SDL_GetTicks() - TimeFPS >= 1000) {
			TimeFPS += 1000;
			FPS = frames;
			Ticks = ticks;
			frames = ticks = 0;
		}
	}
}

void Game::clear()
{
	m_level->clear();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Game::update()
{
	m_level->update(m_input.get());
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
	SDL_RenderClear(renderer);
	m_level->render(renderer);

	SDL_RenderPresent(renderer);
}

int Game::getRandom(int max)
{
	std::uniform_int_distribution<int> range(0, max);
	return range(rnd);
}
