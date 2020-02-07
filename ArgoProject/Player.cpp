#include "Player.h"

void Player::init(RenderSystem* t_rs)
{
	//draws a rectangle for the player
	m_playerRect = new SDL_Rect();
	m_playerRect->x = 100; m_playerRect->y = 100;
	m_playerRect->w = 50; m_playerRect->h = 50;

	SDL_Surface* ecsSurface = IMG_Load("Assets/ecs_text.png");
	texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), ecsSurface);

	m_player = new Entity();
	m_bs = new BehaviourSystem;

	m_pc = new PositionComponent(Vector2(m_playerRect->x, m_playerRect->y), 1);
	m_sc = new SpriteComponent(texture, m_playerRect, 2);
	m_bc = new BehaviourComponent(Vector2(0, 0), 10, 3);

	m_player->addComponent<PositionComponent>(m_pc, 1);
	m_player->addComponent<SpriteComponent>(m_sc, 2);
	m_player->addComponent<BehaviourComponent>(m_bc, 3);
	
	m_bs->addEntity(m_player);
	t_rs->addEntity(m_player);

}

void Player::update()
{
	//the player seeks the mouse position
	if (m_pc->getPosition().x != mousePosition.x && m_pc->getPosition().y != mousePosition.y)
	{
		m_bs->seek(mousePosition);
		m_playerRect->x = m_pc->getPosition().x;
		m_playerRect->y = m_pc->getPosition().y;
	}
}

void Player::processEvents(bool isRunning)
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
