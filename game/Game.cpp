#include "Game.h"
#include <glm.hpp>

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
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
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
	mIsRunning = true;

	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	//shut down everything
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent))
	{
		//quit if the window is closed
		if (currentEvent.type == SDL_QUIT)
		{
			mIsRunning = false;
		}
	}
	const Uint8* keysArray = SDL_GetKeyboardState(nullptr);
	//quit if escape is pressed
	if (keysArray[SDL_SCANCODE_ESCAPE] == 1)
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
	//frame limiting
	while (SDL_GetTicks() - mPrevTick < 16)
	{
		//wait in this loop until at least 16ms have passed
	}
	Uint32 currentTicks = SDL_GetTicks();

	//calculate delta time in ms, then convert to seconds
	unsigned deltaTimeMS = currentTicks - mPrevTick;
	if (deltaTimeMS > 33)
	{
		deltaTimeMS = 33;
	}
	float deltaTime = static_cast<float>(deltaTimeMS) / 1000.0f;
	mPrevTick = currentTicks;
}

void Game::GenerateOutput()
{
	//set blue background
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	//send to screen
	SDL_RenderPresent(mRenderer);
}
