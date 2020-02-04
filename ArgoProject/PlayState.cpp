#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";


void PlayState::update()
{
	//the player seeks the mouse position
	if (m_playerRect->x != mousePosition.x && m_playerRect->y != mousePosition.y)
	{
		Vector2 playerPosition = Vector2(m_playerRect->x, m_playerRect->y);
		m_velocity = mousePosition - playerPosition;
		Vector2 normalizedVelo = Normalize(m_velocity);
		playerPosition.x += normalizedVelo.x * maxSpeed;
		playerPosition.y += normalizedVelo.y * maxSpeed;

		m_playerRect->x = playerPosition.x;
		m_playerRect->y = playerPosition.y;
	}

}

void PlayState::render()
{
	m_rs->render(Render::Instance()->getRenderer());
}

/// handle user and system events/ input
void PlayState::processEvents(bool isRunning)
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
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				std::cout << "left mouse button" << std::endl;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				mousePosition.x = event.button.x;
				mousePosition.y = event.button.y;
				move = true;
			}
			break;
		case SDL_MOUSEMOTION:
			if (move)
			{
				mousePosition.x += event.motion.xrel;
				mousePosition.y += event.motion.yrel;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			move = false;
			//m_mouseRect->x = event.button.x;
			//m_mouseRect->y = event.button.y;
			break;
		default:
			break;
		}
	}
}

bool PlayState::onEnter()
{
	std::cout << "Entering Play State\n";

	//draws a rectangle for the player
	m_playerRect = new SDL_Rect();
	m_playerRect->x = 100; m_playerRect->y = 100;
	m_playerRect->w = 100; m_playerRect->h = 100;

	m_rs = new RenderSystem();

	SDL_Surface* ecsSurface = IMG_Load("Assets/ecs_text.png");
	texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface);

	m_player = new Entity();

	m_pc = new PositionComponent(Vector2(m_playerRect->x, m_playerRect->y), 1);
	m_sc = new SpriteComponent(texture, m_playerRect, 2);

	m_player->addComponent<PositionComponent>(m_pc, 1);
	m_player->addComponent<SpriteComponent>(m_sc, 2);

	m_rs->addEntity(m_player);

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

	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}

Vector2 PlayState::Normalize(Vector2& t_vector)
{
	Vector2 normalizedVector{ 0,0 };
	normalizedVector = t_vector / (sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y)));
	return normalizedVector;
}
