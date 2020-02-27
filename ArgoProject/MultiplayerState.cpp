#include "MultiplayerState.h"

const std::string MultiplayerState::m_playID = "MULTIPLAY";

MultiplayerState::MultiplayerState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
	m_background.load("Assets/Audio/Background.wav");
}


void MultiplayerState::update()
{
	if (!data::Instance()->HOST)
	{
		if (!mapMade)
		{
			std::string temp = m_client.vec1[0];
			std::cout << temp.back();
			if (temp[temp.back()] != '0')
			{
				for (int i = 0; i < myMap->map.size(); i++)
				{
					for (int y = 0; y < myMap->map[i]->tileList.size(); y++)
					{
						myMap->map[i]->tileList[y]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);

						m_rs->deleteEntity(myMap->map[i]->tileList[y]->getEntity());
						if (myMap->map[i]->tileList[y]->getEntity()->getID() == 0)
						{
							m_cs->deleteEntity(myMap->map[i]->tileList[y]->getEntity());
						}
						myMap->map[i]->tileList.erase(myMap->map[i]->tileList.begin() + y);
					}
				}

				for (int i = 0; i < myMap->path.size(); i++)
				{
					myMap->path[i]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);

					m_rs->deleteEntity(myMap->path[i]->getEntity());
					if (myMap->path[i]->getEntity()->getID() == 0)
					{
						m_cs->deleteEntity(myMap->path[i]->getEntity());
					}
					myMap->path.erase(myMap->path.begin() + i);
				}
			}
			else
			{

				{
					if (m_client.vec1.size() > 1)
					{
						mapDataRecString = m_client.vec1[1];
						ParseMapData();
						//m_client.vec1.clear();
						mapMade = true;
					}
				}
			}
		}
	}
	//See's if the game has been Paused ( If Not )
	if (m_player->getMenuActive() == false)
	{
		//Updates()
			// Player 
		m_player->update();
		m_player2->update();
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

		////if its multiplayer
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
				Vector2 tempPos = m_player->getEntity()->getComponent<PositionComponent>(1)->getPosition();
				std::string test = std::to_string(static_cast<int>(tempPos.x));
				std::string test2 = std::to_string((int)tempPos.y);
				test += ",";
				test += test2;
				m_client.SendString(test);
				//m_client.SendString(test2);
			}
			if (m_client.vec.size() > 0)
			{
				std::string temp = m_client.vec[0];
				std::cout << "recv test" << std::endl;
				std::string sub = "";
				std::string sub2 = "";
				float x = 0;
				float y;
				int pos = temp.find(",");
				if (pos > -1)
				{
					// Copy substring after pos 
					std::string sub2 = temp.substr(pos + 1);
					for (int i = 0; i < pos; i++)
					{
						sub += temp[i];
					}
					// prints the result 
					std::cout << "x: " << sub << " , " << "y: " << sub2 << std::endl;
					std::stringstream stream1(sub);
					std::stringstream stream2(sub2);
					stream1 >> x;
					stream2 >> y;
					Vector2 pos{ x, y };
					m_player2->getEntity()->getComponent<PositionComponent>(1)->setPosition(pos);
				}
				std::cout << std::endl;
				std::cout << "==============================================" << std::endl;
			}
		}

		m_hud->update(m_player->getEntity()->getComponent<HealthComponent>(5)->getHealth(), m_player->getEntity()->getComponent<ManaComponent>(7)->getMana());

		if (m_player->m_killCount == 10)
		{
			if (bossSpawned == false)
			{
				//Boss enemy setup here
				m_enemies.push_back(FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_BOSS));
				m_enemies.back()->initialize(m_rs, myMap->map.back()->getCenterPos(), data::Instance()->getData().m_presets.m_stats.at(3).m_class, data::Instance()->getData().m_presets.m_stats.at(3).m_health,
					data::Instance()->getData().m_presets.m_stats.at(3).m_strength, data::Instance()->getData().m_presets.m_stats.at(3).m_speed,
					data::Instance()->getData().m_presets.m_stats.at(3).m_gold, data::Instance()->getData().m_presets.m_stats.at(3).m_killCount);

				m_enemies.back()->setRoom(myMap->map.size() - 1);

				bossSpawned = true;
			}
		}

		if (m_player->getHealth() <= 0 || m_player->m_killCount == 11)
		{
			m_stateMachine->changeState(new EndState(m_cameraDimensions, m_stateMachine));
		}

	}
	else
	{
		m_miniMapList;
		std::cout << "";
	}
}


void MultiplayerState::render()
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
}

/// handle user and system events/ input
void MultiplayerState::processEvents(bool& isRunning)
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

bool MultiplayerState::onEnter()
{
	std::cout << "Entering Play State\n";
	// Sets the Host or Connects the client to the host game
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
	m_player->init(m_rs, camera, Vector2(1200, 900));

	if (!data::Instance()->SINGLEPLAYER)
	{
		m_player2 = FactoryPlayer::createPlayer(FactoryPlayer::PLAYER_WARRIOR);
		m_player2->init(m_rs, camera, Vector2(1000, 800));
	}
	m_hud = new HUD(m_cameraDimensions,
		m_player->getEntity()->getComponent<HealthComponent>(5)->getOriginalHealth(), m_player->getEntity()->getComponent<ManaComponent>(7)->getOriginalMana(),
		m_player->m_skillCooldown[0], m_player->m_skillCooldown[1], m_player->m_skillCooldown[2],
		m_player->m_killCount,
		className);

	//Play Background Music
	m_background.play();


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
	
	for (int i = 0; i < myMap->mapInfo.size(); i++)
	{
		sendMap += std::to_string((int)myMap->mapInfo[i]->getComponent<PositionComponent>(1)->getPosition().x) + ",";
		sendMap += std::to_string((int)myMap->mapInfo[i]->getComponent<PositionComponent>(1)->getPosition().y) + ",";
		sendMap += std::to_string((int)myMap->mapInfo[i]->getID()) + "," + "|";
	}
	m_client.SendString(sendMap);
	//mapDataRecString = m_client.vec1[1];
	//std::cout << "recv test" << std::endl;
	std::cout << "size = " << mapDataRecString.size() << std::endl;
	std::cout << "_____________________________________________" << std::endl;
	std::cout << mapDataRecString << std::endl;
	std::cout << "_____________________________________________" << std::endl;

	
	//ParseMapData();
	return true;
}

bool MultiplayerState::onExit()
{
	std::cout << "Exiting Play State\n";
	SDL_DestroyTexture(m_miniMapTexture);
	SDL_DestroyTexture(m_menuBackgroundTexture);
	SDL_DestroyTexture(m_playOptionTexture);
	SDL_DestroyTexture(m_exitOptionTexture);

	m_rs->clearMap();

	m_hud->onExit();

	//delete m_pSystem;
	//delete m_rs;

	return true;
}

void MultiplayerState::cameraSetup()
{
	camera = new SDL_Rect();
	camera->w = m_cameraDimensions.x;
	camera->h = m_cameraDimensions.y;
	camera->x = 0;
	camera->y = 0;

	level = new SDL_Rect();
	level->w = 18000;
	level->h = 12000;
	level->x = 0;
	level->y = 0;

	m_miniMap = new SDL_Rect();
	m_miniMap->w = m_cameraDimensions.x / 5;
	m_miniMap->h = m_cameraDimensions.y / 5;
	m_miniMap->x = m_cameraDimensions.x - m_miniMap->w;
	m_miniMap->y = m_cameraDimensions.y - m_miniMap->h;
}

void MultiplayerState::collisions()
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
			if (m_enemies[i]->getEntity()->getComponent<HealthComponent>(5)->getHealth() <= 0)
			{
				if (m_enemies[i]->getEntity()->getComponent<ActiveComponent>(6)->getIsActive())
				{
					m_player->m_killCount++;
					data::Instance()->playerScore = m_player->m_killCount;
				}
				m_player->getEntity()->getComponent<StatsComponent>(4)->setKillCount(m_player->getEntity()->getComponent<StatsComponent>(4)->getkillCount() + 1);
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

	for (int i = 0; i < 1; i++)
	{
		m_bts->run(m_btEnemy[i]->getEntity());
	}

	/*for (int i = 0; i < m_pickUp.size(); i++)
	{
		if (m_cs->aabbCollision(m_player->getRect(), m_pickUp.at(i)->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
		{
			m_cs->pickupCollisionResponse(m_player->getEntity(), m_pickUp.at(i)->getEntity());
		}
	}*/

	/*for (int i = 0; i < myMap->map.size(); i++)
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
	for (int i = 0; i < myMap->path.size(); i++)
	{
			if (myMap->path[i]->getTag() == "Wall")
			{
				if (m_cs->aabbCollision(m_player->getRect(), myMap->path[i]->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
				{
					m_player->setTargetPosition(m_player->getPosition());
					m_cs->wallCollisionResponse(m_player->getEntity(), myMap->path[i]->getEntity());
				}
			}
	}*/

	for (int y = 0; y < m_enemies.size(); y++)
	{
		for (int z = 0; z < myMap->map[m_enemies[y]->getRoom()]->tileList.size(); z++)
		{
			if (myMap->map[m_enemies[y]->getRoom()]->tileList[z]->getTag() == "Wall")
			{
				if (m_cs->aabbCollision(m_enemies[y]->getEntity()->getComponent<SpriteComponent>(2)->getRect(), myMap->map[m_enemies[y]->getRoom()]->tileList[z]->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
				{
					m_cs->wallCollisionResponse(m_enemies[y]->getEntity(), myMap->map[m_enemies[y]->getRoom()]->tileList[z]->getEntity());
				}
			}
		}
	}

	//for (int y = 0; y < m_enemies.size(); y++)
	//{
	//	for (int i = 0; i < myMap->path.size(); i++)
	//	{
	//		if (m_cs->aabbCollision(m_enemies[y]->getEntity()->getComponent<SpriteComponent>(2)->getRect(), myMap->path[i]->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
	//		{
	//			m_cs->wallCollisionResponse(m_enemies[y]->getEntity(), myMap->path[i]->getEntity());
	//		}
	//	}
	//}
	//m_cs->pickupCollisionResponse(m_player->getEntity(), m_pickUp->getEntity());

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
					}
					m_player->getEntity()->getComponent<StatsComponent>(4)->setKillCount(m_player->getEntity()->getComponent<StatsComponent>(4)->getkillCount() + 1);
					m_rs->deleteEntity(m_miniMapList[i]);
					m_cs->deleteEntity(m_miniMapList[i]);
				}
			}
			else
			{
				m_player->m_mc->alterMana(0.1f);
			}

			/*	for (int j = 0; j < m_enemies.size(); j++)
				{
					if (m_miniMapList[i] == m_enemies[j]->getEntity())
					{
						m_enemies[j]->update(m_player->getPosition());
					}
				}*/
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

void MultiplayerState::MenuInit()
{
	SDL_Surface* playStateSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_miniMapTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playStateSurface);

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
	SDL_SetTextureAlphaMod(m_menuBackgroundTexture, 125);

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
}

double MultiplayerState::GenerateRandomNumber(double min, double max)
{
	std::random_device m_randDev;
	std::mt19937 mt(m_randDev());
	std::uniform_real_distribution<double> dist(min, max);
	return dist(mt);
}

void MultiplayerState::ParseMapData()
{
	bool done = false;
	std::string sub = "";
	std::string sub2 = "";
	std::string sub3 = "";
	float x = 0;
	float y;
	int id;
	int pos = mapDataRecString.find("|");
	bool xfound = false;
	bool yfound = false;
	bool idFound = false;
	while (!done)
	{
		if (pos >= 0)
		{
			//x,y,id | x,y,id |
			for (int i = 0; i < pos; i++)
			{
				if (mapDataRecString[0] != ',')
				{
					sub += mapDataRecString[0];
					mapDataRecString.erase(mapDataRecString.begin());
				}
				else
				{
					std::stringstream stream1(sub);
					if (xfound && yfound)
					{
						stream1 >> id;
						m_mapTileID.push_back(id);
						idFound = true;
					}
					if (!xfound)
					{
						stream1 >> x;
						m_mapX.push_back(x);
						xfound = true;
					}
					else if (!yfound)
					{
						stream1 >> y;
						m_mapY.push_back(y);
						yfound = true;
					}
					sub.clear();
					mapDataRecString.erase(mapDataRecString.begin());
				}
			}
		}
		else
		{
			done = true;
			break;
		}
		mapDataRecString.erase(mapDataRecString.begin()); // this will be '|'
		pos = mapDataRecString.find("|");
		xfound = false;
		yfound = false;
		idFound = false;

	}

	//if (pos > -1)
	//{
	//	// Copy substring after pos 
	//	//std::string sub2 = temp.substr(pos + 1);
	//	for (int i = 0; i < pos; i++)
	//	{
	//		if (mapDataRecString[i] != 44)
	//		{
	//			sub += mapDataRecString[i];
	//		}
	//	}
	//	// prints the result 
	//	std::cout << "x: " << sub << " , " << "y: " << sub2 << std::endl;
	//	std::stringstream stream1(sub);
	//	std::stringstream stream2(sub2);
	//	std::stringstream stream3(sub2);
	//	stream1 >> x;
	//	stream2 >> y;
	//	stream3 >> id;
	//}
}
