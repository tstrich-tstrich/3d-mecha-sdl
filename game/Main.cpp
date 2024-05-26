#define SDL_MAIN_HANDLED
#include "Game.h"

int main(int argc, char** argv)
{
	Game game;

	if (game.Init())
	{
		game.RunGame();
	}

	return 0;
}