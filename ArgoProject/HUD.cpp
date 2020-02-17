#include "HUD.h"

HUD::HUD(Vector2 t_cameraDimension)
{
	m_background.w = t_cameraDimension.x * 0.8; m_background.h = t_cameraDimension.y * 0.1;
	m_background.x = 0; m_background.y = 0;

	m_health.w = t_cameraDimension.x * 0.25; m_health.h = 20;
	m_health.x = 0; m_health.y = 0;

	m_mana.w = t_cameraDimension.x * 0.25; m_mana.h = 20;
	m_mana.x = 0; m_mana.y = 0;

	SDL_Surface* healthSurface = IMG_Load("Assets/Health.png");
	m_healthtexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), healthSurface);
	//SDL_QueryTexture(m_healthtexture, NULL, NULL, &m_health.w, &m_health.h);
	SDL_FreeSurface(healthSurface);

	SDL_Surface* manaSurface = IMG_Load("Assets/Mana.png");
	m_manatexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), manaSurface);
	SDL_FreeSurface(manaSurface);

	SDL_Surface* hudSurface = IMG_Load("Assets/HUD.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), hudSurface);
	//SDL_QueryTexture(m_texture, NULL, NULL, &m_background.w, &m_background.h);
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
	m_viewableArea = { 0, 900, m_background.w, m_background.h };
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_texture, &m_background, &m_viewableArea);

	m_viewableArea = { 500, 910, 250, 20 };
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_healthtexture, &m_health, &m_viewableArea);

	m_viewableArea = { 500, 950, 250, 20 };
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_manatexture, &m_mana, &m_viewableArea);
}
