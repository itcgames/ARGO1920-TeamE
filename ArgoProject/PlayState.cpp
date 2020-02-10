#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";

PlayState::PlayState(Vector2 t_screenDimensions)
{
	m_cameraDimensions = t_screenDimensions;
}


void PlayState::update()
{
	m_player.update();
	//std::cout << "Player Position: " << m_player.getPosition().x << " " << m_player.getPosition().y << "Camera Position: " << camera->x << " " << camera->y << std::endl;

	camera->x = m_player.getPosition().x + 50 - camera->w / 2;
	camera->y = m_player.getPosition().y + 50 - camera->h / 2;

	if (camera->x < 0)
	{
		camera->x = 0;
	}
	else if (camera->x > 2500 - camera->w)
	{
		camera->x = 2500 - camera->w;
	}
	if (camera->y < 0)
	{
		camera->y = 0;
	}
	else if (camera->y > 2000 - camera->h)
	{
		camera->y = 2000 - camera->h;
	}
	m_enemy->update(m_player.getPosition());

	m_cs->collisionResponse(m_player.getEntity(), m_enemy->getEntity());

	for (int i = 0; i < myMap->map.size(); i++)
	{
		for (int z = 0; z < myMap->map.at(i).tileList.size(); z++)
		{
			if (myMap->map.at(i).tileList.at(z)->getTag() == "Wall")
			{
				m_cs->wallCollisionResponse(m_player.getEntity(), myMap->map.at(i).tileList.at(z)->getEntity());
			}
		}
	}
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
		Vector2(m_player.getPosition().x - camera->x, m_player.getPosition().y - camera->y));
	//SDL_RenderSetViewport(Render::Instance()->getRenderer(), m_viewRect);
	
}

/// handle user and system events/ input
void PlayState::processEvents(bool isRunning)
{
	m_player.processEvents(isRunning);
}

bool PlayState::onEnter()
{
	std::cout << "Entering Play State\n";
	m_rs = new RenderSystem();
	m_cs = new CollisionSystem();

	camera = new SDL_Rect();
	camera->w = m_cameraDimensions.x;
	camera->h = m_cameraDimensions.y;
	camera->x = 0;
	camera->y = 0;

	level = new SDL_Rect();
	level->w = 2500;
	level->h = 2000;
	level->x = 0;
	level->y = 0;

	myMap = new Map(m_rs, m_cs);
	myMap->CreateMap(m_rs, m_cs);
	m_player.init(m_rs, camera,myMap->map.at(0).getCenterPos());

	m_enemy->initialize(m_rs);

	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}