#include "HUD.h"

HUD::HUD()
{
	m_background.h = 700; m_background.w = 100;
	m_background.x = 0; m_background.y = 0;

	m_health.h = 250; m_health.w = 20;
	m_health.x = 0; m_health.y = 0;

	m_mana.h = 10; m_mana.w = 10;
	m_mana.x = 0; m_mana.y = 0;

	SDL_Surface* healthSurface = IMG_Load("Assets/Health.png");
	m_healthtexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), healthSurface);
	SDL_QueryTexture(m_healthtexture, NULL, NULL, &m_health.w, &m_health.h);
	SDL_FreeSurface(healthSurface);

	SDL_Surface* manaSurface = IMG_Load("Assets/Mana.png");
	m_manatexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), manaSurface);
	SDL_FreeSurface(manaSurface);

	SDL_Surface* hudSurface = IMG_Load("Assets/HUD.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), hudSurface);
	SDL_QueryTexture(m_texture, NULL, NULL, &m_background.w, &m_background.h);
	SDL_FreeSurface(hudSurface);
}

HUD::~HUD()
{
}

void HUD::update()
{

}

void HUD::render()
{
	m_viewableArea = { -100, 900, 900, 100 };
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_texture, &m_background, &m_viewableArea);

	m_viewableArea = { 500, 910, 250, 20 };
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_healthtexture, &m_health, &m_viewableArea);

	m_viewableArea = { 500, 950, 250, 20 };
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_manatexture, &m_mana, &m_viewableArea);
}
