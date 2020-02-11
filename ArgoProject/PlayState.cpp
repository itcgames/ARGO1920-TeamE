#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";

PlayState::PlayState(Vector2 t_screenDimensions)
{
	m_cameraDimensions = t_screenDimensions;
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

	//m_miniMap->x = camera->x + camera->w - m_miniMap->w;
	//m_miniMap->y = camera->y + camera->h - m_miniMap->h;

	m_enemy->update(m_player.getPosition());

	m_cs->collisionResponse(m_player.getEntity(), m_enemy->getEntity());

	for (int i = 0; i < myMap->map.size(); i++)
	{
		for (int z = 0; z < myMap->map.at(i).tileList.size(); z++)
		{
			if (myMap->map.at(i).tileList.at(z)->getTag() == "Wall")
			{
				//m_cs->wallCollisionResponse(m_player.getEntity(), myMap->map.at(i).tileList.at(z)->getEntity());
			}
		}
	}
}

void PlayState::render()
{
	//m_rs->render(Render::Instance()->getRenderer());
	/* Creating the surface. */

	//m_rs->render(Render::Instance()->getRenderer());
//	SDL_SetRenderDrawColor(Render::Instance()->getRenderer(), 0, 255, 0, 255);

//	SDL_RenderFillRect(Render::Instance()->getRenderer(), camera);

	m_rs->renderPlayState(
		Render::Instance()->getRenderer(),
		camera,
		m_miniMap,
		m_miniMapTexture,
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
	m_player.init(m_rs, camera,myMap->map.at(0).getCenterPos());
	m_enemy->initialize(m_rs);

	SDL_Surface* miniMapSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_miniMapTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), miniMapSurface);

	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}