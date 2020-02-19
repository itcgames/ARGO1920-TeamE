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
	//Collisions
	for (int i = 0; i < 2; i++)
	{
		m_enemies[i]->update(m_player->getPosition());
		
		//collision with enemy and player
		if (m_cs->aabbCollision(m_player->getRect(), m_enemies[i]->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
		{
			//player attacking enemy function
			float temp = m_enemies[i]->getEntity()->getComponent<HealthComponent>(5)->getHealth();

			if (m_player->m_mc->getMana() > 0)
			{
				m_player->Attack(temp);
			}

			m_enemies[i]->getEntity()->getComponent<HealthComponent>(5)->setHealth(temp);
			//update kill count when enemy dead
			if (m_enemies[i]->getEntity()->getComponent<HealthComponent>(5)->getHealth() <= 0)
			{
				m_player->getEntity()->getComponent<StatsComponent>(4)->setKillCount(m_player->getEntity()->getComponent<StatsComponent>(4)->getkillCount() + 1);
			}
			
			m_player->setSeek(false);
			m_enemies[i]->setSeek(false);
			m_player->setTargetPosition(m_player->getPosition());
			m_cs->collisionResponse(m_player->getEntity(), m_enemies[i]->getEntity(), m_player->getSeek());
			
			//m_enemies[i]->setAttackTime(0);
		}
		else
		{
			m_player->m_mc->alterMana(0.1f);
		}

		if(m_cs->enemyCollisionResponse(m_player->getRect(), m_enemies[i]->getEntity(), m_player->getPosition()) == false)
		{
			m_enemies[i]->setSeek(true);
		}
	}

	m_pickUp->update();

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
					//std::cout << "Hit" << std::endl;

				}
			}
		}
	}

	m_cs->pickupCollisionResponse(m_player->getEntity(), m_pickUp->getEntity());

	if (!m_player->getEntity()->getComponent<ActiveComponent>(6)->getIsActive())
	{
		m_stateMachine->changeState(new EndState(m_cameraDimensions, m_stateMachine));
	}

	m_pSystem->update();

	m_hud->update(m_player->getEntity()->getComponent<HealthComponent>(5)->getHealth(), m_player->getEntity()->getComponent<ManaComponent>(7)->getMana());
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
}

/// handle user and system events/ input
void PlayState::processEvents(bool &isRunning)
{
	m_player->processEvents(isRunning);
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

	Vector2 miniMapRatio = Vector2(level->w / m_miniMap->w, level->h / m_miniMap->h);

	m_rs = new RenderSystem(Render::Instance()->getRenderer(), miniMapRatio);
	m_cs = new CollisionSystem();

	myMap = new Map(m_rs, m_cs);
	myMap->CreateMap(m_rs, m_cs);	
	Vector2 temp = { 1500, 1500 };
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
		temp = {1750, 1200};
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
	m_player->init(m_rs, camera, Vector2(350,350));

	m_hud = new HUD(m_cameraDimensions, m_player->getEntity()->getComponent<HealthComponent>(5)->getOriginalHealth(), m_player->getEntity()->getComponent<ManaComponent>(7)->getOriginalMana());

	SDL_Surface* miniMapSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_miniMapTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), miniMapSurface);


	m_pSystem =new ParticleSystem(m_playID, 1000, Type::EXPLOSION);

	m_background.play();

	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}