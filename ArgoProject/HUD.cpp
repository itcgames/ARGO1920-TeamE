#include "HUD.h"

HUD::HUD(Vector2 t_cameraDimension, float t_OriginalHealth)
{
	m_background.w = t_cameraDimension.x * 0.9; m_background.h = t_cameraDimension.y * 0.1;
	m_background.x = t_cameraDimension.x * -0.1; m_background.y = t_cameraDimension.y * 0.9;

	m_health.w = t_cameraDimension.x * 0.25; m_health.h = 20;
	m_health.x = t_cameraDimension.x * 0.5; m_health.y = t_cameraDimension.y * 0.92;

	healthFullWidth = m_health.w;

	m_mana.w = t_cameraDimension.x * 0.25; m_mana.h = 20;
	m_mana.x = t_cameraDimension.x * 0.5; m_mana.y = t_cameraDimension.y * 0.95;
	manaFullWidth = m_mana.w;

	SDL_Surface* healthSurface = IMG_Load("Assets/Health.png");
	m_healthTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), healthSurface);


	//SDL_QueryTexture(m_healthtexture, NULL, NULL, &m_health.w, &m_health.h);
	//SDL_FreeSurface(healthSurface);

	SDL_Surface* manaSurface = IMG_Load("Assets/Mana.png");
	m_manatexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), manaSurface);
	//SDL_FreeSurface(manaSurface);

	SDL_Surface* hudSurface = IMG_Load("Assets/HUD.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), hudSurface);
	//SDL_QueryTexture(m_texture, NULL, NULL, &m_background.w, &m_background.h);
	//SDL_FreeSurface(hudSurface);

	originalHealth = t_OriginalHealth;
}

HUD::~HUD()
{
}

void HUD::update(float t_currentHealth)
{
	m_health.w = (t_currentHealth / originalHealth)
		* healthFullWidth;
}

void HUD::render()
{
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_texture, NULL, &m_background);

	SDL_RenderCopy(Render::Instance()->getRenderer(), m_healthTexture, NULL,&m_health);

	SDL_RenderCopy(Render::Instance()->getRenderer(), m_manatexture, NULL, &m_mana);
}
