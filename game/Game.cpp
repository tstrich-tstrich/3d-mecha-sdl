#include "Game.h"

Game::Game()
    : mWindow(nullptr)
    , mRenderer(nullptr)
    , mIsRunning(false)
    , mPrevTick(0)
{
}

Game::~Game()
{
    Shutdown();
}

bool Game::Init()
{
    //initialize SDL
	bool initSDLSuccessful = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) == 0;
    if (!initSDLSuccessful)
    {
        SDL_Log("Failed to initialize SDL! %s", SDL_GetError());
        return false;
    }
	//initialize window
	mWindow = SDL_CreateWindow(mGameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN);
	//return false if window fails
	if (mWindow == nullptr)
	{
		SDL_Log("Window initialization failed: %s", SDL_GetError());
		return false;
	}
	//initialize renderer
	mRenderer =
		SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//return false if renderer fails
	if (mRenderer == nullptr)
	{
		SDL_Log("Renderer initialization failed: %s", SDL_GetError());
		return false;
	}
	//if nothing has gone wrong, return true
	return true;

    
}

void Game::RunGame()
{
}

void Game::Shutdown()
{
}

void Game::ProcessInput()
{
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}
