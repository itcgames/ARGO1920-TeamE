#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";


void PlayState::update()
{
<<<<<<< HEAD
	//the player seeks the mouse position
	if (m_playerRect->x != mousePosition.x && m_playerRect->y != mousePosition.y)
	{
		Vector2 playerPosition = Vector2(m_playerRect->x, m_playerRect->y);
		m_playerVelocity = mousePosition - playerPosition;
		Vector2 normalizedVelo = Normalize(m_playerVelocity);
		playerPosition.x += normalizedVelo.x * maxSpeed;
		playerPosition.y += normalizedVelo.y * maxSpeed;

		m_playerRect->x = playerPosition.x;
		m_playerRect->y = playerPosition.y;
	}

=======
	m_player.update();
>>>>>>> 5d08310d226791b074561675216462481b0f601d
}

void PlayState::render()
{
	m_rs->render(Render::Instance()->getRenderer());
}

/// handle user and system events/ input
void PlayState::processEvents(bool isRunning)
{
	m_player.processEvents(isRunning);
}

bool PlayState::onEnter()
{
	std::cout << "Entering Play State\n";
	m_rs = new RenderSystem();
<<<<<<< HEAD

	SDL_Surface* ecsSurface = IMG_Load("Assets/ecs_text.png");
	texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface);

	m_player = new Entity();

	m_pc = new PositionComponent(Vector2(m_playerRect->x, m_playerRect->y), 1);
	m_sc = new SpriteComponent(texture, m_playerRect, 2);

	m_player->addComponent<PositionComponent>(m_pc, 1);
	m_player->addComponent<SpriteComponent>(m_sc, 2);

	m_rs->addEntity(m_player);

	//creates the enemy and adds it to the render system
	m_enemy.initialize(m_rs);

	//draws a rectangle on the mouse when you click and drag 
	//m_mouseRect = new SDL_Rect();
	//m_mouseRect->x = 100; m_mouseRect->y = 100;
	//m_mouseRect->w = 10; m_mouseRect->h = 10;

	//SDL_Surface* mouseSurface = IMG_Load("Assets/MouseArrow.png");
	//mouseTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), mouseSurface);

	//m_mouse = new Entity();

	//m_mousepc = new PositionComponent(Vector2(m_mouseRect->x, m_mouseRect->y), 1);
	//m_mousesc = new SpriteComponent(mouseTexture, m_playerRect, 2);

	//m_mouse->addComponent<PositionComponent>(m_mousepc, 1);
	//m_mouse->addComponent<SpriteComponent>(m_mousesc, 2);

	//m_mousers->addEntity(m_mouse);

=======
	m_player.init(m_rs);
>>>>>>> 5d08310d226791b074561675216462481b0f601d
	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}