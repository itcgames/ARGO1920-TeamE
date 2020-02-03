#include "MenuState.h"

const std::string MenuState::m_menuID = "MENU";

void MenuState::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 9));

}

void MenuState::render()
{
	MyTextureManager::Instance()->DrawFrame("animate", 100, 100, 80, 140, 3, m_currentFrame, menuRender);
}

bool MenuState::onEnter(SDL_Renderer *t_renderer)
{
	menuRender = t_renderer;
	MyTextureManager::Instance()->Load("Assets/char.png", "animate", menuRender);

	std::cout << "Entering Menu State\n";
	return true;
}

bool MenuState::onExit()
{
	menuRender = nullptr;

	std::cout << "Exiting Menu State\n";
	return true;
}
