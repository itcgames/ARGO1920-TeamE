#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";

PlayState::PlayState(Vector2 &t_screenDimensions,GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
	m_background.load("Assets/Audio/Background.wav");
}


void PlayState::update()
{
	if (m_player->getMenuActive() == false)
	{
		collisions();

		m_player->update();
		//std::cout << "Mini Map Position: " << m_miniMap->x << " " << m_miniMap->y << " Camera Position: " << camera->x << " " << camera->y << std::endl;
		camera->x = m_player->getPosition().x + 50 - camera->w / 2;
		camera->y = m_player->getPosition().y + 50 - camera->h / 2;

		if (camera->x < 0)
		{
			camera->x = 0;
		}
		else if (camera->x > level->w - camera->w)
		{
			camera->x = level->w - camera->w;
		}
		if (camera->y < 0)
		{
			camera->y = 0;
		}
		else if (camera->y > level->h - camera->h)
		{
			camera->y = level->h - camera->h;
		}


		if (!m_player->getEntity()->getComponent<ActiveComponent>(6)->getIsActive())
		{
			m_stateMachine->changeState(new EndState(m_cameraDimensions, m_stateMachine));
		}

		m_cs->pickupCollisionResponse(m_player->getEntity(), m_pickUp->getEntity());

		//if its multiplayer
		if (!data::Instance()->SINGLEPLAYER)
		{
			//if you are the host send all positions to the client.
			if (data::Instance()->HOST)
			{
				//Vector2 tempPos = m_player.getEntity()->getComponent<PositionComponent>(1)->getPosition();
				//std::string test = std::to_string(tempPos.x);
				//std::string test2 = std::to_string(tempPos.y);
				//m_server.SendString(1,test);
				//m_server.SendString(2,test2);
			}
			//if you are not the host send your co-ordinates to the server.
			if (!data::Instance()->HOST)
			{
				Vector2 tempPos = m_player2->getEntity()->getComponent<PositionComponent>(1)->getPosition();
				std::string test = std::to_string(static_cast<int>(tempPos.x));
				std::string test2 = std::to_string((int)tempPos.y);
				m_client.SendString(test);
				m_client.SendString(test2);
			}
		}

		m_pickUp->update();

		m_pSystem->update();

		m_hud->update(m_player->getEntity()->getComponent<HealthComponent>(5)->getHealth(), m_player->getEntity()->getComponent<ManaComponent>(7)->getMana());
	}
}


void PlayState::render()
{
	m_rs->renderPlayState(
		Render::Instance()->getRenderer(),
		camera,
		m_miniMap,
		m_miniMapTexture,
		m_hud);

	m_pSystem->render();

	if (m_player->getMenuActive() == true)
	{
		SDL_RenderCopy(Render::Instance()->getRenderer(),m_menuBackgroundTexture,NULL,m_menuBackground);
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_playOptionTexture, NULL, m_playOption);
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_exitOptionTexture, NULL, m_exitOption);
	}
}

/// handle user and system events/ input
void PlayState::processEvents(bool &isRunning)
{
	if (m_player->getMenuActive() == false)
	{
		m_player->processEvents(isRunning);
	}
	else
	{
		SDL_Event event;

		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
					if (event.button.x > m_playOption->x && event.button.x <m_playOption->x + m_playOption->w
						&&
						event.button.y > m_playOption->y && event.button.y < m_playOption->y + m_playOption->h)
					{
						m_player->turnOffMenu();
					}
					else if (event.button.x > m_exitOption->x && event.button.x <m_exitOption->x + m_exitOption->w
						&&
						event.button.y > m_exitOption->y && event.button.y < m_exitOption->y + m_exitOption->h)
					{
						m_stateMachine->changeState(new MenuState(m_cameraDimensions, m_stateMachine));
					}
				
				break;
			default:
				break;
			}
		}
	}
}

bool PlayState::onEnter()
{
	std::cout << "Entering Play State\n";

	if (!data::Instance()->SINGLEPLAYER)
	{
		if (data::Instance()->HOST)
		{
			for (int i = 0; i < 1; i++)
			{
				m_server.ListenForNewConnection();
			}
		}
		else
		{
			m_client.Connect();
		}
	}

	cameraSetup();

	Vector2 miniMapRatio = Vector2(level->w / m_miniMap->w, level->h / m_miniMap->h);

	m_rs = new RenderSystem(Render::Instance()->getRenderer(), miniMapRatio);
	m_cs = new CollisionSystem();

	myMap = new Map(m_rs, m_cs);
	myMap->CreateMap(m_rs, m_cs);	
	Vector2 temp = { myMap->map[1]->getCenterPos() };
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			m_enemies.push_back(FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_EASY));
		}
		else
		{
			m_enemies.push_back(FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_MEDIUM));
		}		
		m_enemies[i]->initialize(m_rs, temp, data::Instance()->getData().m_presets.m_stats.at(i).m_class, data::Instance()->getData().m_presets.m_stats.at(i).m_health,
			data::Instance()->getData().m_presets.m_stats.at(i).m_strength, data::Instance()->getData().m_presets.m_stats.at(i).m_speed,
			data::Instance()->getData().m_presets.m_stats.at(i).m_gold, data::Instance()->getData().m_presets.m_stats.at(i).m_killCount);
		temp = { myMap->map[1]->getCenterPos() };
	}

	m_pickUp->initialize(m_rs, "Health", true, false, false);
	if (data::Instance()->getData().m_playerStats.at(0).m_class == "PLAYER_WARRIOR")
	{
		m_player = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_WARRIOR);
	}
	else if (data::Instance()->getData().m_playerStats.at(0).m_class == "PLAYER_KNIGHT")
	{
		m_player = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_KNIGHT);
	}
	else
	{
		m_player = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_MAGE);
	}
	//m_player = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_WARRIOR);
	m_player->init(m_rs, camera, myMap->map[0]->getCenterPos());

	if (!data::Instance()->SINGLEPLAYER)
	{
		m_player2 = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_WARRIOR);
		m_player2->init(m_rs, camera, Vector2(500, 500));
	}
	m_hud = new HUD(m_cameraDimensions, 
		m_player->getEntity()->getComponent<HealthComponent>(5)->getOriginalHealth(), m_player->getEntity()->getComponent<ManaComponent>(7)->getOriginalMana(),
		m_player->m_skillCooldown[0], m_player->m_skillCooldown[1], m_player->m_skillCooldown[2]);

	SDL_Surface* playStateSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_miniMapTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playStateSurface);


	m_pSystem =new ParticleSystem(m_playID, 500, Type::EXPLOSION);

	m_background.play();


	/// Initialise Menu
	m_menuActive = false;

	m_menuBackground = new SDL_Rect();
	m_menuBackground->x = 0;
	m_menuBackground->y = 0;
	m_menuBackground->w = m_cameraDimensions.x;
	m_menuBackground->h = m_cameraDimensions.y;

	playStateSurface = IMG_Load("Assets/Empty.png");
	m_menuBackgroundTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playStateSurface);
	SDL_SetTextureBlendMode(m_menuBackgroundTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_menuBackgroundTexture,125);

	m_playOption = new SDL_Rect();
	m_playOption->x = m_cameraDimensions.x * 0.25;
	m_playOption->y = m_cameraDimensions.y * 0.1;
	m_playOption->w = m_cameraDimensions.x * 0.5;
	m_playOption->h = m_cameraDimensions.y * 0.3;

	playStateSurface = IMG_Load("Assets/Empty.png");
	m_playOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playStateSurface);

	m_exitOption = new SDL_Rect();
	m_exitOption->x = m_cameraDimensions.x * 0.25;
	m_exitOption->y = m_cameraDimensions.y * 0.6;
	m_exitOption->w = m_cameraDimensions.x * 0.5;
	m_exitOption->h = m_cameraDimensions.y * 0.3;

	playStateSurface = IMG_Load("Assets/Empty.png");
	m_exitOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playStateSurface);


	SDL_FreeSurface(playStateSurface);
	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	SDL_DestroyTexture(m_miniMapTexture);
	SDL_DestroyTexture(m_menuBackgroundTexture);
	SDL_DestroyTexture(m_playOptionTexture);
	SDL_DestroyTexture(m_exitOptionTexture);

	m_rs->clearMap();

	m_hud->onExit();

	return true;
}

void PlayState::cameraSetup()
{
	camera = new SDL_Rect();
	camera->w = m_cameraDimensions.x;
	camera->h = m_cameraDimensions.y;
	camera->x = 0;
	camera->y = 0;

	level = new SDL_Rect();
	level->w = 12000;
	level->h = 12000;
	level->x = 0;
	level->y = 0;

	m_miniMap = new SDL_Rect();
	m_miniMap->w = m_cameraDimensions.x / 5;
	m_miniMap->h = m_cameraDimensions.y / 5;
	m_miniMap->x = m_cameraDimensions.x - m_miniMap->w;
	m_miniMap->y = m_cameraDimensions.y - m_miniMap->h;
}

void PlayState::collisions()
{
// Enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
			//Collision with enemy and player
			if (m_cs->aabbCollision(m_player->getRect(), m_enemies[i]->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
			{
				if (m_enemies[i]->getEntity()->getComponent<HealthComponent>(5)->getHealth() > 0)
				{
					//player attacking enemy function
					float temp = m_enemies[i]->getEntity()->getComponent<HealthComponent>(5)->getHealth();

					if (m_player->m_mc->getMana() > 0)
					{
						m_player->Attack(temp);
					}

					m_enemies[i]->getEntity()->getComponent<HealthComponent>(5)->setHealth(temp);
					//update kill count when enemy dead

					m_player->setSeek(false);
					m_enemies[i]->setSeek(false);
					m_player->setTargetPosition(m_player->getPosition());
					m_cs->collisionResponse(m_player->getEntity(), m_enemies[i]->getEntity(), m_player->getSeek());
					//m_enemies[i]->setAttackTime(0);
				}
				else
				{
					m_player->getEntity()->getComponent<StatsComponent>(4)->setKillCount(m_player->getEntity()->getComponent<StatsComponent>(4)->getkillCount() + 1);
					m_enemies[i]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
					m_rs->deleteEntity(m_enemies[i]->getEntity());
					m_cs->deleteEntity(m_enemies[i]->getEntity());
				}
			}
			else
			{
				m_player->m_mc->alterMana(0.1f);
			}
			m_enemies[i]->update(m_player->getPosition());

	}
	if (m_cs->aabbCollision(m_player->getRect(), m_pickUp->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
	{
		m_cs->pickupCollisionResponse(m_player->getEntity(), m_pickUp->getEntity());
	}

	for (int i = 0; i < myMap->map.size(); i++)
	{
		for (int z = 0; z < myMap->map[i]->tileList.size(); z++)
		{
			if (myMap->map[i]->tileList[z]->getTag() == "Wall")
			{
				if (m_cs->aabbCollision(m_player->getRect(), myMap->map[i]->tileList[z]->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
				{
					m_player->setTargetPosition(m_player->getPosition());
					m_cs->wallCollisionResponse(m_player->getEntity(), myMap->map[i]->tileList[z]->getEntity());
				}
			}
		}
	}

	m_cs->pickupCollisionResponse(m_player->getEntity(), m_pickUp->getEntity());
}
