 #include "Mage.h"

Mage::Mage()
{
}

Mage::~Mage()
{
}

void Mage::init(RenderSystem* t_rs, SDL_Rect* t_camera, Vector2 startPos)
{
	//creates a source and size rectangle for the player animation
	m_positionRect = new SDL_Rect();
	m_positionRect->x = startPos.x;
	m_positionRect->y = startPos.y;

	m_animationRect = new SDL_Rect();
	m_animationRect->x = 0;
	m_animationRect->y = 0;

	//load in the player texture
	SDL_Surface* playerSurface = IMG_Load("Assets/mage.png");
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
	m_ac = new ActiveComponent(true, 6);
	m_mc = new ManaComponent(250.0f, 7);
	M_MAX_HEALTH = m_hc->getHealth() * 2;

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

	for (int i = 0; i < 3; i++)
	{
		m_skillCooldown[i] = false;
		m_skillActive[i] = false;
	}

	m_killCount = m_statc->getkillCount();
	m_particleEffects = new ParticleSystem("PLAY", t_rs);


}

void Mage::update()
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
	}

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

	if (commandQueue.empty() && !m_ih->move && m_animationRect->x >= 1400 || !commandQueue.empty() && m_animationRect->x >= 1400 && !m_ih->move)
	{
		spriteSheetY = frameHeight * 2;
		finiteStateMachine->idle();
	}

	else while (!commandQueue.empty() && m_animationRect->x != 0)
	{
		m_animationRect->x = 0;
		commandQueue.back()->execute(finiteStateMachine);
		commandQueue.pop_back();
	}

	if (m_skillCooldown[0])
	{
		m_particleEffects->AddParticles(m_pc->getPosition(), Type::EXPLOSION, 16);
	}

	setAction();
	m_particleEffects->update();	
	m_anim->animate(m_animationRect, m_positionRect, spriteSheetY, frameWidth, 100,finiteStateMachine->getCurrentState(), m_attackTimer);
}

void Mage::processEvents(bool isRunning)
{
	m_ih->generateInputs(commandQueue, m_camera);
}

void Mage::setAction()
{
	if (m_mc->getMana() > 0)
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
			if (m_skillCooldown[0] == false)
			{
				setDamage(1);
				m_particleEffects->AddParticles(m_pc->getPosition(), Type::EXPLOSION, 16);
				spriteSheetY = 0;
				
			}
			break;
		case 3:
			if (m_skillCooldown[1] == false)
			{
				spriteSheetY = frameHeight * 3;
			}
			break;
		case 4:
			if (m_skillCooldown[2] == false)
			{
				spriteSheetY = frameHeight * 4;
			}
			break;
		case 5:
			spriteSheetY = frameHeight * 5;
			break;
		default:
			break;
		}
	}
}

void Mage::Attack(float& m_enemyHealth)
{
	if (finiteStateMachine->getCurrentState() == 2)
	{
		if (m_skillCooldown[0] == false)
		{
			m_mc->alterMana(-10);
			m_enemyHealth -= dmg;
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
			m_mc->alterMana(-12);
			m_hc->alterHealth(10);
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
			m_mc->alterMana(-13);
			dmg += 1;
			if (m_animationRect->x >= 1000 && m_animationRect->x <= 1400)
			{
				m_skillCooldown[2] = true;
			}
		}
	}
}

bool Mage::getMenuActive()
{
	return m_ih->m_menuActive;
}

void Mage::turnOffMenu()
{
	m_ih->m_menuActive = false;
}