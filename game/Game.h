#pragma once

#include <SDL.h>
#include <string>

class Game
{
public:
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;
	std::string mGameName = "";

	Game();
	~Game();

	bool Init();
	void RunGame();
	void Shutdown();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	Uint32 mPrevTick;

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

};
