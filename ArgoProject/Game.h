#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void update();

	void processEvents();
	void render();
	void cleanUp();

	bool running() { return isRunning; }


private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool m_exitGame; // control exiting game

	// InputHandler Variables
	bool exit;
	//InputHandler* inputHandler;

	////Creates the Command Queue
	//std::vector<Command*> commandQueue;


	GameStateMachine* m_gameStateMachine;
	int timer = 0;
};

