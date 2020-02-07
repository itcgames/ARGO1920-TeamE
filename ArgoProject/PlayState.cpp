#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";


void PlayState::update()
{
	m_player.update();
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
	m_rs->render(Render::Instance()->getRenderer());
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
	myMap = new Map(m_rs,m_cs);
	myMap->CreateMap(m_rs,m_cs);
	m_player.init(m_rs);
	m_enemy->initialize(m_rs);

	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}