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
	srand(time(NULL));

	Render::Instance()->setUpRenderer(title, xPos, yPos, width, height, fullscreen);

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

	m_gameStateMachine->changeState(new PlayState( screenDimensions));


	////
	//m_playerRect = new SDL_Rect();
	//m_playerRect->x = 200; m_playerRect->y = 200;
	//m_playerRect->w = 78; m_playerRect->h = 138;
	//m_rs = new RenderSystem();

	//SDL_Surface* ecsSurface = IMG_Load("Assets/ecs_text.png");
	//m_ecsTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface);

	//m_entity = new Entity();

	//m_pc = new PositionComponent(Vector2(m_playerRect->x, m_playerRect->y), 1);
	//m_sc = new SpriteComponent(m_ecsTexture, m_playerRect, 2);

	//m_entity->addComponent<PositionComponent>(m_pc, 1);
	//m_entity->addComponent<SpriteComponent>(m_sc, 2);

	//m_rs->addEntity(m_entity);


	// To get position of entity within a system type m_entities[i]->getComponent<PositionComponent>(1)->getPosition();
	// Why this way?
	// System's derive from base System which has an std::vector of Entities;
	// When getting component, component type must be put in <> and component ID in (), ID helps with finding componets for Entities;
	// Two components should not have same ID value, i.e Position and Sprite components should not have an ID of 1;
	// using getPosition() is a method within the component simply used to get it's data
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

	//m_rs->render(Render::Instance()->getRenderer());

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
	std::cout << "Cleaned" << std::endl;

}

