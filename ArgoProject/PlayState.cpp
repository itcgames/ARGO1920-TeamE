#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";


void PlayState::update()
{
	m_player.update();
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
	m_player.init(m_rs);
	m_enemy.initialize(m_rs);
	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}