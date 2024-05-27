#define SDL_MAIN_HANDLED
#include "Game.h"

//main function, runs the game. not much else to say
int main(int argc, char** argv)
{
	Game game;

	if (game.Init())
	{
		game.RunGame();
	}

	return 0;
}