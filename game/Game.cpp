#include "Game.h"
#include <glm.hpp>

#include "Object.h"

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
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//return false if renderer fails
	if (mRenderer == nullptr)
	{
		SDL_Log("Renderer initialization failed: %s", SDL_GetError());
		return false;
	}

	// Enable relative mouse mode
	SDL_SetRelativeMouseMode(SDL_TRUE);
	// Clear any saved values
	SDL_GetRelativeMouseState(nullptr, nullptr);

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
	//check if the game window was closed
	SDL_Event currentEvent;
	while (SDL_PollEvent(&currentEvent))
	{
		//quit if the window is closed
		if (currentEvent.type == SDL_QUIT)
		{
			mIsRunning = false;
		}
	}

	//get keyboard state
	const Uint8* keysArray = SDL_GetKeyboardState(nullptr);
	//quit if escape is pressed
	if (keysArray[SDL_SCANCODE_ESCAPE] == 1)
	{
		mIsRunning = false;
	}

	//get mouse info
	int x = 0;
	int y = 0;
	Uint32 mouseButtons = SDL_GetRelativeMouseState(&x, &y);
	glm::vec2 relativeMouse(x, y);

	//send mouse+keyboard info to all objects to process input
	for (auto& obj : mObjects)
	{
		obj.get()->ProcessInput(keysArray, mouseButtons, relativeMouse);
	}
}

void Game::UpdateGame()
{
	Uint32 currentTicks = SDL_GetTicks();

	//calculate delta time in ms, then convert to seconds
	unsigned deltaTimeMS = currentTicks - mPrevTick;
	float deltaTime = static_cast<float>(deltaTimeMS) / 1000.0f;
	mPrevTick = currentTicks;

	//send deltaTime to all objects to update game state
	for (auto& obj : mObjects)
	{
		obj.get()->Update(deltaTime);
	}

	//iterate through all objects flagged for deletion and remove them from main object vector
	for (auto& obj : mDeletionBuffer)
	{
		auto iter = std::find(mObjects.begin(), mObjects.end(), obj);
		if (iter != mObjects.end())
		{
			mObjects.erase(iter);
		}
	}
	mDeletionBuffer.clear();

	//add newly created objects to main object vector and clear new object buffer
	mObjects.insert(mObjects.begin(), mNewObjectBuffer.begin(), mNewObjectBuffer.end());
	mNewObjectBuffer.clear();
}

void Game::GenerateOutput()
{
	//TODO put the actual game graphics here lol
	//set blue background
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	//send to screen
	SDL_RenderPresent(mRenderer);
}


void Game::AddObject(std::shared_ptr<class Object> obj)
{
	mNewObjectBuffer.push_back(obj);
}


void Game::DeleteObject(std::shared_ptr<class Object> obj)
{
	mDeletionBuffer.push_back(obj);
}

void Game::AddCollider(std::shared_ptr<class SphereColliderComp> col)
{
	//won't be creating colliders while checking collisions so can just add straight to vector
	mColliders.push_back(col);
}

void Game::RemoveCollider(std::shared_ptr<class SphereColliderComp> col)
{
	///should only be called from destructor of colliders
	auto iter = std::find(mColliders.begin(), mColliders.end(), col);
	if (iter != mColliders.end())
	{
		mColliders.erase(iter);
	}
}

