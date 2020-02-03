#include "PlayState.h"

const std::string PlayState::m_playID = "PLAY";


void PlayState::update()
{
	//nothing
}

void PlayState::render()
{
	MyTextureManager::Instance()->Draw("animate", 0, 0, 80, 140, playRender);
}

bool PlayState::onEnter(SDL_Renderer* t_renderer)
{
	playRender = t_renderer;
	MyTextureManager::Instance()->Load("Assets/char.png", "animate", playRender);

	std::cout << "Entering Play State\n";
	return true;
}

bool PlayState::onExit()
{
	playRender = nullptr;

	std::cout << "Exiting Play State\n";
	return true;
}
