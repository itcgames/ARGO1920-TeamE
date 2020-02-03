#include "Game.h"

Game::Game()
{
	exit = false;
}


Game::~Game()
{
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << " Subsystem initialised!!" << std::endl;
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

		if (window)
		{
			std::cout << "Window Created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0 | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer Created" << std::endl;

		}

		isRunning = true;

	}
	else
	{
		isRunning = false;
	}
	m_gameStateMachine = new GameStateMachine();
	m_gameStateMachine->changeState(new PlayState(),renderer);

}

/// handle user and system events/ input
void Game::processEvents()
{
	//Handles all the inputs
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
}


/// Update the game world
void Game::update()
{

}

/// draw the frame and then switch bufers
void Game::render()
{
	//Clears image after every frame
	SDL_RenderClear(renderer);

	////Draw here
	m_gameStateMachine->render();

	//Presents the new Images
	SDL_RenderPresent(renderer);
}

void Game::cleanUp()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	renderer = nullptr;

	SDL_Quit();
	std::cout << "Cleaned" << std::endl;

}

