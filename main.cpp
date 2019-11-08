#include <iostream>
#include <SDL.h>
#include "Game.h"

int main(int argc, char** argv)
{
	Game::Instance().setDimensions(800, 600);
	if( !Game::Instance().init() ) {
		return 1;
	}

	Game::Instance().run();
	Game::Instance().clear();

	return 0;
}