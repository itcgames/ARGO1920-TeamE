#include "MenuState.h"

const std::string MenuState::m_menuID = "MENU";

void MenuState::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 9));

}

void MenuState::render()
{
	MyTextureManager::Instance()->DrawFrame("animate", 100, 100, 80, 140, 3, m_currentFrame);
}

bool MenuState::onEnter()
{
	MyTextureManager::Instance()->Load("Assets/char.png", "animate");

	std::cout << "Entering Menu State\n";
	return true;
}

bool MenuState::onExit()
{

	std::cout << "Exiting Menu State\n";
	return true;
}
