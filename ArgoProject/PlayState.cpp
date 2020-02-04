#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";


void PlayState::update()
{
	//nothing
}

void PlayState::render()
{
}

bool PlayState::onEnter()
{
	std::cout << "Entering Play State\n";
	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}
