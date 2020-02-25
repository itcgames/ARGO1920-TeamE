#include "HUD.h"

HUD::HUD(Vector2 t_cameraDimension, float t_OriginalHealth, float t_originalMana, bool& t_skillOne, bool& t_skillTwo, bool& t_skillThree, int& t_killCount ,std::string m_class):
	q(t_skillOne),
	w(t_skillTwo),
	e(t_skillThree),
	killCount(t_killCount)
{
	m_background.w = t_cameraDimension.x * 0.8; m_background.h = t_cameraDimension.y * 0.1;
	m_background.x = 0; m_background.y = t_cameraDimension.y * 0.9;

	m_health.w = t_cameraDimension.x * 0.25; m_health.h = 20;
	m_health.x = t_cameraDimension.x * 0.425; m_health.y = t_cameraDimension.y * 0.92;
	m_healthOverflow.w = 0; m_healthOverflow.h = 20;
	m_healthOverflow.x = t_cameraDimension.x * 0.425; m_healthOverflow.y = t_cameraDimension.y * 0.92;

	healthFullWidth = m_health.w;

	m_mana.w = t_cameraDimension.x * 0.25; m_mana.h = 20;
	m_mana.x = t_cameraDimension.x * 0.425; m_mana.y = t_cameraDimension.y * 0.95;
	m_manaOverflow.w = 0; m_manaOverflow.h = 20;
	m_manaOverflow.x = t_cameraDimension.x * 0.425; m_manaOverflow.y = t_cameraDimension.y * 0.95;
	manaFullWidth = m_mana.w;

	SDL_Surface* healthSurface = IMG_Load("Assets/Health.png");
	m_healthTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), healthSurface);
	SDL_Surface* healthOverflowSurface = IMG_Load("Assets/Gold.png");
	m_healthOverflowTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), healthOverflowSurface);

	//SDL_QueryTexture(m_healthtexture, NULL, NULL, &m_health.w, &m_health.h);
	//SDL_FreeSurface(healthSurface);

	SDL_Surface* manaSurface = IMG_Load("Assets/Mana.png");
	m_manaTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), manaSurface);
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

	/// Timers set up
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	Abel = TTF_OpenFont("Assets/Font/Abel.ttf", t_cameraDimension.y * 0.074);

	if (!Abel) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	SDL_Surface* timerSurface = IMG_Load("Assets/Empty.png");
	m_timerTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), timerSurface);
	SDL_SetTextureBlendMode(m_timerTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_timerTexture, 124);

	std::string m_fileAddress = std::string("Assets/" + m_class + std::string("ButtonQ") + ".png ");
	SDL_Surface* skillSurface = IMG_Load(m_fileAddress.c_str());
	m_skillTexture[0] = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), skillSurface);

	m_fileAddress = std::string("Assets/" + m_class + std::string("ButtonW") + ".png ");
	skillSurface = IMG_Load(m_fileAddress.c_str());
	m_skillTexture[1] = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), skillSurface);

	m_fileAddress = std::string("Assets/" + m_class + std::string("ButtonE") + ".png ");
	skillSurface = IMG_Load(m_fileAddress.c_str());
	m_skillTexture[2] = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), skillSurface);

	for (int i = 0; i < 3; i++)
	{
		m_timerLength[i] = 1 * (i + 1);
		m_timerText[i] = new Text(Abel, std::to_string(int(m_timerLength[i])), t_cameraDimension.x * (0.06 + (0.13 * i)), t_cameraDimension.y * 0.91);
		m_skillBoxs[i] = new SDL_Rect();
		m_skillBoxs[i]->x = t_cameraDimension.x * (0.02 + (0.13 * i));
		m_skillBoxs[i]->y = t_cameraDimension.y * 0.91;
		m_skillBoxs[i]->w = t_cameraDimension.x * 0.125;
		m_skillBoxs[i]->h = t_cameraDimension.y * 0.074;

		m_timerActive[i] = false;
	}

	m_killCountText = new Text(Abel, std::to_string(int(killCount)), t_cameraDimension.x * 0.7, t_cameraDimension.y * 0.91);
	m_previousCount = killCount;
}

HUD::~HUD()
{
}

void HUD::update(float t_currentHealth, float t_currentMana)
{
	currentHealth = t_currentHealth;
	currentMana = t_currentMana;

	//Timer
	if (q != m_timerActive[0] && q == true)
	{
		m_timerActive[0] = q;
		m_timerStart[0] = SDL_GetTicks() / 1000;
	}
	else if (q == false)
	{
		m_timerActive[0] = q;
	}

	if (w != m_timerActive[1] && w == true)
	{
		m_timerActive[1] = w;
		m_timerStart[1] = SDL_GetTicks() / 1000;
	}
	else if (w == false)
	{
		m_timerActive[1] = w;
	}

	if (e != m_timerActive[2] && e == true)
	{
		m_timerActive[2] = e;
		m_timerStart[2] = SDL_GetTicks() / 1000;
	}
	else if(e == false)
	{
		m_timerActive[2] = e;
	}

	//Kill Count
	if (killCount != m_previousCount)
	{
		m_killCountText->update(std::to_string(killCount));
		m_previousCount = killCount;
	}


	//Bars
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

	for (int i = 0; i < 3; i++)
	{
		if (m_timerActive[i])
		{
			m_timerCurrent[i] = SDL_GetTicks() / 1000;
			m_timerText[i]->update(std::to_string(int(m_timerLength[i] - (m_timerCurrent[i] - m_timerStart[i]))));

			if (int(m_timerLength[i] - (m_timerCurrent[i] - m_timerStart[i]) < 0))
			{
				if (i == 0)
				{
					q = false;
				}
				else if (i == 1)
				{
					w = false;
				}
				else
				{
					e = false;
				}
			}
		}
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

	SDL_RenderCopy(Render::Instance()->getRenderer(), m_manaTexture, NULL, &m_mana);

	if (originalMana < currentMana)
	{
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_manaOverflowTexture, NULL, &m_manaOverflow);
	}

	for (int i = 0; i < 3; i++)
	{
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_skillTexture[i], NULL, m_skillBoxs[i]);
		if (m_timerActive[i] == true)
		{
			SDL_RenderCopy(Render::Instance()->getRenderer(), m_timerTexture, NULL, m_skillBoxs[i]);
			m_timerText[i]->render();
		}
	}
	m_killCountText->render();
}

void HUD::adjustEmptyRect(SDL_Rect t_bar, float t_fullWidth)
{
	m_empty.x = t_bar.x;
	m_empty.y = t_bar.y;
	m_empty.w = t_fullWidth;
	m_empty.h = t_bar.h;
}

void HUD::onExit()
{
	SDL_DestroyTexture(m_texture);
	SDL_DestroyTexture(m_healthTexture);
	SDL_DestroyTexture(m_healthOverflowTexture);
	SDL_DestroyTexture(m_manaTexture);
	SDL_DestroyTexture(m_manaOverflowTexture);
	SDL_DestroyTexture(m_emptyTexture);

	for (int i = 0; i < 3; i++)
	{
		m_timerText[i]->DestroyText();
		SDL_DestroyTexture(m_skillTexture[i]);
	}
}