#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include <memory>

//the Game class is in charge of reading input, managing the overall game state, and sending info to the renderer to display on-screen. There should only ever be one instance of this class
//this codebase takes some inspiration from Sanjay Madhav's ITP380 game code. Shout-out to Sanjay
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
	
	void AddObject(std::shared_ptr<class Object> obj);
	void DeleteObject(std::shared_ptr<class Object> obj);

	void AddCollider(std::shared_ptr<class ColliderComp> obj);

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	
	bool mIsRunning;
	Uint32 mPrevTick;

	std::shared_ptr<class PlayerObj> mPlayer;

	std::vector<std::shared_ptr<class Object>> mObjects;
	std::vector<std::shared_ptr<class Object>> mNewObjectBuffer;
	std::vector<std::shared_ptr<class Object>> mDeletionBuffer;
	std::vector<std::shared_ptr<class ColliderComp>> mColliders;

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
};
