#include "Knight.h"

Knight::Knight()
{
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
	SDL_Surface* playerSurface = IMG_Load("Assets/knight.png");
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
	m_playerBot = new Entity();

	//Creates the Systems
	m_bs = new BehaviourSystem;
	finiteStateMachine = new FSM();
	state = new FiniteState();
	m_anim = new AnimationSystem();

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

	M_MAX_HEALTH = m_hc->getHealth() * 2;
	m_playerBot->setID(1);
	m_playerBot->addComponent<PositionComponent>(m_pc, 1);
	m_playerBot->addComponent<SpriteComponent>(m_sc, 2);
	m_playerBot->addComponent<BehaviourComponent>(m_bc, 3);
	m_playerBot->addComponent<StatsComponent>(m_statc, 4);
	m_playerBot->addComponent<HealthComponent>(m_hc, 5);
	m_playerBot->addComponent<ActiveComponent>(m_ac, 6);
	m_playerBot->addComponent<ManaComponent>(m_mc, 7);
	m_playerBot->addComponent<StaminaComponent>(m_stc, 9);
	m_rs = t_rs;

	m_bc->setMaxSpeed(m_statc->getSpeed());
	m_hc->setHealth(m_statc->getHealth());

	//Behaviour System
	m_bs->addEntity(m_playerBot);

	//Render System
	t_rs->addEntity(m_playerBot);

	m_particleEffects = new ParticleSystem("PLAY", t_rs);

	m_camera = t_camera;

	m_seek = false;

	//Input InputHandler
	m_ih = new InputHandler();
	m_ih->addEntity(m_playerBot);
	m_anim->addEntity(m_playerBot);

	m_ih->mousePosition = startPos;

	for (int i = 0; i < 3; i++)
	{
		m_skillCooldown[i] = false;
	}

	attackFinished = true;
	m_killCount = m_statc->getkillCount();

	finiteStateMachine->idle();
}

void Knight::update()
{	
	if (m_ih->move)
	{
		finiteStateMachine->walking();

		if (m_ih->mousePosition != m_ih->mouseRelativePosition + Vector2(m_camera->x, m_camera->y)
			&&
			m_ih->updateMouse)
		{
			m_ih->mousePosition = m_ih->mouseRelativePosition + Vector2(m_camera->x, m_camera->y);
		}
	}

	if (commandQueue.empty() && !m_ih->move && m_animationRect->x >= 1400 || !commandQueue.empty() && m_animationRect->x >= 1400 && !m_ih->move)
	{
		spriteSheetY = frameHeight * 2;
		finiteStateMachine->idle();
	}

	if (!commandQueue.empty() && m_animationRect->x != 0)
	{
		m_animationRect->x = 0;
		commandQueue.back()->execute(finiteStateMachine);
		commandQueue.pop_back();
	}

	setAction();
	if ((attackFinished == false) || finiteStateMachine->getCurrentState() == 0 || finiteStateMachine->getCurrentState() == 1)
	{
		m_anim->animate(m_animationRect, m_positionRect, spriteSheetY, frameWidth, 100, finiteStateMachine->getCurrentState(), m_attackTimer);
	}
	m_particleEffects->update();
}

void Knight::processEvents(bool isRunning)
{
	m_ih->generateInputs(commandQueue, m_camera);
}

void Knight::setAction()
{

		switch (finiteStateMachine->getCurrentState())
		{
		case 0:
			spriteSheetY = frameHeight * 2;
			attackFinished = true;
			break;
		case 1:
			spriteSheetY = frameHeight;
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
			attackFinished = true;
			break;
		case 2:
			if (m_skillCooldown[0] == false && attackFinished == true && m_mc->getMana() > 0)
			{
				setDamage(0.01);	
				m_attackTimer = SDL_GetTicks();
				m_ih->move = false;
				attackFinished = false;
				spriteSheetY = frameHeight * 3;
			}
			break;
		case 3:
			if (m_skillCooldown[1] == false && attackFinished == true && m_mc->getMana() > 0)
			{
				setDamage(0.03);	
				m_ih->move = false;
				m_attackTimer = SDL_GetTicks();
				attackFinished = false;
				spriteSheetY = 0;
			}
			break;
		case 4:
			if (m_skillCooldown[2] == false && attackFinished == true && m_mc->getMana() > 0)
			{
				m_particleEffects->AddParticles(m_pc->getPosition(), Type::EXPLOSION, 10,10,"Assets/Tiles/tile.png");
				spriteSheetY = frameHeight * 4;
				m_attackTimer = SDL_GetTicks();
				m_ih->move = false;
				attackFinished = false;
			}
			break;
		default:
			break;
		}
}

void Knight::Attack(float& m_enemyHealth)
{
	if (finiteStateMachine->getCurrentState() == 2)
	{
		if (m_skillCooldown[0] == false )
		{
			m_mc->alterMana(-3);
			m_enemyHealth -= dmg;
			m_attackFrame = 0;
			if (m_animationRect->x >= 1000 && m_animationRect->x <= 1400)
			{
				m_skillCooldown[0] = true;
			}
		}
	}

	if (finiteStateMachine->getCurrentState() == 3)
	{
		if (m_skillCooldown[1] == false)
		{
			m_mc->alterMana(-3);
			m_enemyHealth -= dmg;
			m_attackFrame = 0;
			if (m_animationRect->x >= 1000 && m_animationRect->x <= 1400)
			{
				m_skillCooldown[1] = true;
			}
		}
	}

	if (finiteStateMachine->getCurrentState() == 4)
	{
		if (m_skillCooldown[2] == false)
		{
			m_mc->alterMana(-6);
			m_hc->alterHealth(5);
			m_attackFrame = 0;
			if (m_animationRect->x >= 1000 && m_animationRect->x <= 1400)
			{
				m_skillCooldown[2] = true;
			}
		}
	}
}

bool Knight::getMenuActive()
{
	return m_ih->m_menuActive;
}

void Knight::turnOffMenu()
{
	m_ih->m_menuActive = false;
}