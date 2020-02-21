#include "HUD.h"

HUD::HUD(Vector2 t_cameraDimension, float t_OriginalHealth, float t_originalMana)
{

	m_background.w = t_cameraDimension.x * 0.9; m_background.h = t_cameraDimension.y * 0.1;
	m_background.x = t_cameraDimension.x * -0.1; m_background.y = t_cameraDimension.y * 0.9;

	m_health.w = t_cameraDimension.x * 0.25; m_health.h = 20;
	m_health.x = t_cameraDimension.x * 0.5; m_health.y = t_cameraDimension.y * 0.92;
	m_healthOverflow.w = 0; m_healthOverflow.h = 20;
	m_healthOverflow.x = t_cameraDimension.x * 0.5; m_healthOverflow.y = t_cameraDimension.y * 0.92;

	healthFullWidth = m_health.w;

	m_mana.w = t_cameraDimension.x * 0.25; m_mana.h = 20;
	m_mana.x = t_cameraDimension.x * 0.5; m_mana.y = t_cameraDimension.y * 0.95;
	m_manaOverflow.w = 0; m_manaOverflow.h = 20;
	m_manaOverflow.x = t_cameraDimension.x * 0.5; m_manaOverflow.y = t_cameraDimension.y * 0.95;
	manaFullWidth = m_mana.w;

	SDL_Surface* healthSurface = IMG_Load("Assets/Health.png");
	m_healthTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), healthSurface);
	SDL_Surface* healthOverflowSurface = IMG_Load("Assets/Gold.png");
	m_healthOverflowTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), healthOverflowSurface);

	//SDL_QueryTexture(m_healthtexture, NULL, NULL, &m_health.w, &m_health.h);
	//SDL_FreeSurface(healthSurface);

	SDL_Surface* manaSurface = IMG_Load("Assets/Mana.png");
	m_manatexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), manaSurface);
	SDL_Surface* manaOverflowSurface = IMG_Load("Assets/Stamina.png");
	m_manaOverflowTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), manaOverflowSurface);
	//SDL_FreeSurface(manaSurface);

	SDL_Surface* hudSurface = IMG_Load("Assets/HUD.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), hudSurface);
	//SDL_QueryTexture(m_texture, NULL, NULL, &m_background.w, &m_background.h);
	//SDL_FreeSurface(hudSurface);

	SDL_Surface* emptySurface = IMG_Load("Assets/Empty.png");
	m_emptyTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), emptySurface);

	originalHealth = t_OriginalHealth;
	originalMana = t_originalMana;
}

HUD::~HUD()
{
}

void HUD::update(float t_currentHealth, float t_currentMana)
{
	currentHealth = t_currentHealth;
	currentMana = t_currentMana;

	if (currentHealth <= originalHealth)
	{
		m_health.w = (currentHealth / originalHealth)
			* healthFullWidth;
	}
	else
	{
		m_health.w = healthFullWidth;
		m_healthOverflow.w = ((currentHealth - originalHealth) / originalHealth)
			* healthFullWidth;
	}

	if (currentMana <= originalMana)
	{
		m_mana.w = (currentMana / originalMana)
			* manaFullWidth;
	}
	else
	{
		m_mana.w = manaFullWidth;
		m_manaOverflow.w = ((currentMana - originalMana) / originalMana)
			* manaFullWidth;
	}
}

void HUD::render()
{
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_texture, NULL, &m_background);

	if (originalHealth > currentHealth)
	{
		adjustEmptyRect(m_health, healthFullWidth);
		//SDL_RenderCopy(Render::Instance()->getRenderer(), m_emptyTexture, NULL, &m_empty);
	}

	SDL_RenderCopy(Render::Instance()->getRenderer(), m_healthTexture, NULL,&m_health);

	if (originalHealth < currentHealth)
	{
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_healthOverflowTexture, NULL, &m_healthOverflow);
	}

	if (originalMana > currentMana)
	{
		adjustEmptyRect(m_mana,manaFullWidth);
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_emptyTexture, NULL, &m_empty);
	}

	SDL_RenderCopy(Render::Instance()->getRenderer(), m_manatexture, NULL, &m_mana);

	if (originalMana < currentMana)
	{
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_manaOverflowTexture, NULL, &m_manaOverflow);
	}
}

void HUD::adjustEmptyRect(SDL_Rect t_bar, float t_fullWidth)
{
	m_empty.x = t_bar.x;
	m_empty.y = t_bar.y;
	m_empty.w = t_fullWidth;
	m_empty.h = t_bar.h;
}
