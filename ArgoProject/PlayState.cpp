#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";


void PlayState::update()
{
	//nothing
}

void PlayState::render()
{
	MyTextureManager::Instance()->Draw("animate", 0, 0, 80, 140);
}

bool PlayState::onEnter()
{
	MyTextureManager::Instance()->Load("Assets/char.png", "animate");
	std::cout << "Entering Play State\n";
	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting Play State\n";
	return true;
}
