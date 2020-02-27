#include "Game.h"

Game::Game(GameData& t_data) :
	m_data(t_data)
{
	exit = false;
}


Game::~Game()
{
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	srand(time(NULL));

	Render::Instance()->setUpRenderer(title, xPos, yPos, width, height, fullscreen);
	SDL_GetWindowSize(Render::Instance()->getWindow(), &width, &height);
	data::Instance()->setUpData(m_data);
	if (Render::Instance()->allOk())
	{
		isRunning = true;

	}
	else
	{
		isRunning = false;
	}
	m_gameStateMachine = new GameStateMachine();

	Vector2 screenDimensions = Vector2(width, height);

	m_gameStateMachine->changeState(new MenuState( screenDimensions,m_gameStateMachine));
}

/// handle user and system events/ input
void Game::processEvents()
{
	m_gameStateMachine->processEvents(isRunning);
}


/// Update the game world
void Game::update()
{
	m_gameStateMachine->update();

}

/// draw the frame and then switch bufers
void Game::render()
{
	//Clears image after every frame
	SDL_RenderClear(Render::Instance()->getRenderer());

	////Draw here
	m_gameStateMachine->render();

	//Presents the new Images
	SDL_RenderPresent(Render::Instance()->getRenderer());
}

void Game::cleanUp()
{
	Render::Instance()->renderToNull();
	Render::Instance()->windowToNull();

	window = nullptr;
	renderer = nullptr;

	SDL_Quit();
}

