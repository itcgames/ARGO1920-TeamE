#include "Warrior.h"

Warrior::Warrior()
{
}

Warrior::~Warrior()
{
	SDL_DestroyTexture(m_playerTexture);
	delete walkSound;
	delete attackSound;
	delete slamAttackSound;
	delete spinAttackSound;
}

void Warrior::init(RenderSystem* t_rs, SDL_Rect* t_camera, Vector2 startPos)
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
	m_anim = new AnimationSystem();

	//Player Animated Rect Components amd Adding those
	m_pc = new PositionComponent(Vector2(m_positionRect->x, m_positionRect->y), 1);
	m_sc = new SpriteComponent(m_playerTexture, m_positionRect, 2);
	m_bc = new BehaviourComponent(Vector2(0, 0), 10, 0, 3);

	m_stc = new StaminaComponent(1000, 9);

	m_statc = new StatsComponent(data::Instance()->getData().m_playerStats.at(0).m_class, data::Instance()->getData().m_playerStats.at(0).m_health,
		data::Instance()->getData().m_playerStats.at(0).m_strength, data::Instance()->getData().m_playerStats.at(0).m_speed,
		data::Instance()->getData().m_playerStats.at(0).m_gold, data::Instance()->getData().m_playerStats.at(0).m_killCount, 4);

	m_hc = new HealthComponent(data::Instance()->getData().m_playerStats.at(0).m_health, 5);
	M_MAX_HEALTH = m_hc->getHealth() * 2;
	m_ac = new ActiveComponent(true, 6);
	m_mc = new ManaComponent(250.0f, 7);

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
	m_anim->addEntity(m_player);

	m_ih->mousePosition = startPos;

	m_particleEffects = new ParticleSystem("PLAY", t_rs);

	walkSound = new Audio();
	attackSound = new Audio();
	slamAttackSound = new Audio();
	spinAttackSound = new Audio();

	walkSound->load("Assets/Audio/walk.wav");
	attackSound->load("Assets/Audio/attack1.wav");
	slamAttackSound->load("Assets/Audio/slam.wav");
	spinAttackSound->load("Assets/Audio/spinAttack.wav");


	for (int i = 0; i < 3; i++)
	{
		m_skillCooldown[i] = false;
	}
	attackFinished = true;
	m_attackFrame = 9999;
	m_killCount = m_statc->getkillCount();

	finiteStateMachine->idle();
}

void Warrior::update()
{
	if (m_ih->move)
	{
		finiteStateMachine->walking();

		//Allows to click and hold to move
		if (m_ih->mousePosition != m_ih->mouseRelativePosition + Vector2(m_camera->x, m_camera->y) && m_ih->updateMouse)
		{
			m_ih->mousePosition = m_ih->mouseRelativePosition + Vector2(m_camera->x, m_camera->y);
		}
	}

	if ((commandQueue.empty() && !m_ih->move && m_animationRect->x >= 1400) || (!commandQueue.empty() && m_animationRect->x >= 1400 && !m_ih->move))
	{
		finiteStateMachine->idle();
		spriteSheetY = frameHeight * 2;
	}

	if(!commandQueue.empty() && m_animationRect->x != 0)
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

void Warrior::processEvents(bool isRunning)
{
	m_ih->generateInputs(commandQueue, m_camera);
}

void Warrior::setAction()
{

		switch (finiteStateMachine->getCurrentState())
		{
		case 0:
			spriteSheetY = frameHeight * 2;
			attackFinished = true;
			break;
		case 1:
			//the player seeks the mouse position
			spriteSheetY = frameHeight;
			if (m_pc->getPosition().x != m_ih->mousePosition.x && m_pc->getPosition().y != m_ih->mousePosition.y)
			{
				walkSound->play();
				m_particleEffects->AddParticles(m_pc->getPosition(), Type::TRAIL, 10,10, "Assets/Tiles/tile.png");
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
					walkSound->stop();
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
				spriteSheetY = 0;
				attackSound->play();
				m_ih->move = false;

				m_attackTimer = SDL_GetTicks();
				attackFinished = false;
			}
			break;
		case 3:
			if (m_skillCooldown[1] == false &&  attackFinished == true && m_mc->getMana() > 0)
			{
				setDamage(0.015);
				spriteSheetY = frameHeight * 3;
				slamAttackSound->play();
				m_ih->move = false;

				m_attackTimer = SDL_GetTicks();
				attackFinished = false;
				
			}
			break;
		case 4:
			if (m_skillCooldown[2] == false  && attackFinished == true && m_mc->getMana() > 0)
			{
				setDamage(0.02);
				spriteSheetY = frameHeight * 4;
				spinAttackSound->play();
				m_ih->move = false;

				m_attackTimer = SDL_GetTicks();
				attackFinished = false;
			}
			break;
		default:
			attackSound->stop();
			spinAttackSound->stop();
			slamAttackSound->stop();
			walkSound->stop();
			break;
		}
	
}

void Warrior::Attack(float &m_enemyHealth)
{
	if (finiteStateMachine->getCurrentState() == 2 )
	{
		if (m_skillCooldown[0] == false )
		{
			m_mc->alterMana(-2);
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
			m_mc->alterMana(-4);
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
			m_enemyHealth -= dmg;
			m_attackFrame = 0;
			if (m_animationRect->x >= 1000 && m_animationRect->x <= 1400)
			{
				m_skillCooldown[2] = true;
			}
		}
	}
}

bool Warrior::getMenuActive()
{
	return m_ih->m_menuActive;
}

void Warrior::turnOffMenu()
{
	m_ih->m_menuActive = false;
}