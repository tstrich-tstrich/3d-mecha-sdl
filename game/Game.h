#pragma once

#include <SDL.h>
#include <string>
#include <vector>

//the Game class is in charge of reading input, managing the overall game state, and sending info to the renderer to display on-screen. There should only ever be one instance of this class
//this codebase takes some inspiration from Sanjay Madhav's ITP380 game code. Shout-out to Sanjay!
class Game
{
public:
	//constants
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;
	const std::string mGameName = "";

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
