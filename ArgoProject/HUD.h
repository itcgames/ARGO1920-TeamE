#ifndef HUD_H
#define HUD_H

#include "SDL.h"
#include "Vector2.h"
#include "Renderer.h"
#include <iostream>
#include "FSM.h"
#include "Text.h"
#include <string>
class HUD
{
public:
	HUD(Vector2 t_cameraDimension, float t_originalHealth, float t_originalMana ,bool& t_skillOne, bool& t_skillTwo, bool& t_skillThree, int& t_killCount, std::string m_class = "Warrior");
	~HUD();

	void update(float t_currentHealth, float t_currentMana);
	void adjustEmptyRect(SDL_Rect t_bar, float t_fullWidth);
	void render();
	void onExit();

	SDL_Rect m_viewableArea;

	SDL_Rect m_background;

	SDL_Rect m_health;
	SDL_Rect m_healthOverflow;

	SDL_Rect m_mana;
	SDL_Rect m_manaOverflow;

	SDL_Rect m_empty;

	SDL_Texture* m_texture;
	SDL_Texture* m_healthTexture;
	SDL_Texture* m_healthOverflowTexture;
	SDL_Texture* m_manaTexture;
	SDL_Texture* m_manaOverflowTexture;
	SDL_Texture* m_emptyTexture;

	SDL_Rect* m_skillBoxs[3];
	SDL_Texture* m_skillTexture[3];
	SDL_Texture* m_timerTexture;
	bool m_timerActive[3];

	bool &q;
	bool &w;
	bool &e;

	int &killCount;
	int m_previousCount;

	float healthFullWidth;
	float originalHealth;
	float currentHealth;

	float manaFullWidth;
	float originalMana;
	float currentMana;

	TTF_Font* Abel;

	Text* m_timerText[3];
	float m_timerStart[3];
	float m_timerCurrent[3];
	float m_timerLength[3];

	Text* m_killCountText;
	Text* m_healthText;
	Text* m_manaText;
	Text* m_KillText;
};

#endif