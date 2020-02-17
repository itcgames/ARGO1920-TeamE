#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";

PlayState::PlayState(Vector2 &t_screenDimensions,GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
}


void PlayState::update()
{
	m_player.update();
	//std::cout << "Mini Map Position: " << m_miniMap->x << " " << m_miniMap->y << " Camera Position: " << camera->x << " " << camera->y << std::endl;
	camera->x = m_player.getPosition().x + 50 - camera->w / 2;
	camera->y = m_player.getPosition().y + 50 - camera->h / 2;

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

	//for (int i = 0; i < 2; i++)
	//{
	//	m_enemies[i]->update(m_player.getPosition());
	//	
	//	if (m_cs->aabbCollision(m_player.m_positionRect, m_enemies[i]->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
	//	{
	//		m_cs->collisionResponse(m_player.getEntity(), m_enemies[i]->getEntity());
	//		m_enemies[i]->setAttackTime(0);
	//	}
	//}

	m_pickUp->update();

	for (int i = 0; i < myMap->map.size(); i++)
	{
		for (int z = 0; z < myMap->map[i]->tileList.size(); z++)
		{
			if (myMap->map[i]->tileList[z]->getTag() == "Wall")
			{
				//m_cs->wallCollisionResponse(m_player.getEntity(), myMap->map[i]->tileList[z]->getEntity());
				if (m_cs->aabbCollision(m_player.m_positionRect, myMap->map[i]->tileList[z]->getEntity()->getComponent<SpriteComponent>(2)->getRect()) == true)
				{
					m_cs->wallCollisionResponse(m_player.getEntity(), myMap->map[i]->tileList[z]->getEntity());
					std::cout << "Hit" << std::endl;
 					//m_player.setSeek(false);
				}
			}
		}
	}

	// Testing deleteEntity
	/*if (m_cs->aabbCollision(m_player.m_playerRect, m_pickUp->getRect()) == true)
	{
		m_player.getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
		m_rs->deleteEntity(m_player.getEntity());
	}*/

	//m_cs->pickupCollisionResponse(m_player.getEntity(), m_pickUp->getEntity());


}

void PlayState::render()
{
	/* Creating the surface. */

	//m_rs->render(Render::Instance()->getRenderer());
//	SDL_SetRenderDrawColor(Render::Instance()->getRenderer(), 0, 255, 0, 255);

//	SDL_RenderFillRect(Render::Instance()->getRenderer(), camera);

	m_rs->renderPlayState(
		Render::Instance()->getRenderer(),
		camera,
		m_miniMap,
		m_miniMapTexture);
	//m_rs->render(Render::Instance()->getRenderer());
		//Vector2(m_player.getPosition().x - camera->x, m_player.getPosition().y - camera->y));
	//SDL_RenderSetViewport(Render::Instance()->getRenderer(), m_viewRect);

	//m_player.render();
}

/// handle user and system events/ input
void PlayState::processEvents(bool &isRunning)
{
	m_player.processEvents(isRunning);

	/*SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			m_stateMachine->changeState(new EndState(m_cameraDimensions, m_stateMachine));
		}
	}*/
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
	m_rs = new RenderSystem();
	m_cs = new CollisionSystem();

	camera = new SDL_Rect();
	camera->w = m_cameraDimensions.x;
	camera->h = m_cameraDimensions.y;
	camera->x = 0;
	camera->y = 0;

	level = new SDL_Rect();
	level->w = 4000;
	level->h = 4000;
	level->x = 0;
	level->y = 0;

	m_miniMap = new SDL_Rect();
	m_miniMap->w = m_cameraDimensions.x / 10;
	m_miniMap->h = m_cameraDimensions.y / 10;
	m_miniMap->x = m_cameraDimensions.x - m_miniMap->w;
	m_miniMap->y = m_cameraDimensions.y - m_miniMap->h;

	myMap = new Map(m_rs, m_cs);
	myMap->CreateMap(m_rs, m_cs);	
	Vector2 temp = { 400, 400 };
	for (int i = 0; i < 2; i++)
	{
		m_enemies.push_back(new Ai);
		m_enemies[i]->initialize(m_rs, temp, data::Instance()->getData().m_presets.m_stats.at(i).m_class, data::Instance()->getData().m_presets.m_stats.at(i).m_health,
			data::Instance()->getData().m_presets.m_stats.at(i).m_strength, data::Instance()->getData().m_presets.m_stats.at(i).m_speed,
			data::Instance()->getData().m_presets.m_stats.at(i).m_gold, data::Instance()->getData().m_presets.m_stats.at(i).m_killCount);
		temp = {600, 800};
	}

	m_pickUp->initialize(m_rs, "Health", true, false, false);
	m_player.init(m_rs, camera, myMap->map.at(0)->getCenterPos());


	SDL_Surface* miniMapSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_miniMapTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), miniMapSurface);

	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}