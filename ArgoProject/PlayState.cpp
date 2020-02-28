#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";

PlayState::PlayState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
	m_background = new Audio();
	m_background->load("Assets/Audio/Background.wav");
}


void PlayState::update()
{
	//See's if the game has been Paused ( If Not )
	if (m_player->getMenuActive() == false)
	{
		//Updates()
			// Player 
		m_player->update();

		//HUD 
		m_hud->update(m_player->getEntity()->getComponent<HealthComponent>(5)->getHealth(), m_player->getEntity()->getComponent<ManaComponent>(7)->getMana());

		//Pickups
		if (m_player->getEntity()->getComponent<HealthComponent>(4)->getHealth() <= 150)
		{
			for (int i = 0; i < m_pickUp.size(); i++)
			{
				m_pickUp.at(i)->update();

				if (m_cs->aabbCollision(m_player->getRect(), m_pickUp.at(i)->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
				{
					m_cs->pickupCollisionResponse(m_player->getEntity(), m_pickUp.at(i)->getEntity());
					m_pickUp[i]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
					m_rs->deleteEntity(m_pickUp.at(i)->getEntity());
					m_cs->deleteEntity(m_pickUp.at(i)->getEntity());
					delete m_pickUp[i];
					m_pickUp.erase(m_pickUp.begin() + i);
				}
			}
		}


		m_miniMapList = m_rs->m_miniMapList;
		//Calls All the games Collisions
		collisions();


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

		m_hud->update(m_player->getEntity()->getComponent<HealthComponent>(5)->getHealth(), m_player->getEntity()->getComponent<ManaComponent>(7)->getMana());

		if (m_player->m_killCount == 15)
		{
			if (bossSpawned == false)
			{
				//Boss enemy setup here
				m_enemies.push_back(FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_BOSS));
				m_enemies.back()->initialize(m_rs, myMap->map.back()->getCenterPos(), data::Instance()->getData().m_presets.m_stats.at(3).m_class, data::Instance()->getData().m_presets.m_stats.at(3).m_health,
					data::Instance()->getData().m_presets.m_stats.at(3).m_strength, data::Instance()->getData().m_presets.m_stats.at(3).m_speed,
					data::Instance()->getData().m_presets.m_stats.at(3).m_gold, data::Instance()->getData().m_presets.m_stats.at(3).m_killCount);

				m_enemies.back()->setRoom(myMap->map.size() - 1);

				message.push_back(new PopUpText(Abel, "Skeleton King Has Spawned!!", 500, 450,120));

				bossSpawned = true;
			}
		}

		if (m_player->getHealth() <= 0)
		{
			m_stateMachine->changeState(new LoadState(m_cameraDimensions, m_stateMachine));
		}
		//|| m_player->m_killCount == 11

		for (int i = 0; i < message.size(); i++)
		{
			if (message[i]->m_text != nullptr)
			{
				message[i]->update();
			}
			else
			{
				message.erase(message.begin() + i);
			}
			std::cout << message.size() << std::endl;
		}

	}
	else
	{
		m_miniMapList;
		std::cout << "";
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

	if (m_player->getMenuActive() == true)
	{
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_menuBackgroundTexture, NULL, m_menuBackground);
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_playOptionTexture, NULL, m_playOption);
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_exitOptionTexture, NULL, m_exitOption);
	}
	for (int i = 0; i < message.size(); i++)
	{
		if (message[i] != nullptr)
		{
			message[i]->render();
		}
	}
}

/// handle user and system events/ input
void PlayState::processEvents(bool& isRunning)
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

	MenuInit();
	cameraSetup();

	// Ratio of map to World Size
	Vector2 miniMapRatio = Vector2(level->w / m_miniMap->w, level->h / m_miniMap->h);

	//Creates the Systems
	m_rs = new RenderSystem(Render::Instance()->getRenderer(), miniMapRatio);
	m_cs = new CollisionSystem();
	m_bts = new BehaviourTreeSystem();

	//Creates the Map
	myMap = new Map(m_rs, m_cs);
	myMap->CreateMap(m_rs, m_cs);


	// Create Enemies 
	for (int i = 0; i < 10; i++)
	{
		int tempRandPos = GenerateRandomNumber(1, myMap->map.size() - 1); // Random room inside the map
		int randomEnemyPreset = rand() % 3; // Random Number to find the type of enemy to spawn

		if (randomEnemyPreset == 0)
		{
			m_enemies.push_back(FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_EASY));
		}
		if (randomEnemyPreset == 1)
		{
			m_enemies.push_back(FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_MEDIUM));
		}
		if (randomEnemyPreset == 2)
		{
			m_enemies.push_back(FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_HARD));
		}

		//Init the enemy based of the above condition that was met
		m_enemies[i]->initialize(m_rs, myMap->map[tempRandPos]->disperse(), data::Instance()->getData().m_presets.m_stats.at(randomEnemyPreset).m_class, data::Instance()->getData().m_presets.m_stats.at(randomEnemyPreset).m_health,
			data::Instance()->getData().m_presets.m_stats.at(randomEnemyPreset).m_strength, data::Instance()->getData().m_presets.m_stats.at(randomEnemyPreset).m_speed,
			data::Instance()->getData().m_presets.m_stats.at(randomEnemyPreset).m_gold, data::Instance()->getData().m_presets.m_stats.at(randomEnemyPreset).m_killCount);

		//Sets the room that the enemy is placed in.
		m_enemies[i]->setRoom(tempRandPos);
	}

	// Create Pickups
	for (int i = 0; i < 20; i++)
	{
		int tempRandPos = GenerateRandomNumber(1, myMap->map.size() - 1);
		int randomPickupPreset = rand() % 3;
		m_pickUp.push_back(new PickUp);
		if (randomPickupPreset == 0)
		{
			m_pickUp.at(i)->initialize(m_rs, "Health", true, false, false, myMap->map[tempRandPos]->disperse());
		}
		if (randomPickupPreset == 1)
		{
			m_pickUp.at(i)->initialize(m_rs, "Health", false, true, false, myMap->map[tempRandPos]->disperse());
		}
		if (randomPickupPreset == 2)
		{
			m_pickUp.at(i)->initialize(m_rs, "Health", false, false, true, myMap->map[tempRandPos]->disperse());
		}
	}

	//Creates the Player
	if (data::Instance()->getData().m_playerStats.at(0).m_class == "PLAYER_WARRIOR")
	{
		m_player = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_WARRIOR);
		className = "Warrior";
	}
	else if (data::Instance()->getData().m_playerStats.at(0).m_class == "PLAYER_KNIGHT")
	{
		m_player = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_KNIGHT);
		className = "Knight";
	}
	else
	{
		m_player = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_MAGE);
		className = "Mage";
	}
	//m_player = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_WARRIOR);
	m_player->init(m_rs, camera, myMap->map[0]->getCenterPos());

	m_hud = new HUD(m_cameraDimensions,
		m_player->getEntity()->getComponent<HealthComponent>(5)->getOriginalHealth(), m_player->getEntity()->getComponent<ManaComponent>(7)->getOriginalMana(),
		m_player->m_skillCooldown[0], m_player->m_skillCooldown[1], m_player->m_skillCooldown[2],
		m_player->m_killCount,
		className);

	//Play Background Music
	m_background->play();


	for (int i = 0; i < 1; i++)
	{
		int tempRandPos = GenerateRandomNumber(1, myMap->map.size() - 1);

		int randomEnemyPreset = rand() % 3;

		m_btEnemy.push_back(FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_EASY));

		//@ALEX HERE 
		m_btEnemy[i]->initialize(m_rs, m_player->getPosition(), "BT", 100, 100, 100, 100, 0);

		m_btEnemy[i]->setRoom(tempRandPos);
	}

	m_miniMapList = m_rs->m_miniMapList;

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	Abel = TTF_OpenFont("Assets/Font/CopperPlateGothicBold.ttf", m_cameraDimensions.y / 20);

	if (!Abel) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}


	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";

	LevelLoader::writeToPlayer(m_player->getEntity()->getComponent<StatsComponent>(4)->getClass(), 200, 200/*m_player->getEntity()->getComponent<StatsComponent>(4)->getHealth()*/, m_player->getEntity()->getComponent<StatsComponent>(4)->getSpeed(), 0, m_player->m_killCount);
	LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", m_data);
	data::Instance()->setUpData(m_data);

	SDL_DestroyTexture(m_miniMapTexture);
	SDL_DestroyTexture(m_menuBackgroundTexture);
	SDL_DestroyTexture(m_playOptionTexture);
	SDL_DestroyTexture(m_exitOptionTexture);

	m_rs->clearMap();

	m_hud->onExit();
	delete m_background;
	//m_player->~IPlayer();
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
	level->w = 18000;
	level->h = 13000;
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
	for (int i = 0; i < 1; i++)
	{
		m_bts->run(m_btEnemy[i]->getEntity());
	}

	for (int i = 0; i < m_miniMapList.size(); i++)
	{
		if (m_miniMapList[i]->getID() == 0)
		{
			if (m_cs->aabbCollision(m_player->getRect(), m_miniMapList[i]->getComponent<SpriteComponent>(2)->getRect()) == true)
			{
				m_player->setTargetPosition(m_player->getPosition());
				m_cs->wallCollisionResponse(m_player->getEntity(), m_miniMapList[i]);

			}
		}

		if (m_miniMapList[i]->getID() == 1)
		{
			bool onMap = false;
			for (int j = 0; j < m_miniMapList.size(); j++)
			{
				if (m_miniMapList[j]->getID() == 0 || m_miniMapList[j]->getID() == -1)
				{
					if (m_cs->aabbCollision(m_player->getRect(), m_miniMapList[j]->getComponent<SpriteComponent>(2)->getRect()) == true)
					{
						onMap = true;
					}
				}
			}
			if (!onMap)
			{
				m_player->getEntity()->getComponent<HealthComponent>(5)->alterHealth(-0.5f);
			}
		}

		//Collision with enemy and player
		if (m_miniMapList[i]->getID() == 2)
		{
			if (m_cs->aabbCollision(m_player->getRect(), m_miniMapList[i]->getComponent<SpriteComponent>(2)->getRect()) == true)
			{
				if (m_miniMapList[i]->getComponent<HealthComponent>(5)->getHealth() > 0)
				{
					//player attacking enemy function
					float temp = m_miniMapList[i]->getComponent<HealthComponent>(5)->getHealth();

					if (m_player->m_mc->getMana() > 0)
					{
						m_player->Attack(temp);
					}

					m_miniMapList[i]->getComponent<HealthComponent>(5)->setHealth(temp);
					//update kill count when enemy dead

					m_player->setSeek(false);

					for (int j = 0; j < m_enemies.size(); j++)
					{
						if (m_miniMapList[i] == m_enemies[j]->getEntity())
						{
							m_enemies[j]->setSeek(false);
						}
					}

					m_player->setTargetPosition(m_player->getPosition());
					m_cs->collisionResponse(m_player->getEntity(), m_miniMapList[i], m_player->getSeek());
					//m_enemies[i]->setAttackTime(0);
				}
				if (m_miniMapList[i]->getComponent<HealthComponent>(5)->getHealth() <= 0)
				{
					if (m_miniMapList[i]->getComponent<ActiveComponent>(6)->getIsActive())
					{
						m_player->m_killCount++;
						enemyKilledMessageSort(m_miniMapList[i]->getComponent<StatsComponent>(4)->getClass());
						message.push_back(new PopUpText(Abel, "+ 1", 1400, 1000, 100));

					}
					m_player->getEntity()->getComponent<StatsComponent>(4)->setKillCount(m_player->getEntity()->getComponent<StatsComponent>(4)->getkillCount() + 1);
					m_rs->deleteEntity(m_miniMapList[i]);
					m_cs->deleteEntity(m_miniMapList[i]);
				}
			}
			else
			{
				m_player->m_mc->alterMana(1.0f);
			}
			for (int j = 0; j < m_enemies.size(); j++)
			{
				if (m_miniMapList[i] == m_enemies[j]->getEntity())
				{
					m_enemies[j]->update(m_player->getPosition());
				}
			}
			for (int j = 0; j < m_miniMapList.size(); j++)
			{
				if (m_miniMapList[j]->getID() == 0)
				{
					if (m_cs->aabbCollision(m_miniMapList[i]->getComponent<SpriteComponent>(2)->getRect(), m_miniMapList[j]->getComponent<SpriteComponent>(2)->getRect()) == true)
					{
						m_cs->wallCollisionResponse(m_miniMapList[i], m_miniMapList[j]);
					}
				}
			}
		}

		if (m_miniMapList[i]->getID() == 3)
			{
				if (m_cs->aabbCollision(m_player->getRect(), m_miniMapList[i]->getComponent<SpriteComponent>(2)->getRect()) == true)
				{
					m_cs->pickupCollisionResponse(m_player->getEntity(), m_miniMapList[i]);
				}
			}
		}

	}

void PlayState::MenuInit()
{
	SDL_Surface* playStateSurface = IMG_Load("Assets/minimapBackground.png");
	m_miniMapTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playStateSurface);

	/// Initialise Menu
	m_menuActive = false;

	m_menuBackground = new SDL_Rect();
	m_menuBackground->x = 0;
	m_menuBackground->y = 0;
	m_menuBackground->w = m_cameraDimensions.x;
	m_menuBackground->h = m_cameraDimensions.y;

	playStateSurface = IMG_Load("Assets/Button.png");
	m_menuBackgroundTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playStateSurface);
	SDL_SetTextureBlendMode(m_menuBackgroundTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_menuBackgroundTexture, 125);

	m_playOption = new SDL_Rect();
	m_playOption->x = m_cameraDimensions.x * 0.25;
	m_playOption->y = m_cameraDimensions.y * 0.1;
	m_playOption->w = m_cameraDimensions.x * 0.5;
	m_playOption->h = m_cameraDimensions.y * 0.3;

	playStateSurface = IMG_Load("Assets/ResumeButton.png");
	m_playOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playStateSurface);

	m_exitOption = new SDL_Rect();
	m_exitOption->x = m_cameraDimensions.x * 0.25;
	m_exitOption->y = m_cameraDimensions.y * 0.6;
	m_exitOption->w = m_cameraDimensions.x * 0.5;
	m_exitOption->h = m_cameraDimensions.y * 0.3;

	playStateSurface = IMG_Load("Assets/QuitButton.png");
	m_exitOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playStateSurface);


	SDL_FreeSurface(playStateSurface);
}

double PlayState::GenerateRandomNumber(double min, double max)
{
	std::random_device m_randDev;
	std::mt19937 mt(m_randDev());
	std::uniform_real_distribution<double> dist(min, max);
	return dist(mt);
}

void PlayState::enemyKilledMessageSort(std::string type)
{
	if (type == "ENEMY_EASY")
	{
		message.push_back(new PopUpText(Abel, "Lesser Zombie Killed!", 50, 50 * message.size(), 80));
	}

	if (type == "ENEMY_MEDIUM")
	{
		message.push_back(new PopUpText(Abel, "Zombie Killed!", 50, 50 * message.size(), 80));
	}

	if (type == "ENEMY_HARD")
	{
		message.push_back(new PopUpText(Abel, "Elite Zombie Killed!", 50, 50 * message.size(), 80));
	}

	if (type == "ENEMY_BOSS")
	{
		message.push_back(new PopUpText(Abel, "SKELETON KING ELIMINATED", 1500, 1000, 100));
	}
}
