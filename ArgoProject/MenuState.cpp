#include "MenuState.h"

const std::string MenuState::m_menuID = "MENU";

void MenuState::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 9));

}

void MenuState::render()
{
}

void MenuState::processEvents(bool isRunning)
{
}

bool MenuState::onEnter()
{

	std::cout << "Entering Menu State\n";
	return true;
}

bool MenuState::onExit()
{

	std::cout << "Exiting Menu State\n";
	return true;
}
