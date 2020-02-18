#include "Knight.h"

Knight::Knight()
{
	std::cout << "You are a Knight" << std::endl;
}

Knight::~Knight()
{
}

void Knight::init(RenderSystem* t_rs, SDL_Rect* t_camera, Vector2 startPos)
{
	//creates a source and size rectangle for the player animation
	m_positionRect = new SDL_Rect();
	m_positionRect->x = startPos.x;
	m_positionRect->y = startPos.y;

	m_animationRect = new SDL_Rect();
	m_animationRect->x = 0;
	m_animationRect->y = 0;

	//load in the player texture
	SDL_Surface* playerSurface = IMG_Load("Assets/warrior.png");
	m_playerTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playerSurface);
	SDL_QueryTexture(m_playerTexture, NULL, NULL, &textureWidth, &textureHeight);
	SDL_FreeSurface(playerSurface);

	//set both rectangles to the size of one frame from the sprite sheet
	frameWidth = textureWidth / 11;
	frameHeight = textureHeight / 5;
	//Players Position Rect Size
	m_positionRect->w = frameWidth;
	m_positionRect->h = frameHeight;
	//Players Animation Rect Size
	m_animationRect->w = frameWidth;
	m_animationRect->h = frameHeight;


	//Create Entities
	m_player = new Entity();

	//Creates the Systems
	m_bs = new BehaviourSystem;
	finiteStateMachine = new FSM();
	state = new FiniteState();

	//Player Animated Rect Components amd Adding those
	m_pc = new PositionComponent(Vector2(m_positionRect->x, m_positionRect->y), 1);
	m_sc = new SpriteComponent(m_playerTexture, m_positionRect, 2);
	m_bc = new BehaviourComponent(Vector2(0, 0), 10, 0, 3);
	

	m_statc = new StatsComponent(data::Instance()->getData().m_playerStats.at(0).m_class, data::Instance()->getData().m_playerStats.at(0).m_health,
		data::Instance()->getData().m_playerStats.at(0).m_strength, data::Instance()->getData().m_playerStats.at(0).m_speed,
		data::Instance()->getData().m_playerStats.at(0).m_gold, data::Instance()->getData().m_playerStats.at(0).m_killCount, 4);

	m_hc = new HealthComponent(data::Instance()->getData().m_playerStats.at(0).m_health, 5);
	m_ac = new ActiveComponent(true, 6);
	m_mc = new ManaComponent(250.0f, 7);
	m_stc = new StaminaComponent(1000, 9);

	m_player->setID(1);
	m_player->addComponent<PositionComponent>(m_pc, 1);
	m_player->addComponent<SpriteComponent>(m_sc, 2);
	m_player->addComponent<BehaviourComponent>(m_bc, 3);
	m_player->addComponent<StatsComponent>(m_statc, 4);
	m_player->addComponent<HealthComponent>(m_hc, 5);
	m_player->addComponent<ActiveComponent>(m_ac, 6);
	m_player->addComponent<ManaComponent>(m_mc, 7);
	m_player->addComponent<StaminaComponent>(m_stc, 9);
	m_rs = t_rs;

	m_bc->setMaxSpeed(m_statc->getSpeed());
	m_hc->setHealth(m_statc->getHealth());

	//Behaviour System
	m_bs->addEntity(m_player);

	//Render System
	t_rs->addEntity(m_player);

	m_camera = t_camera;

	m_seek = false;

	//Input InputHandler
	m_ih = new InputHandler();
	m_ih->addEntity(m_player);

	m_ih->mousePosition = startPos;
}

void Knight::update()
{
	//checks if the player is in walking state
	if (finiteStateMachine->getCurrentState() == 1)
	{
		//the player seeks the mouse position
		if (m_pc->getPosition().x != m_ih->mousePosition.x && m_pc->getPosition().y != m_ih->mousePosition.y)
		{
			m_seek = true;
			//This is to stop the jittering in the movement.         
			float mag = sqrt((m_pc->getPosition().x - m_ih->mousePosition.x) * (m_pc->getPosition().x - m_ih->mousePosition.x) + (m_pc->getPosition().y - m_ih->mousePosition.y) * (m_pc->getPosition().y - m_ih->mousePosition.y));
			if (mag > 40)
			{
				//m_bs->seek(m_ih->mousePosition);
				m_bs->seek(m_ih->mousePosition);
			}
			else
			{
				m_ih->move = false;
			}
			m_positionRect->x = m_pc->getPosition().x;
			m_positionRect->y = m_pc->getPosition().y;
		}
		else
		{
			m_seek = false;
		}
	}

	if (finiteStateMachine->getCurrentState() == 2)
	{
		spriteSheetY = 226;
	}

	if (finiteStateMachine->getCurrentState() == 3)
	{
		spriteSheetY = 339;
	}

	if (finiteStateMachine->getCurrentState() == 4)
	{
		spriteSheetY = 452;
	}

	if (finiteStateMachine->getCurrentState() == 5)
	{
		spriteSheetY = 565;
	}
	animate();

	if (m_ih->move)
	{
		spriteSheetY = frameHeight;
		finiteStateMachine->walking();

		if (m_ih->mousePosition != m_ih->mouseRelativePosition + Vector2(m_camera->x, m_camera->y)
			&&
			m_ih->updateMouse)
		{
			m_ih->mousePosition = m_ih->mouseRelativePosition + Vector2(m_camera->x, m_camera->y);
		}
	}

	if (commandQueue.empty() && !m_ih->move && m_animationRect->x == textureWidth - frameWidth)
	{
		spriteSheetY = frameHeight * 2;
		finiteStateMachine->idle();
	}

	else while (!commandQueue.empty())
	{
		m_animationRect->x = 0;
		commandQueue.back()->execute(finiteStateMachine);
		commandQueue.pop_back();
	}

	setAction();
	animate();
}

void Knight::animate()
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 100) % 11;
	m_animationRect->x = sprite * (frameWidth);
	m_animationRect->y = spriteSheetY;

	m_sc->setRect(m_animationRect);
	m_sc->setDstRect(m_positionRect);
}

void Knight::processEvents(bool isRunning)
{
	m_ih->generateInputs(commandQueue, m_camera);
}

void Knight::setAction()
{
	switch (finiteStateMachine->getCurrentState())
	{
	case 1:
		//the player seeks the mouse position
		if (m_pc->getPosition().x != m_ih->mousePosition.x && m_pc->getPosition().y != m_ih->mousePosition.y)
		{
			m_seek = true;
			//This is to stop the jittering in the movement.         
			float mag = sqrt((m_pc->getPosition().x - m_ih->mousePosition.x) * (m_pc->getPosition().x - m_ih->mousePosition.x) + (m_pc->getPosition().y - m_ih->mousePosition.y) * (m_pc->getPosition().y - m_ih->mousePosition.y));
			if (mag > 40)
			{
				m_bs->playerSeek(m_ih->mousePosition, m_seek);
			}
			else
			{
				m_ih->move = false;
			}
			m_positionRect->x = m_pc->getPosition().x;
			m_positionRect->y = m_pc->getPosition().y;
		}
		else
		{
			m_seek = false;
		}
		break;
	case 2:
		m_animationRect->x = 0;
		spriteSheetY = 0;
		break;
	case 3:
		m_animationRect->x = 0;
		spriteSheetY = frameHeight * 3;
		break;
	case 4:
		m_animationRect->x = 0;
		spriteSheetY = frameHeight * 4;
		break;
	case 5:
		m_animationRect->x = 0;
		spriteSheetY = frameHeight * 5;
		break;
	default:
		break;
	}
}